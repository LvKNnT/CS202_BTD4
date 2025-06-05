#include "Button.h"

Button::Button(const Texture &_texture, std::string _title) {
    texture = _texture;
    title = _title;
}

void Button::onClick(float x, float y) {
    std::cout<<"Button Clicked\n";
}

void Button::draw() const {
    DrawTexture(texture, position.x, position.y, WHITE);

    int textWidth = MeasureText(title.c_str(), 20); // I don't know what's font size, so I use 20 
    int textX = position.x + (texture.width - textWidth) / 2;
    int textY = position.y + (texture.height - 20) / 2; // 20 is font size
    DrawText(title.c_str(), textX, textY, 20, BLACK);
}
