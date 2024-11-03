#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <concepts>

template <class T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& out, const Point<U>& point) {
        out << "(" << point.x << ", " << point.y << ")";
        return out;
    }
};

#endif
