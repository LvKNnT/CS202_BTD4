#ifndef MYTEXTURE_H
#define MYTEXTURE_H

#include "raylib.h"

class MyTexture {
private:
    Texture texture;
    Vector2 position;

public:
    MyTexture(const Texture &_texture, Vector2 _position);
    void draw() const;

    bool operator == (const MyTexture &other);
};

#endif // MYTEXTURE_H