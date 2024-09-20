#include <gtest/gtest.h>
#include "../include/calculator.h"

TEST(test_01, basic_test_set) {
    EXPECT_EQ(box_capacity(32, 64, 16), 13824); 
}

TEST(test_02, basic_test_set) {
    EXPECT_EQ(box_capacity(32, 64, 15), 12672); 
}

TEST(test_03, basic_test_set) {
    EXPECT_EQ(box_capacity(16, 16, 16), 1728);
}

TEST(test_04, basic_test_set) {
    EXPECT_EQ(box_capacity(64, 64, 32), 55296);
}

TEST(test_05, basic_test_set) {
    EXPECT_EQ(box_capacity(0, 16, 16), 0);
}

TEST(test_06, basic_test_set) {
    EXPECT_EQ(box_capacity(20, 35, 12), 3510);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}