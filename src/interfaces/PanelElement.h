#ifndef PANELELEMENT_H
#define PANELELEMENT_H

#include "raylib.h"
#include "Drawable.h"

class PanelElement : public Drawable {
protected:
    int index;
    int height;
    int width;
    Vector2 position;

public:
    PanelElement(int _index, int _height, int _width, Vector2 _position);
    void draw() const override = 0;
};

#endif // PANELELEMENT_H