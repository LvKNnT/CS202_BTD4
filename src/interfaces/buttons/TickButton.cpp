#include "TickButton.h"
#include "../../core/Game.h"
#include "../../logic/mode/ModeUnits.h"

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
    isTick = Game::Instance().getGameLogic().getAutoPlay();
    texture = Game::Instance().getTextureManager().getTexture(!isTick ? "Tick":"Untick");
    tickEvent = Event::Type::AutoNextRound;
    untickEvent = Event::Type::UnAutoNextRound;
}

void AutoNextRound::update() {
    auto mode = Game::Instance().getGameLogic().getModeType();
    if(mode == ModeType::Apopalypse) {
        isTick = true;
        notify(tickEvent);
        texture = Game::Instance().getTextureManager().getTexture("Untick");
        return;
    }
    Tick::update();
}

MuteSound::MuteSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Tick(_texture, _fontSize, _height, _width, _position) {
    isTick = !std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->isMuted(AudioType::SFXSound);
    texture = Game::Instance().getTextureManager().getTexture(!isTick ? "Tick":"Untick");
    untickEvent = Event::Type::MuteSound;
    tickEvent = Event::Type::UnmuteSound;
    attach(Game::Instance().getAudioManager());
}

MuteMusic::MuteMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
: Tick(_texture, _fontSize, _height, _width, _position) {
    isTick = !std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->isMuted(AudioType::MusicSound);
    texture = Game::Instance().getTextureManager().getTexture(!isTick ? "Tick":"Untick");
    untickEvent = Event::Type::MuteMusic;
    tickEvent = Event::Type::UnmuteMusic;
    attach(Game::Instance().getAudioManager());
}
