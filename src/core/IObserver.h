#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Event.h"

class IObserver {
public:
    virtual void update(Event::Type event) = 0;
    virtual void initialize() = 0;
    virtual void draw() const = 0;
    virtual void handleInput() = 0;
};

#endif // IOBSERVER_H