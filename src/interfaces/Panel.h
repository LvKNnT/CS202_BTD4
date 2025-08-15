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
    bool isAvailable;

public:
    Panel();
    void addPanelElement(std::shared_ptr<PanelElement> newPanelElement);
    void removePanelElement(int index);
    void setAvailable(bool _isAvailable);
    bool getIsAvailable() const;
    void draw() const override;
    void update();

};

#endif // PANEL_H