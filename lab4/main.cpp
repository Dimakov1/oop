#include <iostream>
#include "include/Array.h"
#include "include/Trapezoid.h"
#include "include/Rhombus.h"
#include "include/Pentagon.h"

int main() {
    Array<Figure<double>> shapes;

    shapes.add(std::make_shared<Trapezoid<double>>(Trapezoid<double>::input()));

    shapes.add(std::make_shared<Rhombus<double>>(Rhombus<double>::input()));

    shapes.add(std::make_shared<Pentagon<double>>(Pentagon<double>::input()));

    std::cout << "\nИнформация обо всех фигурах:\n";
    shapes.printAll();
    std::cout << "Общая площадь всех фигур: " << shapes.totalArea() << std::endl;

    return 0;
}
