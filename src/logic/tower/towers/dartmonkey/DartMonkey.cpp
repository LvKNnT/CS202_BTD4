#include "DartMonkey.h"

#include "../../../../core/Game.h"

#include "../../../attack/attacks/DartAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "../../../skill/Skill.h"
#include "SharpShots.h"
#include "QuickShots.h"
#include "LongRangeDarts.h"

DartMonkey::DartMonkey(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::DartMonkey, 200) {
    /**
     * cost = 200
     */

    tag = "DartMonkey";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 128.0f
     * * cooldown = 0.95f
     * * * damage = 1
     * * * speed = 600
     * * * pierce = 2
     * * * lifeSpan = 0.25f
     * * * properties = BulletProperties::normal()
     */
    attacks.push_back(std::make_unique<DartAttack>(128.0f, 0.95f, position, towerId, 1, 600, 2, 20.5f, BulletProperties::normal(), BloonDebuff(), BloonDebuff()));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>()); // Set the attack pattern to NormalAttack 
    skill = nullptr;

    // Upgrade Path
    upgradeTop = std::make_unique<SharpShots>();
    upgradeMiddle = std::make_unique<QuickShots>();
    upgradeBottom = std::make_unique<LongRangeDarts>();

    // Info section
    info["name"] = "Dart Monkey";
    info["description"] = "Throw a single dart at nearby Bloons. Short range and low pierce but cheap";
    info["cost"] = std::to_string(cost);
    info["popCount"] = std::to_string(popCount);
    info["sellPrice"] = std::to_string(static_cast<int>(cost * 0.75f));

    // At the beginning, no upgrades are available
    info["nameTop"] = "NoUpgrade";
    info["nameMiddle"] = "NoUpgrade";
    info["nameBottom"] = "NoUpgrade";
    info["descriptionTop"] = "";
    info["descriptionMiddle"] = "";
    info["descriptionBottom"] = "";
    
    info["upgradeNameTop"] = upgradeTop->getName();
    info["upgradeCostTop"] = std::to_string(upgradeTop->getCost());
    info["upgradeDescriptionTop"] = upgradeTop->getDescription();
    info["upgradeNameMiddle"] = upgradeMiddle->getName();
    info["upgradeDescriptionMiddle"] = upgradeMiddle->getDescription();
    info["upgradeCostMiddle"] = std::to_string(upgradeMiddle->getCost());
    info["upgradeNameBottom"] = upgradeBottom->getName();
    info["upgradeDescriptionBottom"] = upgradeBottom->getDescription();
    info["upgradeCostBottom"] = std::to_string(upgradeBottom->getCost());
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
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {60.0f, 60.0f}; // Set the size of the Dart Monkey tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures();
}

void DartMonkey::update() {
    // Dart Monkey has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update(); 
}

void DartMonkey::setRotation(float rotation) {
    this->rotation = rotation;
}

void DartMonkey::draw() const {
    // Draw the Dart Monkey tower using raylib functions
    // DrawCircleV(position, 10, YELLOW); // Example drawing a yellow circle for the tower

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(Game::Instance().getTextureManager().getTexture(tag), 
                   {0, 0, (float) Game::Instance().getTextureManager().getTexture(tag).width, (float) Game::Instance().getTextureManager().getTexture(tag).height},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Dart Monkey texture with the specified position and rotation

    // Draw the upgrades
    upgradeTextureHandler.draw(getBoundingBox());

    // draw the hitbox
    // Rectangle hitbox = getBoundingBox();
    // hitbox.x += size.x / 2.0f; // Adjust hitbox position
    // hitbox.y += size.y / 2.0f; // Adjust hitbox position
    // DrawRectanglePro(hitbox, {size.x / 2.0f, size.y / 2.0f}, rotation, Fade(GREEN, 0.5f)); // Draw the hitbox with a semi-transparent green color
}

void DartMonkey::drawRange() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        DrawCircleV(position, attack->getRange() * attackBuff.rangeRatio + attackBuff.range, Fade(GRAY, 0.5f)); // Draw the attack range
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
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo DartMonkey::getInfo() {
    // info that need to be live-updated
    info["popCount"] = std::to_string(popCount);
    info["sell"] = std::to_string(static_cast<int>(cost * 0.70f));

    // sadly, using switch/case here
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

    // for skill
    if(skill) {
        info["skillName"] = skill->getName();
        info["skillCooldown"] = std::to_string(skill->getCooldownTime());
        info["skillTimer"] = std::to_string(skill->getTimer());
    }
    else {
        info["skillName"] = "No Skill";
        info["skillCooldown"] = "0";
        info["skillTimer"] = "0";
    }
    
    return this->info;
}

Rectangle DartMonkey::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool DartMonkey::isActive() const {
    return isActiveFlag;
}

void DartMonkey::setActive(bool active) {
    isActiveFlag = active;
}