#pragma once

#include "point.h"
#include "vector.h"
#include "basic_algorithm.h"
#include "basics.h"

namespace geom {

template<std::floating_point scalar_type>
class Sector_3D {
public:
    using point = Point_3D<scalar_type>;
    
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
        static constexpr scalar_type eps = epsilon<scalar_type>;
        auto v = b - a;
        auto w = p - a;
        auto t = dot_product(v, w) / v.len2();
        return (w * v).len2() < eps && t > -eps && t < 1. + eps;
    }
private:
    point a, b;
};

} // namepace geom
