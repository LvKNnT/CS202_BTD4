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
     * * * lifeSpan = 1.0f
     */
    attacks.push_back(std::make_unique<DartAttack>(100.0f, 0.1f, position, towerId, 1, 200, 1, 1.0f, false));

    // Upgrade Path
    upgradeTop = std::make_unique<SharpShots>();
    upgradeMiddle = std::make_unique<Upgrade>();
    upgradeBottom = std::make_unique<Upgrade>();

    // Info section
    info["name"] = "Dart Monkey";
    info["description"] = "Throw a single dart at nearby Bloons. Short range and low pierce but cheap";
    info["cost"] = std::to_string(cost);
    info["popCount"] = std::to_string(popCount);
    info["sellPrice"] = std::to_string(static_cast<int>(cost * 0.75f));

    switch (targetPriority) {
        case TargetPriority::First:
            info["targetPriority"] = "First";
            break;
        case TargetPriority::Last:
            info["targetPriority"] = "Last";
            break;
        case TargetPriority::Close:
            info["targetPriority"] = "Close";
            break;
        case TargetPriority::Strong:
            info["targetPriority"] = "Strong";
            break;
        default:
            info["targetPriority"] = "Unknown";
            break;
    }

    // At the beginning, no upgrades are available
    info["descriptionTop"] = "";
    info["descriptionMiddle"] = "";
    info["descriptionBottom"] = "";

    info["upgradeCostTop"] = std::to_string(upgradeTop->getCost());
    info["upgradeDescriptionTop"] = upgradeTop->getDescription();
    info["upgradeCostMiddle"] = std::to_string(upgradeMiddle->getCost());
    info["upgradeDescriptionMiddle"] = upgradeMiddle->getDescription();
    info["upgradeCostBottom"] = std::to_string(upgradeBottom->getCost());
    info["upgradeDescriptionBottom"] = upgradeBottom->getDescription();
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
}

void DartMonkey::drawRange() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
    }
}

void DartMonkey::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void DartMonkey::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Dart Monkey
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(upgradeTop->getCost() * upgradeCost);
    info["upgradeCostMiddle"] = std::to_string(upgradeMiddle->getCost() * upgradeCost);
    info["upgradeCostBottom"] = std::to_string(upgradeBottom->getCost() * upgradeCost);
}

LogicInfo DartMonkey::getInfo() {
    // info that need to be live-updated
    info["popCount"] = std::to_string(popCount);
    info["sell"] = std::to_string(static_cast<int>(cost * 0.70f));
    
    return this->info;
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