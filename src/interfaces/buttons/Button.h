#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <iostream>
#include <list>

#include "../Clickable.h"
#include "../PanelElement.h"
#include "../../core/ISubject.h"
#include "../../core/Event.h"

class Button : public Clickable, public PanelElement, public ISubject {
public: 
    enum State {
        None, 
        Hovering,
        Clicked
    };

protected:
    Texture texture;
    std::string title;
    int fontSize;
    std::list<std::shared_ptr<IObserver>> observers;
    State state;    
    
public:
    Button(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void draw() const override;
    bool isClicked() const override;
    void onClick() override;
    void getBoundingBox(float& x, float& y, float& width, float& height) const override;
    virtual void handleInput();
    State getState() const;
    
    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify(Event::Type event) override;
};

// Normal Buttons
class NewGame : public Button {
public: 
    NewGame(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class Resume : public Button {
public: 
    Resume(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class Exit : public Button {
public: 
    Exit(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class ChooseJungle : public Button {
public: 
    ChooseJungle(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class CommingSoon : public Button {
public: 
    CommingSoon(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class StartRound : public Button {
public:
    StartRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class HigherSound : public Button {
public:
    HigherSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class LowerSound : public Button {
public:
    LowerSound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class HigherMusic : public Button {
public:
    HigherMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class LowerMusic : public Button {
public:
    LowerMusic(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class FastForward : public Button {
private:
    bool isTick;
public:
    FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
    void draw() const override;
};

class Continue : public Button {
public:
    Continue(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class ChooseTower : public Button{ 
    // deal hover effect(show infor, texture) 
    // deal select event -> move the texture need a circle around show range, check whether placable, show cancel by option 
    // deal cancel click -> press esc or move out the screen 
public:
    ChooseTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;

protected:
    Event::Type hoveringEvent;
    Event::Type clickedEvent; // or select
};

class ChooseBombTower : public ChooseTower {
public:
    ChooseBombTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
};

// class Tower : public Button {
//     // deal select tower -> show infor, upgrade, sell 
//     // cancel select by clicking out of range, or press esc key
// public:
//     Tower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
//     void handleInput() override;
// };
#endif // BUTTON_H
