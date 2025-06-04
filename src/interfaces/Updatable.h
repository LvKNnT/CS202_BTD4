#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updatable {
public:
    virtual ~Updatable() = default;

    virtual void update(float deltaTime) = 0;

    virtual bool isActive() const = 0;
};

#endif // UPDATEABLE_H