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
    TextField(const std::string& initialText, const Font& font, const Color& color);
    void setText(const std::string& newText);
};

#endif // TEXTFIELD_H