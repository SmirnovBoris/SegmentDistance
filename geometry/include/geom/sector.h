#pragma once

#include "point.h"
#include "vector.h"
#include "basic_algorithm.h"
#include "basics.h"

#include <concepts>

namespace geom {

template<std::floating_point scalar_type>
class Sector_3D {
public:
    using point = Point_3D<scalar_type>;
    
    constexpr Sector_3D(const point& a, const point& b) 
        : a{a}
        , b{b}
    {}
    constexpr point get_first_point() const {
        return a;
    }
    constexpr point get_second_point() const {
        return b;
    }

    constexpr scalar_type len2() const {
        return (a - b).len2();
    }

    constexpr bool contains(const point& p) const {
        constexpr scalar_type eps = epsilon<scalar_type>;
        auto v = b - a;
        auto w = p - a;
        auto t = dot_product(v, w) / v.len2();
        return (w * v).len2() < eps && t > -eps && t < 1. + eps;
    }
private:
    point a, b;
};

} // namepace geom
