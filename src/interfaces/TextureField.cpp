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
    for(auto &mTexture:textureList) {
        mTexture.draw(height, width);
    }
}

void TextureField::handleInput() {

}

void TextureField::getBoundingBox(float& x, float& y, float& width, float& height) const {

}