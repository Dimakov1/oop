#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "IObserver.h"

class ConsoleLogger : public IObserver {
public:
    void update(const std::string& event) override;
};

#endif
