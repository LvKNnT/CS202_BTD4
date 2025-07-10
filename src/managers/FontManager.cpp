#include "FontManager.h"

FontManager::~FontManager() {
    unloadAllFonts();
}

void FontManager::loadFont(std::string name, std::string path, int fontSize) {
    Font newFont = LoadFontEx(path.c_str(), fontSize, 0, 0);
    if(newFont.texture.id == 0) {
        std::cerr<<"Error: Failed to load font: "<<path<<"!\n";
        return;
    }
    SetTextureFilter(newFont.texture, TEXTURE_FILTER_POINT);
    fonts[name] = newFont;
}

void FontManager::unloadAllFonts() {
    for(auto &font:fonts) {
        UnloadFont(font.second);
    }
    fonts.clear();
}

Font &FontManager::getFront(std::string name) {
    auto it = fonts.find(name);
    if(it != fonts.end()) return it->second;
    static Font empty = {0};
    std::cerr<<"Warning: Font "<<name<<" not found!\n";
    return empty;
}
