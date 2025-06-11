#include "PanelElement.h"

PanelElement::PanelElement(int _height, int _width, Vector2 _position)
    : index(-1), height(_height), width(_width), position(_position) {
}

void PanelElement::draw() const {

}

int PanelElement::getIndex() const {
    return index;
}

void PanelElement::setIndex(int _index) {
    index = _index;
}

