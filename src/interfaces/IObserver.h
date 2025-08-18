#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Event.h"

class IObserver {
public:
    virtual void update(Event::Type event) = 0;
    virtual ~IObserver() = default;
};

#endif // IOBSERVER_H