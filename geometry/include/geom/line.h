#pragma once

#include "vector.h"
#include "sector.h"

namespace geom
{
template<class scalar_type>
class Line_3D {
public:
    using point = Point_3D<scalar_type>;
    using vector = Vector_3D<scalar_type>;
    using sector = Sector_3D<scalar_type>;

    Line_3D(const point& a, const point& b) 
        : a{ a }
        , v{ base_vector(a, b) }
    {}
    Line_3D(const sector& s)
        : Line_3D(s.get_first_point(), s.get_second_point()) 
    {}

    const point& get_point() const { return a; };
    const vector& get_vector() const { return v; };

private:
    point a;
    vector v;

    static vector base_vector(const point& a, const point& b) {
        vector base = b - a;
        if (base.len2() < std::numeric_limits<scalar_type>::epsilon()) {
            throw std::runtime_error("cannot initialize line from 1 point");
        }
        return base.normalized();
    }
};
} // namespace geom
