#include "CanHoveringButton.h"
#include "../../core/Game.h"

CanHoveringButton::CanHoveringButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void CanHoveringButton::update() {
    Button::update();
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

void ModeButton::update() {
    Button::update();
    if(!isAvailable) return;
    if(state != Button::State::None) {
        notify(hoveringEvent);
    } else notify(Event::Type::None);

    if(state != Button::State::Clicked) return;
    notify(clickedEvent);
    notify(Event::Type::ToHeroSelection);
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

HeroButton::HeroButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void HeroButton::update() {
    Button::update();
    if(!isAvailable) return;
    if(state != Button::State::None) {
        notify(hoveringEvent);
    } else notify(Event::Type::None);

    if(state != Button::State::Clicked) return;
    notify(clickedEvent);
    notify(Event::Type::ToGameState);
}

QuincyButton::QuincyButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : HeroButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ClickedQuincy;
    hoveringEvent = Event::Type::HoveringQuincy;
}

BenjaminButton::BenjaminButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : HeroButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ClickedBenjamin;
    hoveringEvent = Event::Type::HoveringBenjamin;
}

RosaliaButton::RosaliaButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : HeroButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ClickedRosalia;
    hoveringEvent = Event::Type::HoveringRosalia;
}

EtienneButton::EtienneButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : HeroButton(_texture, _fontSize, _height, _width, _position) {
    clickedEvent = Event::Type::ClickedEtienne;
    hoveringEvent = Event::Type::HoveringEtienne;
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

ChooseSniperMonkeyTower::ChooseSniperMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseSniperMonkey;
    clickedEvent = Event::Type::ClickedChooseSniperMonkey;
}

ChooseSpikeBullet::ChooseSpikeBullet(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseSpike;
    clickedEvent = Event::Type::ClickedChooseSpike;
}

ChoosePineappleBullet::ChoosePineappleBullet(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChoosePineapple;
    clickedEvent = Event::Type::ClickedChoosePineapple;
}

ChooseIceMonkeyTower::ChooseIceMonkeyTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position){
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseIceMonkey;
    clickedEvent = Event::Type::ClickedChooseIceMonkey;
}

ChooseMonkeySubTower::ChooseMonkeySubTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : CanHoveringButton(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
    hoveringEvent = Event::Type::HoveringChooseMonkeySub;
    clickedEvent = Event::Type::ClickedChooseMonkeySub;
}
