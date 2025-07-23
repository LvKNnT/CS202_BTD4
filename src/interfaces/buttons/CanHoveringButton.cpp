#include "CanHoveringButton.h"
#include "../../core/Game.h"

CanHoveringButton::CanHoveringButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void CanHoveringButton::handleInput() {
    Button::handleInput();
    if(!isAvailable) return;
    if(state != Button::State::None) {
        notify(hoveringEvent);
    } else notify(Event::Type::None);

    if(state != Button::State::Clicked) return;
    notify(clickedEvent);
}

ModeButton::ModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ModeButton::handleInput() {
    Button::handleInput();
    if(!isAvailable) return;
    if(state != Button::State::None) {
        notify(hoveringEvent);
    } else notify(Event::Type::None);

    if(state != Button::State::Clicked) return;
    notify(clickedEvent);
    notify(Event::Type::ToGameState);
}


StandardMode::StandardMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::StandardMode;
    hoveringEvent = Event::Type::None;
}

AlternateBloonsMode::AlternateBloonsMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::AlternateBloonsMode;
    hoveringEvent = Event::Type::HoveringAlternateBloonsMode;
}

ReverseMode::ReverseMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ReverseMode;
    hoveringEvent = Event::Type::HoveringReverseMode;
}

ApopalyseMode::ApopalyseMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ApopalyseMode;
    hoveringEvent = Event::Type::HoveringApopalyseMode;
}

Info::Info(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    clickedEvent = Event::Type::None;
    hoveringEvent = Event::Type::HoveringInfo;
}
