#pragma once

#include "vector.h"
#include "basics.h"
#include "sector.h"

#include <stdexcept>

namespace geom
{
template<std::floating_point scalar_type>
class Sector_3D;

template<std::floating_point scalar_type>
class Line_3D {
public:
    using point = Point_3D<scalar_type>;
    using vector = Vector_3D<scalar_type>;
    using sector = Sector_3D<scalar_type>;

    constexpr Line_3D(const point& a, const point& b) 
        : a{ a }
        , v{ base_vector(a, b) }
    {}
    constexpr Line_3D(const sector& s)
        : Line_3D(s.get_first_point(), s.get_second_point()) 
    {}

    constexpr point get_point() const { return a; };
    constexpr vector get_vector() const { return v; };

private:
    point a;
    vector v;

    static constexpr vector base_vector(const point& a, const point& b) {
        vector base = b - a;
        if (base.len2() < epsilon<scalar_type>) {
            throw std::runtime_error("cannot initialize line from 1 point");
        }
        return base.normalized();
    }
};
} // namespace geom
