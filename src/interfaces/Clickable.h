#ifndef CLICKABLE_H
#define CLICKABLE_H

class Clickable {
public:
    virtual ~Clickable() = default;

    virtual void onClick() = 0;
    virtual bool isClicked() const = 0;

    virtual void getBoundingBox(float& x, float& y, float& width, float& height) const = 0;
};

#endif // CLICKABLE_H
