#pragma once

#include <algorithm>
#include <stdexcept>
#include <optional>
#include "line.h"
#include "sector.h"
#include "basic_algorithm.h"

namespace geom
{

namespace impl
{
template<std::floating_point scalar_type>
std::pair<Point_3D<scalar_type>, Point_3D<scalar_type>> closest_point_on_cross_lines(
    const Line_3D<scalar_type>& a, const Line_3D<scalar_type>& b) 
{
    auto c = a.get_point() - b.get_point();
    const auto& v = a.get_vector();
    const auto& w = b.get_vector();

    scalar_type vw = dot_product(v, w);
    if (std::abs(vw - 1.) < epsilon<scalar_type>) {
        throw std::runtime_error("lines are parallel");
    }
    scalar_type cv = dot_product(c, v);
    scalar_type cw = dot_product(c, w);

    scalar_type u = (cw - cv * vw) / (1. - std::pow(vw, 2.));
    scalar_type t = u * vw - cv;

    return {a.get_point() + t * a.get_vector(), b.get_point() + u * b.get_vector()};
}
} // namespace impl

template<std::floating_point scalar_type>
scalar_type distance(const Sector_3D<scalar_type>& first_sector, 
                     const Sector_3D<scalar_type>& second_sector) 
{
    using point = Point_3D<scalar_type>;
    using line = Line_3D<scalar_type>;
    static constexpr auto eps = epsilon<scalar_type>;
    
    std::vector<point> first_sector_interested_points{
        first_sector.get_first_point(), 
        first_sector.get_second_point()};
    std::vector<point> second_sector_interested_points{
        second_sector.get_first_point(), 
        second_sector.get_second_point()};
    std::optional<line> first_line;
    if (first_sector.len2()) {
        first_line = first_sector;
    }
    std::optional<line> second_line;
    if (second_sector.len2()) {
        second_line = second_sector;
    }

    const auto& add_first_point = [&](const point& p) {
        if (first_sector.contains(p)) {
            first_sector_interested_points.push_back(p);
        }

    };
    const auto& add_second_point = [&](const point& p) {
        if (second_sector.contains(p)) {
            second_sector_interested_points.push_back(p);
        }
    };

    if (first_line && second_line && (first_line->get_vector() * second_line->get_vector()).len2() > eps) {
        const auto& [first_line_point, second_line_point] = 
            impl::closest_point_on_cross_lines(*first_line, *second_line);
        add_first_point(first_line_point);
        add_second_point(second_line_point);
    }
    if (first_line) {
        add_first_point(projection(*first_line, second_sector.get_first_point()));
        add_first_point(projection(*first_line, second_sector.get_second_point()));
    }
    if (second_line) {
        add_second_point(projection(*second_line, first_sector.get_first_point()));
        add_second_point(projection(*second_line, first_sector.get_second_point()));
    }

    scalar_type res = std::numeric_limits<scalar_type>::infinity();
    for (const auto& p1 : first_sector_interested_points) {
        for (const auto& p2 : second_sector_interested_points) {
            res = std::min(res, (p1 - p2).len());
        }
    }

    return res;
}

} // namespace geom
