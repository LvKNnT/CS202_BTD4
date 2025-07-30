#ifndef SKILL_BUTTON_H
#define SKILL_BUTTON_H

#include "Button.h"

class SkillButton : public Button {
private:
    float cooldown;
public:
    SkillButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
    void draw() const override;
    void setCooldown(float newCooldown);
    void setTexture(const Texture &newTexture);
};

#endif // SKILL_BUTTON_H