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
    void update() override;
};

class AutoNextRound : public Tick {
public:
    AutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void update() override;
};

class MuteSound : public Tick {
public:
    MuteSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class MuteMusic : public Tick {
public:
    MuteMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class Jiggle : public Tick {
public:
    Jiggle(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};
#endif // TICK_BUTTON_H
