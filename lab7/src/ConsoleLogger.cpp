#include "ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::update(const std::string& event) {
    std::cout << event << std::endl;
}
