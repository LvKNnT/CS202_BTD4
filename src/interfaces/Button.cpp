#include "Button.h"
#include "../core/Game.h"

Button::Button(Type _type, const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position), texture(_texture), fontSize(_fontSize), type(_type), state(Button::State::None) {

    if (texture.id == 0) {
        std::cerr << "Error : Cannot load Texture\n";
    }

    switch(type) {
        case NewGame:
            title = "New Game";
            attach(Game::Instance().getStateManager());
            break;
        case Resume:
            title = "Resume";
            break;
        case Options:
            title = "Options";
            break;
        case Exit:
            title = "Exit";
            break;
        case CancelMapSelection:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
        case NextMap:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
        case PreviousMap:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
        case ChooseMonkeyLane:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
        case ChooseJungle:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
        case CommingSoon:
            title = "";
            attach(Game::Instance().getStateManager());
            break;
    }
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
    if(!isAvailable) return;

    if(CheckCollisionPointRec(GetMousePosition(), {position.x, position.y, (float) width, (float) height})) {
        state = (title == "" ? Button::State::None:Button::State::Hovering);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) state = Button::State::Clicked;
    } else state = Button::State::None;

    if(state != Button::State::Clicked) return;

    switch(type) {
        case NewGame:
            notify(Event::Type::MainMenuToMapSelection);
            break;
        case Resume:
            break;
        case Options:
            break;
        case Exit:
            Game::Instance().requestExit();
            break;
        case CancelMapSelection:
            notify(Event::Type::CancelMapSelection);
            break;
        case NextMap:
            notify(Event::Type::MoveNext);
            break;
        case PreviousMap:
            notify(Event::Type::MovePrevious);
            break;
        case ChooseMonkeyLane:
            notify(Event::Type::MapSelectionToMonkeyLane);
            break;
        default:
            notify(Event::Type::None);
            break;
    }
}

