#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <string>

#include "PanelElement.h"

class InputField : public PanelElement {
private:
    int maxLength;
    std::string text;

public:
    InputField(const int _maxLength, const std::string &_text);
    void setText(const std::string &newText);
    std::string getText() const;
};

#endif // INPUTFIELD_H