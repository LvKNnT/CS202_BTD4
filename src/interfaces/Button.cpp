#include "Button.h"

Button::Button(const Texture &_texture, std::string _title, int _fontSize, int _index, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position), texture(_texture), title(_title), fontSize(_fontSize) {

    if (texture.id == 0) {
        std::cerr << "Error:Cannot load Texture\n";
    }
}

void Button::onClick(float x, float y) {
    std::cout<<"Button Clicked\n";
}

void Button::draw() const {
    DrawTexture(texture, position.x, position.y, WHITE);

    int textWidth = MeasureText(title.c_str(), fontSize);  
    int textX = position.x + (texture.width - textWidth) / 2;
    int textY = position.y + (texture.height - fontSize) / 2; 
    DrawText(title.c_str(), textX, textY, fontSize, BLACK);
}