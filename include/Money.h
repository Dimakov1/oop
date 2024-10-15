#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <vector>
#include <string>

class Money {
public:
    Money();
    Money(const size_t& n, unsigned char t = 0);
    Money(const std::initializer_list<unsigned char>& t);
    Money(const std::string& str);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    ~Money() noexcept;

    Money& operator=(const Money& other);
    Money& operator=(Money&& other) noexcept;

    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    
    bool operator==(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;

    void print() const;

private:
    std::vector<unsigned char> digits;

    void fromString(const std::string& str);
    void removeLeadingZeros();
};

#endif