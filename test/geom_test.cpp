#include <gtest/gtest.h>

#include <geom/vector.h>
#include <geom/basic_algorithm.h>
#include <geom/distance.h>

#include <numeric>

#include "test_algorithm.h"


template <typename T>
class GeomTest : public testing::Test {
public:
    using scalar_type = T;
    using point = geom::Point_3D<scalar_type>;
    using vector = geom::Vector_3D<scalar_type>;
    using line = geom::Line_3D<scalar_type>;
    using sector = geom::Sector_3D<scalar_type>;
    static constexpr scalar_type eps = geom::epsilon<scalar_type>;

    static void expect_vector_eq(const vector& l, const vector& r) {
        EXPECT_NEAR(l.get_x(), r.get_x(), eps);
        EXPECT_NEAR(l.get_y(), r.get_y(), eps);
        EXPECT_NEAR(l.get_z(), r.get_z(), eps);
    }

    static void expect_point_eq(const point& l, const point& r) {
        EXPECT_NEAR(l.get_x(), r.get_x(), eps);
        EXPECT_NEAR(l.get_y(), r.get_y(), eps);
        EXPECT_NEAR(l.get_z(), r.get_z(), eps);
    }

    static std::vector<point> gen_points(scalar_type from, scalar_type to) {
        std::vector<point> points;
        for (scalar_type x = from; x < to; x += 1.) {
            for (scalar_type y = from; y < to; y += 1.) {
                for (scalar_type z = from; z < to; z += 1.) {
                    points.push_back(point{x, y, z});
                }
            }
        }
        return points;
    }

    static std::vector<point> gen_points_sorted(scalar_type from, scalar_type to) {
        std::vector<point> points;
        for (scalar_type x = from; x < to; x += 1.) {
            for (scalar_type y = x; y < to; y += 1.) {
                for (scalar_type z = y; z < to; z += 1.) {
                    points.push_back(point{x, y, z});
                }
            }
        }
        return points;
    }

    static std::vector<sector> gen_sectors(scalar_type from, scalar_type to) {
        std::vector<sector> sectors;
        auto points = gen_points(from, to);
        for (auto a : points) {
            for (auto b : points) {
                sectors.push_back(sector{a, b});
            }
        }
        return sectors;
    }

    static std::vector<sector> gen_sectors_sorted(scalar_type from, scalar_type to) {
        std::vector<sector> sectors;
        auto points = gen_points(from, to);
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i; j < points.size(); ++j) {
                sectors.push_back(sector{points[i], points[j]});
            }
        }
        return sectors;
    }
};

using MyTypes = ::testing::Types<float, double>;
TYPED_TEST_SUITE(GeomTest, MyTypes);


TYPED_TEST(GeomTest, Basics) {
    using point =  typename TestFixture::point; 
    using vector =  typename TestFixture::vector; 
    using scalar_type =  typename TestFixture::scalar_type; 
    point p{ 1., 2., 3. };
    EXPECT_NEAR(1.f, p.get_x(), TestFixture::eps);
    EXPECT_NEAR(2.f, p.get_y(), TestFixture::eps);
    EXPECT_NEAR(3.f, p.get_z(), TestFixture::eps);

    vector v{ 10., -20., 30. };
    EXPECT_NEAR(10.f, v.get_x(), TestFixture::eps);
    EXPECT_NEAR(-20.f, v.get_y(), TestFixture::eps);
    EXPECT_NEAR(30.f, v.get_z(), TestFixture::eps);

    scalar_type length = 37.416573867739;
    EXPECT_NEAR(length, v.len(), TestFixture::eps);
    EXPECT_NEAR(std::pow(length, 2.), v.len2(), TestFixture::eps);
}


TYPED_TEST(GeomTest, Vector) {
    using vector =  typename TestFixture::vector; 
    using scalar_type =  typename TestFixture::scalar_type; 
    vector a{ 0., 1., 2. };
    vector b{ 0.f + TestFixture::eps / 2.f, 1.f - TestFixture::eps / 2.f, 2.f };
    vector c{ 100., 1., 2. };

    TestFixture::expect_vector_eq(a, b);
    EXPECT_TRUE(geom::vector_eq<scalar_type>(a, b, TestFixture::eps));
    EXPECT_FALSE(geom::vector_eq<scalar_type>(a, c, TestFixture::eps));
    EXPECT_FALSE(geom::vector_eq<scalar_type>(b, c, TestFixture::eps));
}


