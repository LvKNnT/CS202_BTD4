#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <string>
#include "PanelElement.h"

class TextField : public PanelElement {
protected:
    std::string text;
    Font font;
    Color color;

    void formatText();
public:
    TextField(const std::string& _text, const Font& _font, const Color& _color, int _height, int _width, Vector2 _position);
    void setText(const std::string& newText);
    void setTextAndPos(const std::string &newText, Vector2 newPosition);
    void draw() const override;
    void handleInput() override; 
};

class MovableTextbox : public TextField {
public:
    MovableTextbox(const std::string& _text, const Font& _font, const Color& _color, int _height, int _width);
    void draw() const override;
};

#endif // TEXTFIELD_H