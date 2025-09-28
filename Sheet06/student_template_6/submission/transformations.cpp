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
    Point3D translated = p + translation;
    return sub_shape.isInside(translated);
}

Shape Rotated::clone_impl() const {
    return {std::make_shared<Rotated>(sub_shape, axis, angle)};
}

bool Rotated::isInside_impl(const Point3D& p) const {
    std::pair<float, float> xy = rotate2D(p.x, p.y, -angle);
    Point3D rotated{xy.first, xy.second, p.z};
    return sub_shape.isInside(rotated);
}