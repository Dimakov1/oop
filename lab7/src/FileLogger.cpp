#include "FileLogger.h"
#include <fstream>

FileLogger::FileLogger(const std::string& filename) : filename(filename) {}

void FileLogger::update(const std::string& event) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << event << std::endl;
        file.close();
    }
}
