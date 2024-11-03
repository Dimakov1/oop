#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <memory>
#include <cmath>
#include <iostream>

template <Scalar T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[4];
public:
    Rhombus(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        vertices[0] = std::make_unique<Point<T>>(a);
        vertices[1] = std::make_unique<Point<T>>(b);
        vertices[2] = std::make_unique<Point<T>>(c);
        vertices[3] = std::make_unique<Point<T>>(d);
    }

    Rhombus(const Rhombus& other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
        return *this;
    }

    Rhombus(Rhombus&& other) noexcept {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        return *this;
    }

    T area() const override {
        T d1 = std::sqrt(std::pow(vertices[0]->x - vertices[2]->x, 2) + std::pow(vertices[0]->y - vertices[2]->y, 2));
        T d2 = std::sqrt(std::pow(vertices[1]->x - vertices[3]->x, 2) + std::pow(vertices[1]->y - vertices[3]->y, 2));
        return (d1 * d2) / 2;
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
        return std::make_unique<Rhombus<T>>(*this);
    }

    static Rhombus input() {
        T x1, y1, x2, y2, x3, y3, x4, y4;
        std::cout << "Введите координаты четырех точек ромба (x y): ";
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        return Rhombus(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3), Point<T>(x4, y4));
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& in, Rhombus<U>& rhombus);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Rhombus<U>& rhombus);
};

template <typename T>
std::istream& operator>>(std::istream& in, Rhombus<T>& rhombus) {
    T x1, y1, x2, y2, x3, y3, x4, y4;
    in >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    rhombus = Rhombus<T>(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3), Point<T>(x4, y4));
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Rhombus<T>& rhombus) {
    for (const auto& vertex : rhombus.vertices)
        out << *vertex << " ";
    return out;
}

#endif
