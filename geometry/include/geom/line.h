#pragma once

#include "vector.h"

namespace geom
{
template<class scalar_type>
class Line_3D {
public:
    using point = Point_3D<scalar_type>;
    using vector = Vector_3D<scalar_type>;
    Line_3D(const point& a, const point& b) 
        : a{ a }
        , v{ (b - a).normalized() }
    {}

    const point& get_point() const {return a;};
    const vector& get_vector() const {return v;};

private:
    point a;
    vector v;
};
} // namespace geom
