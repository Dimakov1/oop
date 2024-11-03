#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include <iostream>
#include "Figure.h"

template <class T>
class Array {
private:
    std::vector<std::shared_ptr<T>> data;
public:
    void add(std::shared_ptr<T> figure) {
        data.push_back(std::move(figure));
    }

    void remove(size_t index) {
        if (index < data.size()) data.erase(data.begin() + index);
    }

    double totalArea() const {
        double area = 0;
        for (const auto& figure : data)
            area += static_cast<double>(*figure);
        return area;
    }

    void printAll() const {
        for (const auto& figure : data) {
            figure->printVertices();
            std::cout << "Area: " << figure->area() << ", Center: (" << figure->center().x << ", " << figure->center().y << ")\n";
        }
    }
};

#endif
