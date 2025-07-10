#include "DartMonkey.h"

#include "../../../attack/attacks/DartAttack.h"
#include "SharpShots.h"

DartMonkey::DartMonkey(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::DartMonkey, 200) {
    /**
     * cost = 200
     */

    tag = "DartMonkey";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 100.0f
     * * cooldown = 1.0f
     * * * position = {0.0f, 0.0f}
     * * * damage = 1
     * * * speed = 200
     * * * pierce = 1
     * * * lifeSpan = 60.0f
     */
    attacks.push_back(std::make_unique<DartAttack>(100.0f, 0.1f, position, 1, 200, 1, 5.0f));

    // Upgrade Path
    upgradeTop = std::make_unique<SharpShots>();
    upgradeMiddle = std::make_unique<Upgrade>();
    upgradeBottom = std::make_unique<Upgrade>();
}

DartMonkey::DartMonkey(const DartMonkey& other)
    : Tower(other) {
}

std::unique_ptr<Tower> DartMonkey::clone() const {
    return std::make_unique<DartMonkey>(*this);
}

void DartMonkey::loadTexture() {
    // Load the texture for the Dart Monkey tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/DartMonkey.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();
}

void DartMonkey::update() {
    // Dart Monkey has no special update.
}

void DartMonkey::setRotation(float rotation) {
    this->rotation = rotation;
}

void DartMonkey::draw() const {
    // Check if the tower is active before drawing
    if (!isActiveFlag) {
        return; 
    } 

    // Draw the Dart Monkey tower using raylib functions
    DrawCircleV(position, 10, YELLOW); // Example drawing a yellow circle for the tower

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(texture, 
                   {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Dart Monkey texture with the specified position and rotation

    // Draw the range of attacks
    for(const auto& attack : attacks) {
        DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
    }
}

void DartMonkey::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Dart Monkey
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = static_cast<int>(upgradeCost * modifies.upgradeCost);
}

void DartMonkey::upgrade(const UpgradeUnits& upgradeUnits, int& currentCash) {
    // Upgrade the Dart Monkey tower based on the specified upgrade unit
    switch (upgradeUnits) {
        case UpgradeUnits::Top:
            if (upgradeTop->getCost() * upgradeCost <= currentCash && upgradeTop->getName() != "NoUpgrade") {
                upgradeTop->update(attacks);
                upgradeTop = upgradeTop->buy();
                currentCash -= upgradeTop->getCost() * upgradeCost;
            }
            break;
        case UpgradeUnits::Middle:
            if (upgradeMiddle->getCost() * upgradeCost <= currentCash && upgradeMiddle->getName() != "NoUpgrade") {
                upgradeMiddle->update(attacks);
                upgradeMiddle = upgradeMiddle->buy();
                currentCash -= upgradeMiddle->getCost() * upgradeCost;
            }
            break;
        case UpgradeUnits::Bottom:
            if (upgradeBottom->getCost() * upgradeCost <= currentCash && upgradeBottom->getName() != "NoUpgrade") {
                upgradeBottom->update(attacks);
                upgradeBottom = upgradeBottom->buy();
                currentCash -= upgradeBottom->getCost() * upgradeCost;
            }
            break;
        default:
            break;
    }
}

Rectangle DartMonkey::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2, position.y - size.y / 2, size.x, size.y};
}

bool DartMonkey::isActive() const {
    return isActiveFlag;
}

void DartMonkey::setActive(bool active) {
    isActiveFlag = active;
}