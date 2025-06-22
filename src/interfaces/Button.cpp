#include "Button.h"
#include "../core/Game.h"


Button::Button(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
: PanelElement(_height, _width, _position), texture(_texture), fontSize(_fontSize), state(Button::State::None)
{
    title = "";
}

void Button::onClick() {
    
}

void Button::draw() const {
    if(!isAvailable) return;
    
    float scale = std::max(((float) width / texture.width), ( (float) height / texture.height));
    // Draw texture 
    DrawTextureEx(texture, position, 0.0f, scale, state == Button::State::Hovering ? (Color) {200, 200, 200, 255}:WHITE);

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

void Button::handleInput() {    
    if(CheckCollisionPointRec(GetMousePosition(), {position.x, position.y, (float) width, (float) height})) {
        state = (title == "" ? Button::State::None:Button::State::Hovering);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) state = Button::State::Clicked;
    } else state = Button::State::None;
}

// Types of button
NewGame::NewGame(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "New Game";
    attach(Game::Instance().getStateManager());
}

void NewGame::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MainMenuToMapSelection);
}

Resume::Resume(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "Resume";
}

void Resume::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

Options::Options(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "Options";
    attach(Game::Instance().getStateManager());
}

void Options::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::ToOptions);
}

Exit::Exit(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    title = "Exit";
}

void Exit::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    Game::Instance().requestExit();
}

CancelCurrentState::CancelCurrentState(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void CancelCurrentState::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::CancelCurrentState);
}

PreviousMap::PreviousMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void PreviousMap::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MovePrevious);
}

NextMap::NextMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void NextMap::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MoveNext);
}


ChooseMonkeyLane::ChooseMonkeyLane(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ChooseMonkeyLane::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MapSelectionToMonkeyLane);
}

ChooseJungle::ChooseJungle(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ChooseJungle::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

CommingSoon::CommingSoon(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
   : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void CommingSoon::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}


StartRound::StartRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {    
}

void StartRound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;

}

GameOptions::GameOptions(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void GameOptions::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::ToOptions);

}

PreviousTower::PreviousTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void PreviousTower::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

NextTower::NextTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void NextTower::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

AutoNextRound::AutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void AutoNextRound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

UnAutoNextRound::UnAutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void UnAutoNextRound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

HigherSound::HigherSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void HigherSound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

LowerSound::LowerSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void LowerSound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}


HigherMusic::HigherMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void HigherMusic::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

LowerMusic::LowerMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void LowerMusic::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

FastForward::FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void FastForward::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}



