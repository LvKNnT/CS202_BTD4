#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>

#include "IObserver.h"

class ISubject {
public:
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify(Event::Type event) = 0;
};

#endif // ISUBJECT