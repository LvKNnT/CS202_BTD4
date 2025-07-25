#ifndef UPGRADE_BUTTON_H
#define UPGRADE_BUTTON_H

#include "Button.h"

class UpgradeButton : public Button {
public:
    UpgradeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void setTexture(const Texture &newTexture);
    void handleInput() override;

protected:
    Event::Type upgradeEvent;
};  

class UpgradeLeftButton : public UpgradeButton {
public:
    UpgradeLeftButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class UpgradeMiddleButton : public UpgradeButton {
public:
    UpgradeMiddleButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class UpgradeRightButton : public UpgradeButton {
public:
    UpgradeRightButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

class NoUpgradeButton : public UpgradeButton {
public:
    NoUpgradeButton(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
}; 
#endif // UPGRADE_BUTTON_H