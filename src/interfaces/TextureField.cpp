#include "TextureField.h"

TextureField::TextureField(int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position) { 
}

TextureField::TextureField(const Texture &texture, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position) {
    textureList.push_back({texture, _position});
}

void TextureField::addTexture(const MyTexture &mTexture) {
    textureList.push_back(mTexture);
}

void TextureField::removeTexture(const MyTexture &mTexture) {
    auto it = std::find(textureList.begin(), textureList.end(), mTexture);
    if(it != textureList.end()) {
        textureList.erase(it);
    }
}

void TextureField::draw() const {
    if(!isAvailable) return;
    for(auto &mTexture:textureList) {
        mTexture.draw(height, width);
    }
}

void TextureField::setTexture(const Texture &newTexture, int idx) {
    textureList[idx].setTexture(newTexture);
}

void TextureField::draw(int idx, float rotation) const {
    if(!isAvailable) return;
    textureList[idx].draw(height, width, rotation);
}

void TextureField::update() {
    if(!isAvailable) return;
}
