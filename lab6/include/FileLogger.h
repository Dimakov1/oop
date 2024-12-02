#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <string>
#include "IObserver.h"

class FileLogger : public IObserver {
public:
    FileLogger(const std::string& filename);
    void update(const std::string& event) override;

private:
    std::string filename;
};

#endif 
