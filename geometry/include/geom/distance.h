#pragma once

#include <algorithm>
#include <stdexcept>
#include "line.h"

namespace geom
{

template<class scalar_type>
std::pair<Point_3D<scalar_type>, Point_3D<scalar_type>> closest_point_on_cross_lines(
    const Line_3D<scalar_type>& a, const Line_3D<scalar_type>& b) 
{
    auto c = a.get_point() - b.get_point();
    const auto& v = a.get_vector();
    const auto& w = b.get_vector();

    scalar_type vw = dot_product(v, w);
    if (std::abs(vw - 1.) < std::numeric_limits<scalar_type>::epsilon()) {
        throw std::runtime_error("lines are parallel");
    }
    scalar_type cv = dot_product(c, v);
    
    scalar_type cw = dot_product(c, w);

    scalar_type u = .5 * (cv * vw + 2. * cw) / (1. - std::pow(vw, 2.));
    scalar_type t = u * vw - cv;

    return {a.get_point() + t * a.get_vector(), b.get_point() + u * b.get_vector()};
}
} // namespace geom
