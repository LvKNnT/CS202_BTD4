#include "Panel.h"

Panel::Panel():isAvailable(true) {
}

void Panel::addPanelElement(std::shared_ptr<PanelElement> newPanelElement) {
    newPanelElement->setIndex((int) elements.size());
    elements.push_back(newPanelElement);
}

void Panel::removePanelElement(int index) {
    if (index < 0 || index >= (int)elements.size()) return;
    elements.erase(elements.begin() + index);
    for (int i = 0; i < (int)elements.size(); ++i) {
        elements[i]->setIndex(i);
    }
}

void Panel::draw() const {
    if(!isAvailable) return;
    for(auto &element:elements) {
        if(element) element->draw();
    }
}

void Panel::update() {
    if(!isAvailable) return;
}

void Panel::handleInput() {
    if(!isAvailable) return;
    for(auto &element:elements) {
        if(element) element->handleInput();
    }
}

void Panel::setAvailable(bool _isAvailable) {
    isAvailable = _isAvailable;
}

bool Panel::getIsAvailable() const {
    return isAvailable;
}
