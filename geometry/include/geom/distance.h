#pragma once

#include "sector.h"
#include "line.h"
#include "basic_algorithm.h"

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <optional>

namespace geom
{

namespace impl
{
template<std::floating_point scalar_type>
constexpr std::pair<Point_3D<scalar_type>, Point_3D<scalar_type>> closest_point_on_cross_lines(
    const Line_3D<scalar_type>& a, const Line_3D<scalar_type>& b) 
{
    auto c = a.get_point() - b.get_point();
    const auto& v = a.get_vector();
    const auto& w = b.get_vector();

    scalar_type vw = dot_product(v, w);
    scalar_type cv = dot_product(c, v);
    scalar_type cw = dot_product(c, w);

    scalar_type u = (cw - cv * vw) / (1. - vw * vw));
    scalar_type t = u * vw - cv;

    return {a.get_point() + t * a.get_vector(), b.get_point() + u * b.get_vector()};
}
} // namespace impl

template<std::floating_point scalar_type>
constexpr scalar_type distance(const Sector_3D<scalar_type>& first_sector, 
                     const Sector_3D<scalar_type>& second_sector) 
{
    using point = Point_3D<scalar_type>;
    using line = Line_3D<scalar_type>;
    constexpr auto eps = epsilon<scalar_type>;
    
    
    bool has_first_line = first_sector.len2() > eps;
    bool has_second_line = second_sector.len2() > eps;
    bool lines_cross = has_first_line && has_second_line && (line{first_sector}.get_vector() * line{second_sector}.get_vector()).len2() > eps;

    const auto& add_first_point = [&](const point& p) {
        if (first_sector.contains(p)) {
            return p;
        }
        return first_sector.get_first_point();
    };
    const auto& add_second_point = [&](const point& p) {
        if (second_sector.contains(p)) {
            return p;
        }
        return second_sector.get_first_point();
    };
    const auto& crooss_point = [&](bool first) {
        if (first) {
            if (lines_cross) {
                return add_first_point(impl::closest_point_on_cross_lines(line{first_sector}, line{second_sector}).first);
            }
            return first_sector.get_first_point();
        }
        if (lines_cross) {
            return add_second_point(impl::closest_point_on_cross_lines(line{first_sector}, line{second_sector}).second);
        }
        return second_sector.get_first_point();
    };

    std::array<point, 5> first_sector_interested_points{
        first_sector.get_first_point(), 
        first_sector.get_second_point(),
        crooss_point(true),
        has_first_line ? add_first_point(projection(line{first_sector}, second_sector.get_first_point())) : first_sector.get_first_point(),
        has_first_line ? add_first_point(projection(line{first_sector}, second_sector.get_second_point())) : first_sector.get_first_point()
    };
    std::array<point, 5> second_sector_interested_points{
        second_sector.get_first_point(), 
        second_sector.get_second_point(),
        crooss_point(false),
        has_second_line ? add_second_point(projection(line{second_sector}, first_sector.get_first_point())) : second_sector.get_first_point(),
        has_second_line ? add_second_point(projection(line{second_sector}, first_sector.get_second_point())) : second_sector.get_first_point()
    };

    scalar_type res = std::numeric_limits<scalar_type>::infinity();
    for (const auto& p1 : first_sector_interested_points) {
        for (const auto& p2 : second_sector_interested_points) {
            res = std::min(res, (p1 - p2).len());
        }
    }

    return res;
}

} // namespace geom
