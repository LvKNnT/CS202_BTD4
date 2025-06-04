#ifndef CLICKABLE_H
#define CLICKABLE_H

class Clickable {
public:
    virtual ~Clickable() = default;

    virtual void onClick(float x, float y) = 0;
    virtual bool isClicked(float x, float y) const = 0;

    virtual void getBoundingBox(float& x, float& y, float& width, float& height) const = 0;
};

#endif // CLICKABLE_H
