#include <gtest/gtest.h>

#include <geom/vector.h>
#include <geom/basic_algorithm.h>



template <typename T>
class GeomTest : public testing::Test {
public:
    using scalar_type = T;
    using point = geom::Point_3D<scalar_type>;
    using vector = geom::Vector_3D<scalar_type>;
private:
    static constexpr scalar_type eps_value() {
        if constexpr (std::is_same_v<scalar_type, float>) {
            return 1.e-4f;
        }
        if constexpr (std::is_same_v<scalar_type, double>) {
            return 1.e-5;
        }
    }
public:
    static constexpr scalar_type eps = eps_value();

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
    EXPECT_NEAR(length, v.dist(), TestFixture::eps);
    EXPECT_NEAR(std::pow(length, 2.), v.dist2(), TestFixture::eps);
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
}
