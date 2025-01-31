#pragma once

#include "geom/sector.h"

#include <ranges>

namespace geom::test
{

template<std::floating_point scalar_type>
scalar_type distance(const Sector_3D<scalar_type>& first_sector, 
                     const Sector_3D<scalar_type>& second_sector) 
{
    static constexpr int steps_count = 50;
    using point = Point_3D<scalar_type>;
    auto get_first_point = 
        [p = first_sector.get_first_point(), 
         v = first_sector.get_second_point() - first_sector.get_first_point()](auto t) 
    {
        return p + t * v;
    };
    

    scalar_type min_t = 0.;
    scalar_type max_t = 1.;
    
    scalar_type left_dist_to_second_sector, right_dist_to_second_sector;

    const auto& calc_dist_to_second_sector = [&](const point& p) {
        auto get_second_point = 
            [p = second_sector.get_first_point(), 
             v = second_sector.get_second_point() - second_sector.get_first_point()](auto u) 
        {
            return p + u * v;
        };
        scalar_type min_u = 0.;
        scalar_type max_u = 1.;

        scalar_type left_dist_to_point, right_dist_to_point;
        for (int it : std::views::iota(0, steps_count)) {
            scalar_type delta = (max_u - min_u) / 3.;
            scalar_type left_u = min_u + delta;
            scalar_type right_u = min_u + 2. * delta;

            auto left_p = get_second_point(left_u);
            auto right_p = get_second_point(right_u);
            left_dist_to_point = (left_p - p).len2();
            right_dist_to_point = (right_p - p).len2();

            if (left_dist_to_point < right_dist_to_point) {
                max_u = right_u;
            } else {
                min_u = left_u;
            }
        }

        return std::min(left_dist_to_point, right_dist_to_point);
    };

    for (int it : std::views::iota(0, steps_count)) {
        scalar_type delta = (max_t - min_t) / 3.;
        scalar_type left_t = min_t + delta;
        scalar_type right_t = min_t + 2. * delta;
        auto left_p = get_first_point(left_t);
        auto right_p = get_first_point(right_t);

        left_dist_to_second_sector = calc_dist_to_second_sector(left_p);
        right_dist_to_second_sector = calc_dist_to_second_sector(right_p);

        if (left_dist_to_second_sector < right_dist_to_second_sector) {
            max_t = right_t;
        } else {
            min_t = left_t;
        }
    }

    auto left_p = get_first_point(min_t);
    return std::sqrt(std::min(left_dist_to_second_sector, right_dist_to_second_sector));
}
} // namespace geom::test
