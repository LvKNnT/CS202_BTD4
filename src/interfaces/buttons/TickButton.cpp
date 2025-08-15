#include "TickButton.h"
#include "../../core/Game.h"

Tick::Tick(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)  
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::None;
}
     
void Tick::update() {
    Button::update();
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

void AutoNextRound::update() {
    std::string mode = std::dynamic_pointer_cast<StateManager>(Game::Instance().getStateManager())->getMode();
    if(mode.find("Apopalyse") != std::string::npos) {
        isTick = true;
        notify(tickEvent);
        texture = Game::Instance().getTextureManager().getTexture("Untick");
        return;
    }
    Tick::update();
}

MuteSound::MuteSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Tick(_texture, _fontSize, _height, _width, _position) {
    isTick = true;
    untickEvent = Event::Type::MuteSound;
    tickEvent = Event::Type::UnmuteSound;
    attach(Game::Instance().getAudioManager());
}

MuteMusic::MuteMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Tick(_texture, _fontSize, _height, _width, _position) {
    isTick = true;
    untickEvent = Event::Type::MuteMusic;
    tickEvent = Event::Type::UnmuteMusic;
    attach(Game::Instance().getAudioManager());
}
