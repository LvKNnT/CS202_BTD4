#include "SkillButton.h"
#include "../../core/Game.h"

SkillButton::SkillButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position)
    : Button(_texture, _fontSize, _height, _width, _position), cooldown(100.f) {
    attach(Game::Instance().getStateManager());
}

void SkillButton::handleInput() {
    Button::handleInput();
    if(!isAvailable || state != Button::State::Clicked) return;

}

void SkillButton::draw() const {
    if(!isAvailable) return;
    float scale = std::min(((float) width / texture.width), ( (float) height / texture.height));
    float texWidth = texture.width * scale;
    float texHeight = texture.height * scale;

    if(cooldown < 100.f) {
        DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, (Color) {170, 170, 170, 255});
        float rectHeight = (cooldown / 100.0f) * height;
        Rectangle cooldownRect = {position.x + width - 5.f, position.y, 10.f, static_cast<float>(height)};
        DrawRectangleRec(cooldownRect, Fade(BLACK, 0.5f));
        cooldownRect = {position.x + width - 5.f, position.y + height - rectHeight, 10.f, rectHeight};
        DrawRectangleRec(cooldownRect, ORANGE);
    } else {
        DrawTextureEx(texture, (Vector2) {position.x + std::max((float) width - texWidth, 0.f) / 2, position.y + std::max((float) height - texHeight, 0.f) / 2}, 0.0f, scale, WHITE);
    }
}

void SkillButton::setCooldown(float newCooldown) {
    cooldown = newCooldown;
}

void SkillButton::setTexture(const Texture& newTexture) {
    texture = newTexture;
}