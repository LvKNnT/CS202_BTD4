#ifndef TICK_BUTTON_H
#define TICK_BUTTON_H

#include "Button.h"

// Tick Buttons
class Tick : public Button {
protected:
    bool isTick;
    Event::Type tickEvent;
    Event::Type untickEvent;
    Event::Type hoveringEvent;
public: 
    Tick(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class AutoNextRound : public Tick {
public:
    AutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

#endif // TICK_BUTTON_H
