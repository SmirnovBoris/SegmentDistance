#pragma once

#include <concepts> 

namespace geom
{

template<std::floating_point scalar_type>
struct scalar_type_epsilon {
};

template<>
struct scalar_type_epsilon<float> {
    static constexpr float value = 1e-4f;
};

template<>
struct scalar_type_epsilon<double> {
    static constexpr double value = 1e-6;
};

template<std::floating_point scalar_type>
constexpr scalar_type epsilon = scalar_type_epsilon<scalar_type>::value;

} // namespace geom
