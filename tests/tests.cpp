#include "../include/Money.h"
#include <gtest/gtest.h>

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    EXPECT_EQ(m, Money("0.00"));
}

TEST(MoneyTest, SizeValueConstructor) {
    Money m(5, 9);
    EXPECT_EQ(m, Money("999.99"));
}

TEST(MoneyTest, InitializerListConstructor) {
    Money m = {1, 2, 3, 4, 5};
    EXPECT_EQ(m, Money("543.21"));
}

TEST(MoneyTest, StringConstructor) {
    Money m("123.45");
    EXPECT_EQ(m, Money("123.45"));

    Money m2("0.00");
    EXPECT_EQ(m2, Money("0.00"));

    Money m3("999999.99");
    EXPECT_EQ(m3, Money("999999.99"));
}

TEST(MoneyTest, CopyConstructor) {
    Money m1("123.45");
    Money m2 = m1;
    EXPECT_EQ(m1, m2);
}

TEST(MoneyTest, MoveConstructor) {
    Money m1("123.45");
    Money m2 = std::move(m1);
    EXPECT_EQ(m2, Money("123.45"));
    EXPECT_EQ(m1, Money("0.00"));
}

TEST(MoneyTest, AssignmentOperator) {
    Money m1("123.45");
    Money m2;
    m2 = m1;
    EXPECT_EQ(m1, m2);

    Money m3 = std::move(m1);
    EXPECT_EQ(m3, Money("123.45"));
    EXPECT_EQ(m1, Money("0.00"));
}

TEST(MoneyTest, AdditionOperator) {
    Money m1("123.45");
    Money m2("76.55");
    Money sum = m1 + m2;
    EXPECT_EQ(sum, Money("200.00"));
}

TEST(MoneyTest, SubtractionOperator) {
    Money m1("123.45");
    Money m2("76.55");
    Money diff = m1 - m2;
    EXPECT_EQ(diff, Money("46.90"));
}

TEST(MoneyTest, AdditionAssignmentOperator) {
    Money m1("123.45");
    Money m2("76.55");
    m1 += m2;
    EXPECT_EQ(m1, Money("200.00"));
}

TEST(MoneyTest, SubtractionAssignmentOperator) {
    Money m1("123.45");
    Money m2("76.55");
    m1 -= m2;
    EXPECT_EQ(m1, Money("46.90"));
}

TEST(MoneyTest, EqualityOperator) {
    Money m1("123.45");
    Money m2("123.45");
    EXPECT_TRUE(m1 == m2);

    Money m3("123.46");
    EXPECT_FALSE(m1 == m3);
}

TEST(MoneyTest, LessThanOperator) {
    Money m1("123.45");
    Money m2("123.46");
    EXPECT_TRUE(m1 < m2);

    Money m3("124.00");
    EXPECT_TRUE(m1 < m3);

    EXPECT_FALSE(m2 < m1);
}

TEST(MoneyTest, GreaterThanOperator) {
    Money m1("123.45");
    Money m2("123.44");
    EXPECT_TRUE(m1 > m2);

    Money m3("122.99");
    EXPECT_TRUE(m1 > m3);

    EXPECT_FALSE(m2 > m1);
}

TEST(MoneyTest, ZeroHandling) {
    Money m1("0.00");
    Money m2("0.00");
    EXPECT_EQ(m1, m2);

    Money m3("100.00");
    Money result = m3 - m3;
    EXPECT_EQ(result, Money("0.00"));
}

TEST(MoneyTest, LargeValues) {
    Money m1("999999.99");
    Money m2("0.01");
    Money result = m1 + m2;
    EXPECT_EQ(result, Money("1000000.00"));
}

TEST(MoneyTest, NegativeSubtraction) {
    Money m1("50.00");
    Money m2("100.00");

    try {
        Money result = m1 - m2;
        FAIL() << "Ожидалось исключение std::overflow_error";
    } catch (const std::overflow_error& e) {
        EXPECT_STREQ("Результат вычитания меньше нуля.", e.what());
    } catch (...) {
        FAIL() << "Ожидалось исключение std::overflow_error";
    }
}

TEST(MoneyTest, InvalidStringFormat) {
    try {
        Money m1("123.456");
        FAIL() << "Ожидалось исключение std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Неверный формат строки: слишком много знаков после точки.", e.what());
    } catch (...) {
        FAIL() << "Ожидалось исключение std::invalid_argument";
    }

    try {
        Money m2("abc.12");
        FAIL() << "Ожидалось исключение std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Неверный символ в строке.", e.what());
    } catch (...) {
        FAIL() << "Ожидалось исключение std::invalid_argument";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}