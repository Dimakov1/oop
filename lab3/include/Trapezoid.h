#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <memory>
#include <cmath>
#include <iostream>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[4];
public:
    Trapezoid(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        vertices[0] = std::make_unique<Point<T>>(a);
        vertices[1] = std::make_unique<Point<T>>(b);
        vertices[2] = std::make_unique<Point<T>>(c);
        vertices[3] = std::make_unique<Point<T>>(d);
    }

    Trapezoid(const Trapezoid& other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
        return *this;
    }

    Trapezoid(Trapezoid&& other) noexcept {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        return *this;
    }

    T area() const override {
        T height = std::abs(vertices[0]->y - vertices[2]->y);
        T base1 = std::abs(vertices[1]->x - vertices[0]->x);
        T base2 = std::abs(vertices[3]->x - vertices[2]->x);
        return (base1 + base2) * height / 2;
    }

    Point<T> center() const override {
        T x = 0, y = 0;
        for (const auto& vertex : vertices) {
            x += vertex->x;
            y += vertex->y;
        }
        return Point<T>(x / 4, y / 4);
    }

    void printVertices() const override {
        for (const auto& vertex : vertices)
            std::cout << *vertex << " ";
        std::cout << std::endl;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapezoid<T>>(*this);
    }

    static Trapezoid input() {
        T x1, y1, x2, y2, x3, y3, x4, y4;
        std::cout << "Введите координаты четырех точек трапеции (x y): ";
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        return Trapezoid(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3), Point<T>(x4, y4));
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& in, Trapezoid<U>& trapezoid);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Trapezoid<U>& trapezoid);
};

template <typename T>
std::istream& operator>>(std::istream& in, Trapezoid<T>& trapezoid) {
    T x1, y1, x2, y2, x3, y3, x4, y4;
    in >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    trapezoid = Trapezoid<T>(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3), Point<T>(x4, y4));
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Trapezoid<T>& trapezoid) {
    for (const auto& vertex : trapezoid.vertices)
        out << *vertex << " ";
    return out;
}

#endif
