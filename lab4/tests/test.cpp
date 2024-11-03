#include <gtest/gtest.h>
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"

TEST(TrapezoidTest, AreaTest) {
    Trapezoid<double> trapezoid(Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 3), Point<double>(1, 3));
    EXPECT_DOUBLE_EQ(trapezoid.area(), 9.0);
}

TEST(TrapezoidTest, CenterTest) {
    Trapezoid<double> trapezoid(Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 3), Point<double>(1, 3));
    Point<double> center = trapezoid.center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.5);
}

TEST(RhombusTest, AreaTest) {
    Rhombus<double> rhombus(Point<double>(1, 1), Point<double>(3, 3), Point<double>(5, 1), Point<double>(3, -1));
    EXPECT_DOUBLE_EQ(rhombus.area(), 8.0);
}

TEST(RhombusTest, CenterTest) {
    Rhombus<double> rhombus(Point<double>(1, 1), Point<double>(3, 3), Point<double>(5, 1), Point<double>(3, -1));
    Point<double> center = rhombus.center();
    EXPECT_DOUBLE_EQ(center.x, 3.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(PentagonTest, AreaTest) {
    std::array<Point<double>, 5> points = {Point<double>(0, 0), Point<double>(2, 0), Point<double>(3, 2), 
                                           Point<double>(1, 4), Point<double>(-1, 2)};
    Pentagon<double> pentagon(points);
    EXPECT_DOUBLE_EQ(pentagon.area(), 10.0);
}

TEST(PentagonTest, CenterTest) {
    std::array<Point<double>, 5> points = {Point<double>(0, 0), Point<double>(2, 0), Point<double>(3, 2), 
                                           Point<double>(1, 4), Point<double>(-1, 2)};
    Pentagon<double> pentagon(points);
    Point<double> center = pentagon.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
