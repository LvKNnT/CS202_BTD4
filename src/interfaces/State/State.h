#ifndef STATE_H
#define STATE_H

#include <memory>

#include "raylib.h"
#include "../Button.h"
#include "../Panel.h"

class State {
private:
    int height;
    int width;
    Texture background;
    std::unique_ptr<Panel> panel;

public:
    State() = default;
    void onButtonClick(std::shared_ptr<Button> button);
    void draw() const;
    void update();
    void handleInput();
};

#endif // STATE_H