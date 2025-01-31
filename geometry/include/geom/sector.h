#pragma once

#include "point.h"
#include "vector.h"

namespace geom {

template<std::floating_point scalar_type>
class Sector_3D {
public:
    using point = Point_3D<scalar_type>;
    static constexpr scalar_type eps = 1e-5;

    Sector_3D(const point& a, const point& b) 
        : a{a}
        , b{b}
    {}
    point get_first_point() const {
        return a;
    }
    point get_second_point() const {
        return b;
    }

    scalar_type len2() const {
        return (a - b).len2();
    }

    bool contains(const point& p) const {
        auto v = b - a;
        auto w = p - a;
        auto t = dot_product(v, w) / v.len2();
        return (w * v).len2() < eps && t > -eps && t < 1. + eps;
    }
private:
    point a, b;
};

} // namepace geom
