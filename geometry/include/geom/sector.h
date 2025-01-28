#pragma once

namespace geom {

template<class point_type>
class Sector {
public:
    Sector(const point_type& a, const point_type& b) 
        : a{a}
        , b{b}
    {}
    point_type get_first_point() const {
        return a;
    }
    point_type get_second_point() const {
        return b;
    }
private:
    point_type a, b;
};

} // namepace geom
