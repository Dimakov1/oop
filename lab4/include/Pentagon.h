#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <memory>
#include <array>
#include <iostream>

template <Scalar T>
class Pentagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[5];
public:
    Pentagon(const std::array<Point<T>, 5>& points) {
        for (size_t i = 0; i < 5; ++i)
            vertices[i] = std::make_unique<Point<T>>(points[i]);
    }

    Pentagon(const Pentagon& other) {
        for (int i = 0; i < 5; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 5; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
        return *this;
    }

    Pentagon(Pentagon&& other) noexcept {
        for (int i = 0; i < 5; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 5; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        return *this;
    }

    T area() const override {
        T area = 0;
        for (int i = 0; i < 5; i++) {
            int j = (i + 1) % 5;
            area += vertices[i]->x * vertices[j]->y - vertices[j]->x * vertices[i]->y;
        }
        return std::abs(area) / 2;
    }

    Point<T> center() const override {
        T x = 0, y = 0;
        for (const auto& vertex : vertices) {
            x += vertex->x;
            y += vertex->y;
        }
        return Point<T>(x / 5, y / 5);
    }

    void printVertices() const override {
        for (const auto& vertex : vertices)
            std::cout << *vertex << " ";
        std::cout << std::endl;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Pentagon<T>>(*this);
    }

    static Pentagon input() {
        T x, y;
        std::array<Point<T>, 5> points;
        std::cout << "Введите координаты пяти точек пятиугольника (x y): ";
        for (int i = 0; i < 5; ++i) {
            std::cin >> x >> y;
            points[i] = Point<T>(x, y);
        }
        return Pentagon(points);
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& in, Pentagon<U>& pentagon);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Pentagon<U>& pentagon);
};

template <typename T>
std::istream& operator>>(std::istream& in, Pentagon<T>& pentagon) {
    std::array<Point<T>, 5> points;
    T x, y;
    for (int i = 0; i < 5; ++i) {
        in >> x >> y;
        points[i] = Point<T>(x, y);
    }
    pentagon = Pentagon(points);
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Pentagon<T>& pentagon) {
    for (const auto& vertex : pentagon.vertices)
        out << *vertex << " ";
    return out;
}

#endif
