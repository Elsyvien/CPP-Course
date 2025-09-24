#pragma once

#include "shapes.h"

#include <memory>

/// shared abstract transformation base class containing a nested shape to be transformed
class Transformation : public Shape {
protected:
    Transformation(const Shape& shape);
public:
    Shape sub_shape;
};

// of course, one could implement all these transformations jointly as a single transformation matrix.
// for simplicity, we don't do that here.

