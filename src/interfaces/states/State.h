#ifndef STATE_H
#define STATE_H

#include <memory>

#include "raylib.h"
#include "../buttons/Button.h"
#include "../buttons/CanHoveringButton.h"
#include "../buttons/SingleEventButton.h"
#include "../buttons/TickButton.h"
#include "../TextField.h"
#include "../TextureField.h"
#include "../Panel.h"
#include "../../core/Event.h"
#include "../../utils/Properties.h"

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
    virtual void update(Event::Type event); // updated by on-click event
    virtual void handleInput();
};

#endif // STATE_H