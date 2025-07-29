#ifndef TICK_HOVERING_BUTTON_H
#define TICK_HOVERING_BUTTON_H

#include "Button.h"

class TickHoveringButton : public Button {
protected:
    bool isTick;
    Event::Type tickEvent;
    Event::Type untickEvent;
public:
    TickHoveringButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
    void draw() const override;
};

class FastForward : public TickHoveringButton {
public:
    FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class StartRoundButton : public TickHoveringButton {
public:
    StartRoundButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

#endif // TICK_HOVERING_BUTTON_H