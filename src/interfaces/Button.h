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
    enum Type {
        NewGame, 
        Resume, 
        Options, 
        CancelMapSelection,
        PreviousMap, 
        NextMap, 
        Exit, 
        ChooseMonkeyLane, 
        ChooseJungle, 
        CommingSoon
    };

    enum State {
        None, 
        Hovering,
        Clicked
    };

private:
    Texture texture;
    std::string title;
    int fontSize;
    std::list<std::shared_ptr<IObserver>> observers;
    Type type;
    State state;

public:
    Button(Type _type, const Texture &_texture, int _fontSize, int _height, int _width, Vector2 _position);
    void draw() const override;
    bool isClicked() const override;
    void onClick() override;
    void getBoundingBox(float& x, float& y, float& width, float& height) const override;
    void handleInput() override;

    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify(Event::Type event) override;
};

#endif // BUTTON_H