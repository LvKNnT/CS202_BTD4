#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <unordered_map>
#include <string>
#include <iostream>

#include "raylib.h"

class FontManager {
private:
    std::unordered_map<std::string, Font> fonts;

public:
    ~FontManager();
    void loadFont(std::string name, std::string path, int fontSize);
    Font &getFont(std::string name);
};

#endif // FONT_MANAGER_H

