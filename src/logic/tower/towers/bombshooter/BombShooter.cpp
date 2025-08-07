#include "BombShooter.h"

#include "../../../../core/Game.h"
#include "../../../skill/Skill.h"

#include "../../../attack/attacks/BombAttack.h"
#include "../../../attack/patterns/NormalAttack.h"

#include "BiggerBombs.h"
#include "FasterReload.h"
#include "ExtraRange.h"

BombShooter::BombShooter(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::BombShooter, 375) {
    /**
     * cost = 375
     */

    tag = "BombShooter";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 160.0f
     * * cooldown = 1.5f
     * * * damage = 1
     * * * speed = 360
     * * * pierce = 22
     * * * lifeSpan = 2.0f
     * * * properties = {true, false, true, false, true} // canHitCamo, canHitLead, canHitFrozen, canHitRegrow, canHitBlack
     */
    attacks.push_back(std::make_unique<BombAttack>(160.0f, 1.5f, position, towerId, 1, 360, 22, 2.0f, BulletProperties(true, false, true, true, false, true), BloonDebuff(), BloonDebuff())); 
    attackPattern = std::make_unique<NormalAttack>(); 
    skill = nullptr;

    // Upgrade Path
    upgradeTop = std::make_unique<BiggerBombs>();
    upgradeMiddle = std::make_unique<FasterReload>();
    upgradeBottom = std::make_unique<ExtraRange>();
    
    // Info section
    info["name"] = "Bomb Shooter";
    info["description"] = "Launches a powerful bomb at the Bloons. Slow rate of fire but affects a radius around the explosion.";
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

BombShooter::BombShooter(const BombShooter& other)
: Tower(other) {
}

std::unique_ptr<Tower> BombShooter::clone() const {
    return std::make_unique<BombShooter>(*this);
}

void BombShooter::loadTexture() {
    // Load the texture for the Dart Monkey tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/Bomb_Shooter.png");
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {70.0f, 70.0f}; // Set the size of the Bomb Shooter tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures(); 
}

void BombShooter::update() {
    // Bomb Shooter has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update();
}

void BombShooter::setRotation(float rotation) {
    this->rotation = rotation;
}

void BombShooter::draw() const {
    // Draw the Dart Monkey tower using raylib functions
    // DrawCircleV(position, 10, YELLOW); // Example drawing a yellow circle for the tower

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(
        Game::Instance().getTextureManager().getTexture(tag),
        {0, 0, (float) Game::Instance().getTextureManager().getTexture(tag).width, (float) Game::Instance().getTextureManager().getTexture(tag).height},
        {draw_position.x, draw_position.y, size.x, size.y},
        {size.x / 2.0f, size.y / 2.0f},
        rotation,
        WHITE); // Draw the Bomb Shooter texture with the specified position and rotation

    // Draw the upgrades
    upgradeTextureHandler.draw(getBoundingBox());

    // draw the hitbox
    // Rectangle hitbox = getBoundingBox();
    // hitbox.x += size.x / 2.0f; // Adjust hitbox position
    // hitbox.y += size.y / 2.0f; // Adjust hitbox position
    // DrawRectanglePro(hitbox, {size.x / 2.0f, size.y / 2.0f}, rotation, Fade(GREEN, 0.5f)); // Draw the hitbox with a semi-transparent green color
}

void BombShooter::drawRange() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        DrawCircleV(position, attack->getRange() * attackBuff.rangeRatio + attackBuff.range, Fade(GRAY, 0.5f)); // Draw the attack range
    }
}

void BombShooter::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void BombShooter::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Dart Monkey
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo BombShooter::getInfo() {
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

Rectangle BombShooter::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool BombShooter::isActive() const {
    return isActiveFlag;
}

void BombShooter::setActive(bool active) {
    isActiveFlag = active;
}