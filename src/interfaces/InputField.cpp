#include "InputField.h"

InputField::InputField(int _maxLength, const std::string &_text, int _index, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position), maxLength(_maxLength), text(_text) {
}

void InputField::setText(const std::string &newText) {
    text = newText; 
}

std::string InputField::getText() const {
    return text;
}

void InputField::draw() const {
    
}