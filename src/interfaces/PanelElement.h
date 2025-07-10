#ifndef PANELELEMENT_H
#define PANELELEMENT_H

#include <algorithm>

#include "raylib.h"
#include "Drawable.h"

class PanelElement : public Drawable {
protected:
    int index;
    int height;
    int width;
    Vector2 position;
    bool isAvailable;

public:
    PanelElement(int _height, int _width, Vector2 _position);
    void draw() const override;
    int getIndex() const;
    void setIndex(int _index);
    virtual void handleInput() = 0;
    void setAvailable(bool _isAvailable);
};

#endif // PANELELEMENT_H