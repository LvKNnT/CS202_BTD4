#ifndef PANEL_H
#define PANEL_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

#include "raylib.h"
#include "Drawable.h"
#include "PanelElement.h"

class Panel : public Drawable {
private:
    std::vector<std::shared_ptr<PanelElement>> elements;
    int height;
    int width;
    std::string title;
    Vector2 position;

public:
    Panel();
    void addPanelElement(std::shared_ptr<PanelElement> newPanelElement);
    void removePanelElement(int index);
    void draw() const override;
    void update();
    void getBoundingBox(float& x, float& y, float& width, float& height) const override;
    void handleInput();

};

#endif // PANEL_H