/*
Philipp Schmid
Max Staneker
*/
#include "voxel_grid.h"

#include "transformations.h"
#include "operations.h"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <sstream>

VoxelGrid::VoxelGrid(const Shape& shape)
{
    //throw std::logic_error("task 6.4 b)");
    //(void) shape; // silence unused parameter warning
    AABB ShapeBounds = shape.getBounds();
    bounds = ShapeBounds;

    Point3D boundMin = bounds.min;
    Point3D boundMax = bounds.max;
    Point3D range = boundMax - boundMin;

    if (range.x <= 0.0f || range.y <= 0.0f || range.z <= 0.0f) {range = {0, 0, 0};}
        
    if (range.x > INT_MAX / level_of_detail ||
        range.y > INT_MAX / level_of_detail ||
        range.z > INT_MAX / level_of_detail)
        {range = {0, 0, 0};}

    res_x = static_cast<int>(std::ceil(range.x * level_of_detail));
    res_y = static_cast<int>(std::ceil(range.y * level_of_detail));
    res_z = static_cast<int>(std::ceil(range.z * level_of_detail));

    if (res_x == 0) res_x = 1;
    if (res_y == 0) res_y = 1;
    if (res_z == 0) res_z = 1;

    const std::size_t voxelCount = static_cast<std::size_t>(res_x) * res_y * res_z;
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
    Point3D resolution{static_cast<float>(res_x), 
                      static_cast<float>(res_y), 
                      static_cast<float>(res_z)};
    
    Point3D boundsExtents = bounds.max - bounds.min;
    Point3D pOffseted = (p - bounds.min) * resolution / boundsExtents;
    
    uint32_t x = static_cast<uint32_t>(pOffseted.x);
    uint32_t y = static_cast<uint32_t>(pOffseted.y);
    uint32_t z = static_cast<uint32_t>(pOffseted.z);
    
    if (x >= res_x || y >= res_y || z >= res_z) {
        return false;
    }
    return isSet(x, y, z);
}

bool VoxelGrid::isSet(uint32_t x, uint32_t y, uint32_t z) const
{
    // When running in debug mode, these will check whether the supplied indices are valid or "trap" to the debugger.
    // When no debugger is running, failing the assertion will terminate the program immediately.
    // When compiled in release mode, assert() does nothing.
    assert(x < res_x);
    assert(y < res_y);
    assert(z < res_z);

    //throw std::logic_error("task 6.4 c)");

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
