#include "MyTexture.h"

MyTexture::MyTexture(const Texture &_texture, Vector2 _position) {
    texture = _texture;
    position = _position;
}

void MyTexture::draw() const {
    DrawTexture(texture, position.x, position.y, WHITE);
}

bool MyTexture::operator==(const MyTexture &other) {
    return texture.id == other.texture.id;
}
