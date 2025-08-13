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

class ChooseBombShooterTower : public CanHoveringButton {
public:
    ChooseBombShooterTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseDartMonkeyTower : public CanHoveringButton {
public:
    ChooseDartMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseNinjaMonkeyTower : public CanHoveringButton {
public:
    ChooseNinjaMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseSniperMonkeyTower : public CanHoveringButton {
public:
    ChooseSniperMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseBoomerangMonkeyTower : public CanHoveringButton {
public:
    ChooseBoomerangMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseTackShooterTower : public CanHoveringButton {
public:
    ChooseTackShooterTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};
#endif // CAN_HOVERING_BUTTON_H