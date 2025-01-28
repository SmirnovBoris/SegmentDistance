#pragma once

#include "point.h"
#include "vector.h"

namespace geom
{

template<class scalar_type>
Vector_3D<scalar_type> operator- (const Point_3D<scalar_type>& a, const Point_3D<scalar_type>& b) {
    return { a.get_x() - b.get_x(),
             a.get_y() - b.get_y(),
             a.get_z() - b.get_z() };
}

template<class scalar_type>
Point_3D<scalar_type> operator+ (const Point_3D<scalar_type>& a, const Vector_3D<scalar_type>& v) {
    return { a.get_x() + v.get_x(),
             a.get_y() + v.get_y(),
             a.get_z() + v.get_z() };
}

} // namespace geom
