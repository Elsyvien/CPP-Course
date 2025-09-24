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
