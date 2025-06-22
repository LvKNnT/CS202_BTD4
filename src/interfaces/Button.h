#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <iostream>
#include <list>

#include "Clickable.h"
#include "PanelElement.h"
#include "../core/ISubject.h"
#include "../core/Event.h"

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

    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify(Event::Type event) override;
};

// Types of button
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

class Options : public Button {
public: 
    Options(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class Exit : public Button {
public: 
    Exit(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class CancelCurrentState : public Button {
public: 
    CancelCurrentState(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class PreviousMap : public Button {
public: 
    PreviousMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class NextMap : public Button {
public: 
    NextMap(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class ChooseMonkeyLane : public Button {
public: 
    ChooseMonkeyLane(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
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

class GameOptions : public Button {
public: 
    GameOptions(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class PreviousTower : public Button {
public:
    PreviousTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class NextTower : public Button {
public:
    NextTower(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class AutoNextRound : public Button {
public:
    AutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};

class UnAutoNextRound : public Button {
public:
    UnAutoNextRound(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
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
public:
    FastForward(const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void handleInput() override;
};
#endif // BUTTON_H
