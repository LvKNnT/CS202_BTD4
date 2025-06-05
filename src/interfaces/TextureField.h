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
    TextureField();
    void addTexture(const MyTexture &mTexture);
    void removeTexture(const MyTexture &mTexture);
    void draw() const override;
};

#endif // TEXTUREFIELD_H