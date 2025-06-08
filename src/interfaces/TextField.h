#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <string>
#include "PanelElement.h"

class TextField : public PanelElement {
private:
    std::string text;
    Font font;
    Color color;

public:
    TextField(const std::string& _text, const Font& _font, const Color& _color, int _index, int _height, int _width, Vector2 _position);
    void setText(const std::string& newText);
    void draw() const override; 
};

#endif // TEXTFIELD_H