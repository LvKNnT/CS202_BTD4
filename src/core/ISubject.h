#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include <list>
#include "IObserver.h"

class ISubject {
protected:
    std::list<std::shared_ptr<IObserver>> observers;
public:
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify(Event::Type event) = 0;
};

#endif // ISUBJECT