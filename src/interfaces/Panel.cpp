#include "Panel.h"

Panel::Panel()
{
}

void Panel::addPanelElement(std::unique_ptr<PanelElement> newPanelElement) {
    newPanelElement->setIndex((int) elements.size());
    elements.push_back(std::move(newPanelElement));
}

void Panel::removePanelElement(int index) {
    if (index < 0 || index >= (int)elements.size()) return;
    elements.erase(elements.begin() + index);
    for (int i = 0; i < (int)elements.size(); ++i) {
        elements[i]->setIndex(i);
    }
}

void Panel::draw() const {
    for(auto &element:elements) {
        element->draw();
    }
}

void Panel::update() {

}

void Panel::getBoundingBox(float& x, float& y, float& width, float& height) const {
    
}

void Panel::handleInput() {
    for(auto &element:elements) {
        element->handleInput();
    }
}