#ifndef CAN_HOVERING_BUTTON_H
#define CAN_HOVERING_BUTTON_H

#include "Button.h"

// CanHovering Buttons
class CanHoveringButton : public Button {
public: 
    CanHoveringButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;

protected:
    Event::Type clickedEvent;
    Event::Type hoveringEvent;
};

class Info : public CanHoveringButton {
public:
    Info(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ModeButton : public CanHoveringButton {
public: 
    ModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};


class StandardMode : public ModeButton {
public:
    StandardMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class AlternateBloonsMode : public ModeButton {
public:
    AlternateBloonsMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ReverseMode : public ModeButton {
public:
    ReverseMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ApopalyseMode : public ModeButton {
public:
    ApopalyseMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

#endif // CAN_HOVERING_BUTTON_H