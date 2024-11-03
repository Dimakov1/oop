#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>

template <Scalar T>
class Figure {
public:
    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    virtual void printVertices() const = 0;
    virtual ~Figure() = default;

    explicit operator double() const { return static_cast<double>(area()); }
    bool operator==(const Figure& other) const { return this->area() == other.area(); }
    virtual std::unique_ptr<Figure> clone() const = 0;
};

#endif
