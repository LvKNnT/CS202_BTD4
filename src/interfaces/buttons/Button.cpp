#include "Button.h"
#include "../../core/Game.h"


Button::Button(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
: PanelElement(_height, _width, _position), texture(_texture), fontSize(_fontSize), state(Button::State::None)
{
    title = "";
}

void Button::onClick() {
    
}

void Button::draw() const {
    if(!isAvailable) return;
    
    // Draw texture 
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, state == Button::State::Hovering && fontSize ? (Color) {200, 200, 200, 255}:WHITE);
    
    // Draw text
    int textWidth = MeasureText(title.c_str(), fontSize);
    float textX = position.x + (texture.width * scale - textWidth) / 2;
    float textY = position.y + (texture.height * scale - fontSize) / 2; 
    DrawText(title.c_str(), textX, textY, fontSize, WHITE);
}

bool Button::isClicked() const {
    return false;
}

void Button::getBoundingBox(float &x, float &y, float &width, float &height) const
{
}

void Button::attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

void Button::detach(std::shared_ptr<IObserver> observer) {
    observers.remove(observer);
}

void Button::notify(Event::Type event) {
    for(auto observer:observers) observer->update(event);
}

void Button::update() {    
    if(CheckCollisionPointRec(GetMousePosition(), {position.x, position.y, (float) width, (float) height})) {
        state = Button::State::Hovering;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) state = Button::State::Clicked;
    } else state = Button::State::None;
}

Button::State Button::getState() const {
    return state;
}

// Types of button

NewGame::NewGame(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "New Game";
    attach(Game::Instance().getStateManager());
}

void NewGame::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::NewGame);
    notify(Event::Type::ToMapSelection);
}

Exit::Exit(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "Exit";
}

void Exit::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) return;
    Game::Instance().requestExit();
    notify(Event::Type::Exit);
}

CommingSoon::CommingSoon(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
   : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void CommingSoon::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) return;
}

HigherSound::HigherSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getAudioManager());
    attach(Game::Instance().getStateManager());
}

void HigherSound::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::HigherSound);
}

LowerSound::LowerSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getAudioManager());
    attach(Game::Instance().getStateManager());
}

void LowerSound::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::LowerSound);
}

HigherMusic::HigherMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getAudioManager());
    attach(Game::Instance().getStateManager());
}

void HigherMusic::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::HigherMusic);
}

LowerMusic::LowerMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getAudioManager());
    attach(Game::Instance().getStateManager());
}

void LowerMusic::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::LowerMusic);
}

Continue::Continue(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position){
    title = "Continue";
    attach(Game::Instance().getStateManager());
}

void Continue::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::Continue);
    notify(Event::Type::ToMapSelection);
}
