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
    TextField(const std::string& _text, const Font& _font, const Color& _color, int _height, int _width, Vector2 _position);
    void setText(const std::string& newText);
    void draw() const override;
    void handleInput() override; 
    void getBoundingBox(float& x, float& y, float& width, float& height) const override;
};

#endif // TEXTFIELD_H