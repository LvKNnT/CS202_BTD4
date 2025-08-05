#include "UpgradeTextureHandler.h"
#include <iostream>
#include "../../core/Game.h"

void UpgradeTextureHandler::loadTextures() {
    // Load textures for each upgrade
    Game::Instance().getTextureManager().loadTexture("Glowy Star", "../assets/tower/GlowyStar.png");
}

void UpgradeTextureHandler::upgradeTopTexture() {
    topTextureId++;
}
void UpgradeTextureHandler::upgradeMiddleTexture() {
    middleTextureId++;
}
void UpgradeTextureHandler::upgradeBottomTexture() {
    bottomTextureId++;
}

void UpgradeTextureHandler::draw(Rectangle boundingBox) const {
    int drawLength = boundingBox.width / 3;
    Vector2 position = {boundingBox.x, boundingBox.y + boundingBox.height * 2 / 3};

    // Draw the top texture
    DrawTexturePro(Game::Instance().getTextureManager().getTexture("Glowy Star"),
                {0, 0, static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").width), static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").height)},
                {position.x, position.y, static_cast<float>(drawLength), static_cast<float>(drawLength)},
                {0, 0}, 0.0f, colors[topTextureId % colors.size()]); // Draw the top texture
    // Draw the middle texture
    position.x += drawLength;
    DrawTexturePro(Game::Instance().getTextureManager().getTexture("Glowy Star"),
                {0, 0, static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").width), static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").height)},
                {position.x, position.y, static_cast<float>(drawLength), static_cast<float>(drawLength)},
                {0, 0}, 0.0f, colors[middleTextureId % colors.size()]); // Draw the middle texture
    // Draw the bottom texture
    position.x += drawLength;
    DrawTexturePro(Game::Instance().getTextureManager().getTexture("Glowy Star"),
                {0, 0, static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").width), static_cast<float>(Game::Instance().getTextureManager().getTexture("Glowy Star").height)},
                {position.x, position.y, static_cast<float>(drawLength), static_cast<float>(drawLength)},
                {0, 0}, 0.0f, colors[bottomTextureId % colors.size()]); // Draw the bottom texture
}