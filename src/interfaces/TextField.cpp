#include "TextField.h"

TextField::TextField(const std::string &initialText, const Font &font, const Color &color) 
    : text(initialText), font(font), color(color) {
}

void TextField::setText(const std::string &newText)
{
    text = newText;
}