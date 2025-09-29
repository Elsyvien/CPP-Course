#include "transformations.h"
#include <cmath>

// helper function for 2D rotations
std::pair<float, float> rotate2D(float x, float y, float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return {cos*x-sin*y, sin*x+cos*y};
}


Transformation::Transformation(const Shape& shape)
    : sub_shape{shape.clone()}
{

}

Shape Scaled::clone_impl() const { 
    return {std::make_shared<Scaled>(sub_shape, scale)};
}

bool Scaled::isInside_impl(const Point3D& p) const {
    Point3D scaled = p / scale;
    return sub_shape.isInside(scaled);
}

AABB Scaled::getBounds_impl() const {
    Point3D boundsMin = sub_shape.getBounds().min;
    Point3D boundsMax = sub_shape.getBounds().max;
    AABB result = {boundsMin * scale, boundsMax * scale };
    return result;
}

Shape Translated::clone_impl() const {
    return {std::make_shared<Translated>(sub_shape, translation)};
}

AABB Translated::getBounds_impl() const {
    AABB originalShape = sub_shape.getBounds();
    AABB result = {originalShape.min + translation, originalShape.max + translation};
    return result;
}

bool Translated::isInside_impl(const Point3D& p) const {
    Point3D translated = p - translation;
    return sub_shape.isInside(translated);
}

Shape Rotated::clone_impl() const {
    return {std::make_shared<Rotated>(sub_shape, axis, angle)};
}

bool Rotated::isInside_impl(const Point3D& p) const {
    Point3D rotated = p;

    if (axis == Axis::Z) {
        auto xy = rotate2D(p.x, p.y, -angle);
        rotated.x = xy.first;
        rotated.y = xy.second;
    } else if (axis == Axis::X) {
        auto yz = rotate2D(p.y, p.z, -angle);
        rotated.y = yz.first;
        rotated.z = yz.second;
    } else if (axis == Axis::Y) {
        auto xz = rotate2D(p.x, p.z, angle);
        rotated.x = xz.first;
        rotated.z = xz.second;
    }

    return sub_shape.isInside(rotated);
}

AABB Rotated::getBounds_impl() const {
    AABB original = sub_shape.getBounds();

    Point3D originalMin = original.min;
    Point3D originalMax = original.max;

    Point3D ecken[8] = {
        {originalMin.x, originalMin.y, originalMin.z}, {originalMin.x, originalMin.y, originalMax.z},
        {originalMin.x, originalMax.y, originalMin.z}, {originalMin.x, originalMax.y, originalMax.z},
        {originalMax.x, originalMin.y, originalMin.z}, {originalMax.x, originalMin.y, originalMax.z},
        {originalMax.x, originalMax.y, originalMin.z}, {originalMax.x, originalMax.y, originalMax.z}
    };

    Point3D rotateOrigin = ecken[0];
    if (axis == Axis::Z) {
        std::pair<float, float> xy = rotate2D(rotateOrigin.x, rotateOrigin.y, angle);
        rotateOrigin.x = xy.first;
        rotateOrigin.y = xy.second;
    } else if (axis == Axis::X) {
        std::pair<float, float> yz = rotate2D(rotateOrigin.y, rotateOrigin.z, angle);
        rotateOrigin.y = yz.first;
        rotateOrigin.z = yz.second;
    } else if (axis == Axis::Y) {
        std::pair<float, float> xz = rotate2D(rotateOrigin.x, rotateOrigin.z, -angle);
        rotateOrigin.x = xz.first;
        rotateOrigin.z = xz.second;
    }
    Point3D newMin = rotateOrigin;
    Point3D newMax = rotateOrigin;
    // TODO: Bessere lösung finden
    for (int i = 1; i < 8; ++i) { // meh irgendwie unschön
        Point3D next = ecken[i];
        if (axis == Axis::Z) {
            std::pair<float, float> xy = rotate2D(next.x, next.y, angle);
            next.x = xy.first;
            next.y = xy.second;
        } else if (axis == Axis::X) {
            std::pair<float, float> yz = rotate2D(next.y, next.z, angle);
            next.y = yz.first;
            next.z = yz.second;
        } else if (axis == Axis::Y) {
            std::pair<float, float> xz = rotate2D(next.x, next.z, -angle);
            next.x = xz.first;
            next.z = xz.second;
        }
        newMin.x = std::min(newMin.x, next.x);
        newMin.y = std::min(newMin.y, next.y);
        newMin.z = std::min(newMin.z, next.z);
        newMax.x = std::max(newMax.x, next.x);
        newMax.y = std::max(newMax.y, next.y);
        newMax.z = std::max(newMax.z, next.z);
    }
    return {newMin, newMax};
}