#include "TickButton.h"
#include "../../core/Game.h"

Tick::Tick(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)  
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::None;
}
     
void Tick::handleInput() {
    Button::handleInput();
    if(!isAvailable) return;
    if(state != Button::State::None) {
        notify(hoveringEvent);
    } else notify(Event::Type::None);
    
    if(state != Button::State::Clicked) return;
    
    isTick = !isTick;
    if(!isTick) {
        notify(untickEvent);
    texture = Game::Instance().getTextureManager().getTexture("Tick");
    }
    else {
        notify(tickEvent);
        texture = Game::Instance().getTextureManager().getTexture("Untick");
    }
}

AutoNextRound::AutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Tick(_texture, _fontSize, _height, _width, _position) {
    isTick = false;
    tickEvent = Event::Type::AutoNextRound;
    untickEvent = Event::Type::UnAutoNextRound;
}
