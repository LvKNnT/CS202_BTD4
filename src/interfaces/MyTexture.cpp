#include "MyTexture.h"

MyTexture::MyTexture(const Texture &_texture, Vector2 _position) {
    texture = _texture;
    position = _position;
}

void MyTexture::draw(int height, int width, float rotation) const {
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, rotation, scale, WHITE);
}

void MyTexture::followMouse(int height, int width) {
    Vector2 mousePos = GetMousePosition();
    position = {mousePos.x - width / 2, mousePos.y - height / 2};
}

void MyTexture::setTexture(const Texture &_texture) {
    texture = _texture;
}

void MyTexture::drawRangeCircle(float range, Color color) {
    Vector2 mousePos = GetMousePosition();
    DrawCircle(mousePos.x, mousePos.y, range, color);
}

void MyTexture::draw() const {
    DrawTextureEx(texture, position, 0.0f, 1.0, WHITE);
}
bool MyTexture::operator==(const MyTexture &other) {
    return texture.id == other.texture.id;
}
