#ifndef TEXTUREFIELD_H
#define TEXTUREFIELD_H

#include <vector>
#include <algorithm>

#include "PanelElement.h"
#include "MyTexture.h"

class TextureField : public PanelElement {
private:
    std::vector<MyTexture> textureList;

public:
    TextureField(int _height, int _width, Vector2 _position);
    TextureField(const Texture &texture, int _height, int _width, Vector2 _position); 
    void addTexture(const MyTexture &mTexture);
    void removeTexture(const MyTexture &mTexture);
    void draw() const override;
    void handleInput() override; 
    void getBoundingBox(float& x, float& y, float& width, float& height) const override;
};

#endif // TEXTUREFIELD_H