#include "TextureField.h"

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
        mTexture.draw();
    }
}
