#ifndef TEXTUREFIELD_H
#define TEXTUREFIELD_H

#include <vector>
#include <algorithm>

#include "PanelElement.h"
#include "MyTexture.h"

class TextureField : public PanelElement {
protected:
    std::vector<MyTexture> textureList;

public:
    TextureField(int _height, int _width, Vector2 _position);
    TextureField(const Texture &texture, int _height, int _width, Vector2 _position); 
    void addTexture(const MyTexture &mTexture);
    void removeTexture(const MyTexture &mTexture);
    void draw() const override;
    void draw(int idx, float rotation) const;
    void handleInput() override; 
    void setTexture(const Texture &newTexture, int idx = 0);
};

class MovableTextureField : public TextureField {
public:
    MovableTextureField(const Texture &texture, int _height, int _width);
    void handleInput() override;
    void setTexture(const Texture &_texture, int idx);
    void drawRangeCircle(float range, Color color);

};

#endif // TEXTUREFIELD_H