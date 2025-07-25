#include "UpgradeButton.h"
#include "../../core/Game.h"

UpgradeButton::UpgradeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void UpgradeButton::setTexture(const Texture &newTexture) {
    texture = newTexture;
}

void UpgradeButton::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(upgradeEvent);
}

UpgradeLeftButton::UpgradeLeftButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : UpgradeButton(_texture, _fontSize, _height, _width, _position){
    upgradeEvent = Event::Type::UpgradeTowerLeft;        
}

UpgradeMiddleButton::UpgradeMiddleButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : UpgradeButton(_texture, _fontSize, _height, _width, _position){
    upgradeEvent = Event::Type::UpgradeTowerMiddle;        
}

UpgradeRightButton::UpgradeRightButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : UpgradeButton(_texture, _fontSize, _height, _width, _position){
    upgradeEvent = Event::Type::UpgradeTowerRight;        
}

NoUpgradeButton::NoUpgradeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : UpgradeButton(_texture, _fontSize, _height, _width, _position){
    upgradeEvent = Event::Type::None;   
}
