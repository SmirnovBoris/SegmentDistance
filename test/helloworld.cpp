#include <gtest/gtest.h>

#include <geom/vector.h>



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

    static void expect_vector_eq(const vector& l, vector& r) {
        EXPECT_NEAR(l.get_x(), r.get_x(), eps);
        EXPECT_NEAR(l.get_y(), r.get_y(), eps);
        EXPECT_NEAR(l.get_z(), r.get_z(), eps);
    }
};

using MyTypes = ::testing::Types<float, double>;
TYPED_TEST_SUITE(GeomTest, MyTypes);


TYPED_TEST(GeomTest, Basics) {
    geom::Point_3D<float> p{ 1., 2., 3. };
    EXPECT_NEAR(1.f, p.get_x(), TestFixture::eps);
    EXPECT_NEAR(2.f, p.get_y(), TestFixture::eps);
    EXPECT_NEAR(3.f, p.get_z(), TestFixture::eps);

    geom::Vector_3D<float> v{ 10., -20., 30. };
    EXPECT_NEAR(10.f, v.get_x(), TestFixture::eps);
    EXPECT_NEAR(-20.f, v.get_y(), TestFixture::eps);
    EXPECT_NEAR(30.f, v.get_z(), TestFixture::eps);

    typename TestFixture::scalar_type length = 37.416573867739;
    EXPECT_NEAR(length, v.dist(), TestFixture::eps);
    EXPECT_NEAR(std::pow(length, 2.), v.dist2(), TestFixture::eps);
}


TYPED_TEST(GeomTest, Vector) {
    typename TestFixture::vector a{ 0., 1., 2. };
    typename TestFixture::vector b{ 0.f + TestFixture::eps / 2.f, 1.f - TestFixture::eps / 2.f, 2.f };
    typename TestFixture::vector c{ 100., 1., 2. };

    TestFixture::expect_vector_eq(a, b);
    EXPECT_TRUE(geom::vector_eq<typename TestFixture::scalar_type>(a, b, TestFixture::eps));
    EXPECT_FALSE(geom::vector_eq<typename TestFixture::scalar_type>(a, c, TestFixture::eps));
    EXPECT_FALSE(geom::vector_eq<typename TestFixture::scalar_type>(b, c, TestFixture::eps));
}
