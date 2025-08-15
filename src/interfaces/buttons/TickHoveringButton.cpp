#include "TickHoveringButton.h"
#include "../../core/Game.h"

TickHoveringButton::TickHoveringButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : Button(_texture, _fontSize, _height, _width, _position) {
    isTick = false;
    attach(Game::Instance().getStateManager());
}

void TickHoveringButton::update() {
    Button::update();
    if(!isAvailable || state != Button::State::Clicked) return;
    isTick = !isTick;
    if(isTick) notify(tickEvent);
    else notify(untickEvent);
}

void TickHoveringButton::draw() const {
    if(!isAvailable) return;
    
    // Draw texture 
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;
    DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, isTick ? (Color) {150, 150, 150, 255}:WHITE);
    
    // Draw text
    int textWidth = MeasureText(title.c_str(), fontSize);
    float textX = position.x + (texture.width * scale - textWidth) / 2;
    float textY = position.y + (texture.height * scale - fontSize) / 2; 
    DrawText(title.c_str(), textX, textY, fontSize, WHITE);
}

FastForward::FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : TickHoveringButton(_texture, _fontSize, _height, _width, _position){
    tickEvent = Event::Type::TickFastForward;
    untickEvent = Event::Type::UntickFastForward;
}

StartRoundButton::StartRoundButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position) 
    : TickHoveringButton(_texture, _fontSize, _height, _width, _position){
    tickEvent = Event::Type::StartRound;
    untickEvent = Event::Type::None;
}

void StartRoundButton::update() {
    Button::update();
    if(Game::Instance().getGameLogic().isRoundRun()) {
        isTick = 1;
    } else isTick = 0;

    if(!isAvailable || state != Button::State::Clicked) return;
    notify(tickEvent);
}
