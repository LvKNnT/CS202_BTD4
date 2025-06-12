#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void draw() const = 0;

};

class Hixbox {
public:
    virtual Rectangle getBoundingBox(float& x, float& y, float& width, float& height) const = 0;
};

#endif // DRAWABLE_H