TYPED_TEST(GeomTest, CrossProduct) {
    using vector =  typename TestFixture::vector; 
    vector ox{ 1., 0., 0. };
    vector oy{ 0., 1., 0. };
    vector oz{ 0., 0., 1. };

    TestFixture::expect_vector_eq(geom::cross_product(ox, oy), oz);
    TestFixture::expect_vector_eq(geom::cross_product(ox, ox), vector::zero());
}

TYPED_TEST(GeomTest, BasicAlgs) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point; 
    point a{ 1., 0., 0. };
    point b{ 0., 1., 0. };
    vector v = b - a;

    TestFixture::expect_vector_eq(v, vector{-1., 1., 0.});
    TestFixture::expect_point_eq(a + v, b);

    vector w{1., 0., 0.};
    vector p{2., 0., 0.};
    TestFixture::expect_vector_eq(w * 2., p);
    TestFixture::expect_vector_eq(p.normalized(), w);
}

TYPED_TEST(GeomTest, DistanceLine) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point;
    using line =  typename TestFixture::line;

    line l1(point{0., 0., 0.}, {1., 0., 0.});
    line l2(point{0., 0., 0.}, {0., 1., 0.});

    const auto& [p1, p2] = geom::impl::closest_point_on_cross_lines(l1, l2);

    TestFixture::expect_point_eq(p1, point{0., 0., 0.});
    TestFixture::expect_point_eq(p2, point{0., 0., 0.});

    line l3{point{-1., 0., -1.}, {1., 0., -1.}};
    line l4{point{0., -1., 1.}, {0., 1., 1.}};

    const auto& [p3, p4] = geom::impl::closest_point_on_cross_lines(l3, l4);

    TestFixture::expect_point_eq(p3, point{0., 0., -1.});
    TestFixture::expect_point_eq(p4, point{0., 0., 1.});
}

TYPED_TEST(GeomTest, DistanceSector) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point;
    using sector =  typename TestFixture::sector;

    sector a{point{0., 0., 0.}, point{1., 0., 0.}};
    sector b{point{0., 0., 0.}, point{0., 1., 0.}};

    EXPECT_NEAR(0.f, geom::distance(a, b), TestFixture::eps);
}

TYPED_TEST(GeomTest, DistanceAllPointsInSmallCube) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point;
    using sector =  typename TestFixture::sector;

    auto sectors = TestFixture::gen_sectors(-1., 1.);
    for (auto a : sectors) {
        for (auto b : sectors) {
            auto dist = geom::distance(a, b);
            auto calc_dist = geom::test::distance(a, b);
            EXPECT_NEAR(dist, calc_dist, TestFixture::eps);
        }
    }
}

TYPED_TEST(GeomTest, DistanceOneStaticSector) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point;
    using sector =  typename TestFixture::sector;
    using scalar_type = typename TestFixture::scalar_type;

    auto sectors = TestFixture::gen_sectors(-2., 3.);
    for (scalar_type len : {0., .5, 2., 3., 5., 10.}) {
        sector b{point{-len, 0., 0.}, point{len, 0., 0.}};
        for (auto a : sectors) {
            auto dist = geom::distance(a, b);
            auto calc_dist = geom::test::distance(a, b);
            EXPECT_NEAR(dist, calc_dist, TestFixture::eps);
        }
    }
}

TYPED_TEST(GeomTest, DistanceOneStaticSectorSorted) {
    using vector =  typename TestFixture::vector; 
    using point =  typename TestFixture::point;
    using sector =  typename TestFixture::sector;
    using scalar_type = typename TestFixture::scalar_type;

    auto sectors = TestFixture::gen_sectors_sorted(-3., 4.);
    for (scalar_type len : {0., .5, 5., 10.}) {
        sector b{point{-len, 0., 0.}, point{len, 0., 0.}};
        for (auto a : sectors) {
            auto dist = geom::distance(a, b);
            auto calc_dist = geom::test::distance(a, b);
            EXPECT_NEAR(dist, calc_dist, TestFixture::eps);
        }
    }
}
