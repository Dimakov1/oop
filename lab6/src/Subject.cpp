#include "Subject.h"

void Subject::attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

void Subject::notify(const std::string& event) {
    for (auto& observer : observers) {
        observer->update(event);
    }
}
