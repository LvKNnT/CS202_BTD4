#ifndef SINGLE_EVENT_BUTTON_H
#define SINGLE_EVENT_BUTTON_H

#include "Button.h"

// Single Event Buttons
class SingleEventButton : public Button {
public:
    SingleEventButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;

protected:
    Event::Type event;
};

class CancelCurrentState : public SingleEventButton {
public: 
    CancelCurrentState(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class PreviousMap : public SingleEventButton {
public: 
    PreviousMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class NextMap : public SingleEventButton {
public: 
    NextMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ChooseMonkeyLane : public SingleEventButton {
public: 
    ChooseMonkeyLane(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class Options : public SingleEventButton {
public: 
    Options(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class GameOptions : public SingleEventButton {
public: 
    GameOptions(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class PreviousTower : public SingleEventButton {
public:
    PreviousTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class NextTower : public SingleEventButton {
public:
    NextTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class BackHome : public SingleEventButton {
public:
    BackHome(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ToAreYouSure : public SingleEventButton {
public:
    ToAreYouSure(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ToEasyModeSelection : public SingleEventButton {
public:
    ToEasyModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ToMediumModeSelection : public SingleEventButton {
public:
    ToMediumModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ToHardModeSelection : public SingleEventButton {
public:
    ToHardModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class ToImpoppableModeSelection : public SingleEventButton {
public:
    ToImpoppableModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class NextPriority : public SingleEventButton {
public:
    NextPriority(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class PreviousPriority : public SingleEventButton {
public:
    PreviousPriority(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

#endif // SINGLE_EVENT_BUTTON_H
