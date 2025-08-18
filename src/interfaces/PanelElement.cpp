#include "PanelElement.h"

PanelElement::PanelElement(int _height, int _width) 
    : height(_height), width(_width), isAvailable(true) {
}

PanelElement::PanelElement(int _height, int _width, Vector2 _position)
    : index(-1), height(_height), width(_width), position(_position), isAvailable(true)
{
}

void PanelElement::draw() const {

}

int PanelElement::getIndex() const {
    return index;
}

void PanelElement::setIndex(int _index) {
    index = _index;
}

void PanelElement::setAvailable(bool _isAvailable) {
    isAvailable = _isAvailable;
}
