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

void UpgradeLeftButton::draw() const {
    if(!isAvailable) return;
    
    // Draw texture 
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, (Color) {170, 170, 170, 255});
    
    // Draw text
    int textWidth = MeasureText(title.c_str(), fontSize);
    float textX = position.x + (texture.width * scale - textWidth) / 2;
    float textY = position.y + (texture.height * scale - fontSize) / 2; 
    DrawText(title.c_str(), textX, textY, fontSize, WHITE);
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
