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

StandardModeButton::StandardModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::StandardMode;
    hoveringEvent = Event::Type::HoveringStandardMode;
}

AlternateBloonsModeButton::AlternateBloonsModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::AlternateBloonsMode;
    hoveringEvent = Event::Type::HoveringAlternateBloonsMode;
}

ReverseModeButton::ReverseModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ModeButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ReverseMode;
    hoveringEvent = Event::Type::HoveringReverseMode;
}

ApopalyseModeButton::ApopalyseModeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
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

ChooseBombShooterTower::ChooseBombShooterTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseBomb;
    clickedEvent = Event::Type::ClickedChooseBomb;
}

ChooseDartMonkeyTower::ChooseDartMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseDartMonkey;
    clickedEvent = Event::Type::ClickedChooseDartMonkey;
}

ChooseNinjaMonkeyTower::ChooseNinjaMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseNinjaMonkey;
    clickedEvent = Event::Type::ClickedChooseNinjaMonkey;
}
