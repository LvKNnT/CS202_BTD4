#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "raylib.h"

class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void draw() const = 0;

};

class HitBox {
public:
    virtual Rectangle getBoundingBox() const = 0;
};

#endif // DRAWABLE_H