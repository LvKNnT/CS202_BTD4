#include "TextField.h"

TextField::TextField(const std::string& _text, const Font& _font, const Color& _color, int _index, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position), text(_text), font(_font), color(_color) {
}

void TextField::setText(const std::string &newText) {
    text = newText;
}

void TextField::draw() const {
    
}