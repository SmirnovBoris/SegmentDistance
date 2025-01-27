#pragma once

namespace geom {

template<class scalar_type>
class Point_3D {

public:
    Point_3D(scalar_type x, scalar_type y, scalar_type z)
        : x{ x }
        , y{ y }
        , z{ z } 
    {}

    scalar_type dist2() const {
        return x * x + y * y + z * z;
    }

    const scalar_type& get_x() const { return x; }
    const scalar_type& get_y() const { return y; }
    const scalar_type& get_z() const { return z; }

private:
    scalar_type x, y, z;
};


} // namespace geom
