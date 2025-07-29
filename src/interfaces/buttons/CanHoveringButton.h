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


class StandardModeButton : public ModeButton {
public:
    StandardModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class AlternateBloonsModeButton : public ModeButton {
public:
    AlternateBloonsModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ReverseModeButton : public ModeButton {
public:
    ReverseModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ApopalyseModeButton : public ModeButton {
public:
    ApopalyseModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

// Tower buttons

class ChooseBombTower : public CanHoveringButton {
public:
    ChooseBombTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseDartMonkeyTower : public CanHoveringButton {
public:
    ChooseDartMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

#endif // CAN_HOVERING_BUTTON_H