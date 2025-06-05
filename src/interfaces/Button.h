#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <iostream>

#include "Clickable.h"
#include "PanelElement.h"

class Button : public Clickable, public PanelElement {
private:
    Texture texture;
    std::string title;

public:
    Button(const Texture &_texture, std::string _title);
    void onClick(float x, float y) override;
    void draw() const override;
};

#endif // BUTTON_H