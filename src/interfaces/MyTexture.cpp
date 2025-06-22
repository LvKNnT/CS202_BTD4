#include "MyTexture.h"

MyTexture::MyTexture(const Texture &_texture, Vector2 _position) {
    texture = _texture;
    position = _position;
}

void MyTexture::draw(int height, int width) const {
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float textWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - textWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, WHITE);
}

void MyTexture::draw() const {
    DrawTextureEx(texture, position, 0.0f, 1.0, WHITE);
}
bool MyTexture::operator==(const MyTexture &other) {
    return texture.id == other.texture.id;
}
