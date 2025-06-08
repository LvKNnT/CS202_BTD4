#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <string>

#include "PanelElement.h"

class InputField : public PanelElement {
private:
    int maxLength;
    std::string text;

public:
    InputField(int _maxLength, const std::string &_text, int _index, int _height, int _width, Vector2 _position);
    void setText(const std::string &newText);
    std::string getText() const;
    void draw() const override;
};

#endif // INPUTFIELD_H