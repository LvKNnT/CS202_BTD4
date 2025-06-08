#include "TextureField.h"

TextureField::TextureField(int _index, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position) { 
}

void TextureField::removeTexture(const MyTexture &mTexture) {
    auto it = std::find(textureList.begin(), textureList.end(), mTexture);
    if(it != textureList.end()) {
        textureList.erase(it);
    }
}

void TextureField::draw() const {
    for(auto &mTexture:textureList) {
        mTexture.draw();
    }
}
