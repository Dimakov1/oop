#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include <string>
#include "IObserver.h"

class Subject {
public:
    void attach(std::shared_ptr<IObserver> observer);
    void notify(const std::string& event);
    virtual ~Subject() = default;

private:
    std::vector<std::shared_ptr<IObserver>> observers;
};

#endif 
