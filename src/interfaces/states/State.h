#ifndef STATE_H
#define STATE_H

#include <memory>

#include "raylib.h"
#include "../Button.h"
#include "../TextField.h"
#include "../TextureField.h"
#include "../Panel.h"
#include "../../Properties.h"

class State {
protected:
    int height;
    int width;
    Texture background;
    std::unique_ptr<Panel> panel;

public:
    State(int _height, int _width, const Texture& _texture);
    virtual ~State() = default;
    void onButtonClick(std::shared_ptr<Button> button);
    virtual void draw() const;
    virtual void update(Event::Type event);
    virtual void handleInput();
};

#endif // STATE_H