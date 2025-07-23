#include "TextField.h"
#include <vector>
#include "iostream"

TextField::TextField(const std::string &_text, const Font &_font, const Color &_color, int _height, int _width, Vector2 _position)
    : PanelElement(_height, _width, _position), text(_text), font(_font), color(_color) {
    if(width) formatText();
}

void TextField::formatText() {
    std::string tmp = "";
    std::string res = "";
    std::vector<std::string> words;
    for(auto ch:text) {
        if(ch == ' ') {
            words.push_back(tmp);
            tmp = "";
        } else tmp += ch;
    }
    words.push_back(tmp);

    int cntWord = 0;
    for(int i = 0; i < (int) words.size(); i++) {
        tmp += (i == 0 ? "":" ") + words[i];
        float curWidth = MeasureTextEx(font, tmp.c_str(), height, 0).x;
        if(curWidth > width && cntWord > 0) {
            tmp.clear();
            tmp += words[i];
            cntWord = 1;
            res += '\n' + words[i];
        } else {
            cntWord++;
            res += (i == 0 ? "":" ") + words[i];
        }
    }
    text = res;
}

void TextField::setText(const std::string &newText) {
    text = newText;
    if(width) formatText();
}

void TextField::setTextAndPos(const std::string &newText, Vector2 newPosition) {
    position = newPosition;
    setText(newText);
}

void TextField::draw() const {
    if(!isAvailable) return;
    DrawTextEx(font, text.c_str(), position, height, 0, color);
}

void TextField::handleInput() {
    if(!isAvailable) return;
}

MovableTextbox::MovableTextbox(const std::string& _text, const Font& _font, const Color& _color, int _height, int _width) 
    : TextField(_text, _font, _color, _height, _width, GetMousePosition()) {

}

void MovableTextbox::draw() const {
    if(!isAvailable) return;
    Vector2 mousePos = GetMousePosition();
    float rectHeight = height;
    for(auto ch:text) {
        if(ch == '\n') {
            rectHeight += height;
        }
    }
    DrawRectangle(mousePos.x - width, mousePos.y, width, rectHeight, {0, 0, 0, 170});
    DrawTextEx(font, text.c_str(), (Vector2) {mousePos.x - width, mousePos.y}, height, 0, color);
}
