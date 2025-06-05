#include "InputField.h"

InputField::InputField(const int _maxLength, const std::string &_text)
    : maxLength(_maxLength), text(_text) {
    if (text.length() > maxLength) {
        text = text.substr(0, maxLength);
    }
}

void InputField::setText(const std::string &newText) {
    text = newText; 
}

std::string InputField::getText() const {
    return text;
}