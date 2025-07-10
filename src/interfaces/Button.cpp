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
    
    // Draw texture 
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, state == Button::State::Hovering ? (Color) {200, 200, 200, 255}:WHITE);
    
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
        state = (fontSize == 0 ? Button::State::None:Button::State::Hovering);
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
    notify(Event::Type::ToMapSelection);
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
    notify(Event::Type::ToMonkeyLane);
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
    attach(Game::Instance().getStateManager());
}

void PreviousTower::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MovePrevious);
}

NextTower::NextTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void NextTower::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::MoveNext);
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
    attach(Game::Instance().getSoundManager());
    attach(Game::Instance().getStateManager());
}

void HigherSound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::HigherSound);
}

LowerSound::LowerSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getSoundManager());
    attach(Game::Instance().getStateManager());
}

void LowerSound::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::LowerSound);
}

HigherMusic::HigherMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getSoundManager());
    attach(Game::Instance().getStateManager());
}

void HigherMusic::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::HigherMusic);
}

LowerMusic::LowerMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getSoundManager());
    attach(Game::Instance().getStateManager());
}

void LowerMusic::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) {
        notify(Event::Type::None);
        return;
    }
    notify(Event::Type::LowerMusic);
}

FastForward::FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
}

void FastForward::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
}

BackHome::BackHome(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void BackHome::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::BackHome);
}

ToAreYouSure::ToAreYouSure(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ToAreYouSure::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(Event::Type::ToAreYouSure);
}

ChooseTower::ChooseTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ChooseTower::handleInput() {
    Button::handleInput();
    if(!isAvailable) return;
    if(state == Button::State::Hovering) {
        notify(hoveringEvent);
    } else if(state == Button::State::Clicked) {
        notify(clickedEvent);
    } 
}

ChooseBombTower::ChooseBombTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ChooseTower(_texture, _fontSize, _height, _width, _position){
    hoveringEvent = Event::Type::HoveringChooseBomb;
    clickedEvent = Event::Type::ClickedChooseBomb;
}

ToSpecificModeSelection::ToSpecificModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position) {
    attach(Game::Instance().getStateManager());
}

void ToSpecificModeSelection::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;
    notify(modeSelectionEvent);
}

ToEasyModeSelection::ToEasyModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToEasyModeSelection;
}

ToMediumModeSelection::ToMediumModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToMediumModeSelection;
}

ToHardModeSelection::ToHardModeSelection(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToHardModeSelection;
}

ToEasyStandardMode::ToEasyStandardMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToEasyStandardMode;
}

ToEasyPrimaryOnlyMode::ToEasyPrimaryOnlyMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToEasyPrimaryOnlyMode;
}

ToEasyDeflationdMode::ToEasyDeflationdMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToEasyDeflationdMode;
}

ToEasySandboxMode::ToEasySandboxMode(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : ToSpecificModeSelection(_texture, _fontSize, _height, _width, _position) {
    modeSelectionEvent = Event::Type::ToEasySandboxMode;
}
