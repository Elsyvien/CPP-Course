#include "voxel_grid.h"

#include "transformations.h"
#include "operations.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>

VoxelGrid::VoxelGrid(const Shape& shape)
{
    bounds = shape.getBounds();

    auto sanitize = [](float value) {
        return std::isfinite(value) ? value : 0.0f;
    };

    bounds.min.x = sanitize(bounds.min.x);
    bounds.min.y = sanitize(bounds.min.y);
    bounds.min.z = sanitize(bounds.min.z);
    bounds.max.x = sanitize(bounds.max.x);
    bounds.max.y = sanitize(bounds.max.y);
    bounds.max.z = sanitize(bounds.max.z);

    if (bounds.max.x < bounds.min.x) bounds.max.x = bounds.min.x;
    if (bounds.max.y < bounds.min.y) bounds.max.y = bounds.min.y;
    if (bounds.max.z < bounds.min.z) bounds.max.z = bounds.min.z;

    Point3D range = bounds.max - bounds.min;

    const auto safeResolution = [](float extent) -> uint32_t {
        if (!(extent > 0.0f)) {
            return 1u;
        }
        float scaled = extent * static_cast<float>(VoxelGrid::level_of_detail);
        if (!std::isfinite(scaled) || scaled <= 0.0f) {
            return 1u;
        }
        if (scaled > static_cast<float>(std::numeric_limits<uint32_t>::max())) {
            return std::numeric_limits<uint32_t>::max();
        }
        uint32_t res = static_cast<uint32_t>(std::ceil(scaled));
        return std::max(1u, res);
    };

    res_x = safeResolution(range.x);
    res_y = safeResolution(range.y);
    res_z = safeResolution(range.z);

    const std::size_t voxelCount = static_cast<std::size_t>(res_x) * static_cast<std::size_t>(res_y) * static_cast<std::size_t>(res_z);
    voxels.assign(voxelCount, false);
    for (uint32_t x = 0; x < res_x; x++) {
        for (uint32_t y = 0; y < res_y; y++) {
            for (uint32_t z = 0; z < res_z; z++) {
                Point3D center = voxelCenter(x, y, z);
                if (shape.isInside(center)) {
                    voxels[x + res_x * (y + res_y * z)] = true;
                }
            }
        }
    }
}

std::tuple<uint32_t, uint32_t, uint32_t> VoxelGrid::getResolution() const
{
    return {res_x, res_y, res_z};
}

VoxelSlice VoxelGrid::extractSlice(Axis axis, uint32_t slice) const
{
    uint32_t dim1, dim2;
    if (axis == Axis::X) {
        dim1 = res_y; 
        dim2 = res_z;  
    } else if (axis == Axis::Y) {
        dim1 = res_z;
        dim2 = res_x;
    } else {
        dim1 = res_x;
        dim2 = res_y;
    }
    VoxelSlice result(dim1, dim2);
    
    if (axis == Axis::X) {
        for (uint32_t y = 0; y < res_y; y++) {
            for (uint32_t z = 0; z < res_z; z++) {
                bool voxelValue = isSet(slice, y, z);
                result.data[z][y] = voxelValue;
            }
        }
    } else if (axis == Axis::Y) {
        for (uint32_t z = 0; z < res_z; z++) {
            for (uint32_t x = 0; x < res_x; x++) {
                bool voxelValue = isSet(x, slice, z);
                result.data[x][z] = voxelValue;
            }
        }
    } else { 
        for (uint32_t y = 0; y < res_y; y++) {
            for (uint32_t x = 0; x < res_x; x++) {
                bool voxelValue = isSet(x, y, slice);
                result.data[y][x] = voxelValue;
            }
        }
    } return result;
}

Shape VoxelGrid::clone_impl() const
{
    return {std::make_shared<VoxelGrid>(*this)};
}

AABB VoxelGrid::getBounds_impl() const
{
    return bounds;
}

bool VoxelGrid::isInside_impl(const Point3D& p) const
{
    if (!bounds.contains(p)) {
        return false;
    }

    Point3D extents = bounds.max - bounds.min;

    auto normalize = [&](float value, float extent, float minimum) {
        if (extent == 0.0f) {
            return 0.0f;
        }
        return (value - minimum) / extent;
    };

    float nx = normalize(p.x, extents.x, bounds.min.x);
    float ny = normalize(p.y, extents.y, bounds.min.y);
    float nz = normalize(p.z, extents.z, bounds.min.z);

    if (nx < 0.0f || nx > 1.0f || ny < 0.0f || ny > 1.0f || nz < 0.0f || nz > 1.0f) {
        return false;
    }

    auto toIndex = [](float t, uint32_t resolution) {
        if (resolution <= 1u) {
            return 0u;
        }
        if (t <= 0.0f) {
            return 0u;
        }
        if (t >= 1.0f) {
            return resolution - 1u;
        }
        return static_cast<uint32_t>(std::floor(t * static_cast<float>(resolution)));
    };

    uint32_t x = toIndex(nx, res_x);
    uint32_t y = toIndex(ny, res_y);
    uint32_t z = toIndex(nz, res_z);

    return isSet(x, y, z);
}

bool VoxelGrid::isSet(uint32_t x, uint32_t y, uint32_t z) const
{
    assert(x < res_x);
    assert(y < res_y);
    assert(z < res_z);

    return voxels[x + res_x * (y + res_y * z)];
}

Point3D VoxelGrid::voxelCenter(uint32_t x, uint32_t y, uint32_t z) const
{
    auto boundMin = bounds.min;
    auto boundMax = bounds.max;
    
    Point3D range = boundMax - boundMin;
    Point3D step{
        res_x ? range.x / static_cast<float>(res_x) : 0.0f,
        res_y ? range.y / static_cast<float>(res_y) : 0.0f,
        res_z ? range.z / static_cast<float>(res_z) : 0.0f
    };

    Point3D offset{
        (static_cast<float>(x) + 0.5f) * step.x,
        (static_cast<float>(y) + 0.5f) * step.y,
        (static_cast<float>(z) + 0.5f) * step.z
    };

    return boundMin + offset;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelSlice& slice)
{
    for (uint32_t y = 0; y < slice.data.size(); y++) {
        for (uint32_t x = 0; x < slice.data[y].size(); x++) {
            if (slice.data[y][x] == true) {
                ostream << 'X';  
            } else {
                ostream << '.'; 
            }
            ostream << ' ';
        }
        ostream << '\n';
    }
    
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelGrid& vg)
{
    uint32_t res_z;
    std::tie(std::ignore, std::ignore, res_z) = vg.getResolution();

    for (uint32_t z=0; z<res_z; ++z) {
        auto slice = vg.extractSlice(Axis::Z, z);
        ostream << slice << std::endl;
    }
    return ostream;
}
