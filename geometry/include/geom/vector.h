#pragma once

#include "point.h"

#include <algorithm>
#include <cmath>

namespace geom
{

template<class scalar_type>
class Vector_3D;

template<class scalar_type>
Vector_3D<scalar_type> cross_product(const Vector_3D<scalar_type>& a, const Vector_3D<scalar_type>& b);

template<class scalar_type>
class Vector_3D {

public:
    Vector_3D(scalar_type x, scalar_type y, scalar_type z)
        : x(x)
        , y(y)
        , z(z)
    {}

    static Vector_3D zero() {
        return Vector_3D{ 0., 0., 0. };
    }
   
    const scalar_type& get_x() const { return x; }
    const scalar_type& get_y() const { return y; }
    const scalar_type& get_z() const { return z; }

    const scalar_type dist2() const {
        return x * x + y * y + z * z;
    }

    const scalar_type dist() const {
        return std::sqrt(dist2());
    }

     Vector_3D operator* (scalar_type&& k) {
        return {x * k, y * k, z * k};
    }

private:
    scalar_type x, y, z;

    friend Vector_3D<scalar_type> cross_product<>(const Vector_3D<scalar_type>& a, const Vector_3D<scalar_type>& b);
}; 

template<class scalar_type>
Vector_3D<scalar_type> operator* (scalar_type&& k, Vector_3D<scalar_type>&& vec) {
    return vec * k;
}

template<class scalar_type>
bool vector_eq(const Vector_3D<scalar_type>& l, const Vector_3D<scalar_type>& r, scalar_type eps) {
    auto eq = [eps](auto l, auto r) {
        return std::abs(l - r) < eps;
    };
    return eq(l.get_x(), r.get_x()) && 
           eq(l.get_y(), r.get_y()) &&
           eq(l.get_z(), r.get_z());
}

template<class scalar_type>
Vector_3D<scalar_type> cross_product(const Vector_3D<scalar_type>& a, const Vector_3D<scalar_type>& b) {
    return Vector_3D<scalar_type>{ 
        a.y * b.z - a.z * b.y,
        a.x * b.z - a.z * b.x,
        a.x * b.y - a.y * b.x  
    };
}

} // namespace geom
