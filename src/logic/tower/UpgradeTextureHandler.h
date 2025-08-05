#ifndef UPGRADE_TEXTURE_HANDLER_H
#define UPGRADE_TEXTURE_HANDLER_H

#include "raylib.h"
#include <vector>

class UpgradeTextureHandler {
private:
    int topTextureId = 0;
    int middleTextureId = 0;
    int bottomTextureId = 0;

    const std::vector<Color> colors = {WHITE, GREEN, BLUE, PURPLE, ORANGE, RED}; // Rarity colors for upgrades

public:
    UpgradeTextureHandler() = default;
    UpgradeTextureHandler(const UpgradeTextureHandler&) = default;
    ~UpgradeTextureHandler() = default;

    // Load textures for tower upgrades
    void loadTextures();

    void upgradeTopTexture();
    void upgradeMiddleTexture();
    void upgradeBottomTexture();

    // Get texture based on upgrade unit type
    void draw(Rectangle boundingBox) const;
};

#endif // UPGRADE_TEXTURE_HANDLER_H