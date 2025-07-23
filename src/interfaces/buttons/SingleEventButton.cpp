#include "SingleEventButton.h"
#include "../../core/Game.h"

SingleEventButton::SingleEventButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    event = Event::Type::None;
}

void SingleEventButton::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(event);
}

Options::Options(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    title = "Options";
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToOptions;
}

CancelCurrentState::CancelCurrentState(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::CancelCurrentState;
}

PreviousMap::PreviousMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::MovePrevious;
}

NextMap::NextMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::MoveNext;
}

ChooseMonkeyLane::ChooseMonkeyLane(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToMonkeyLane;
}

GameOptions::GameOptions(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToOptions;
}

PreviousTower::PreviousTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::MovePrevious;
}

NextTower::NextTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::MoveNext;
}

BackHome::BackHome(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::BackHome;
}

ToAreYouSure::ToAreYouSure(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToAreYouSure;
}

ToEasyModeSelection::ToEasyModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToEasyModeSelection;
}

ToMediumModeSelection::ToMediumModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToMediumModeSelection;
}

ToHardModeSelection::ToHardModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToHardModeSelection;
}

ToImpoppableModeSelection::ToImpoppableModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    event = Event::Type::ToImpoppableModeSelection;
}

NextPriority::NextPriority(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    event = Event::Type::NextPriority;
}

PreviousPriority::PreviousPriority(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : SingleEventButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    event = Event::Type::PreviousPriority;
}