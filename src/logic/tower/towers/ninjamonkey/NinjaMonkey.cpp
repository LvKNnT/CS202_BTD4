#include "NinjaMonkey.h"

#include "../../../../core/Game.h"

#include "../../../attack/attacks/ShurikenAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "../../../skill/Skill.h"
#include "../../../skill/skills/SuperMonkeyFanClubSkill.h"

#include "NinjaDiscipline.h"
#include "Distraction.h"
#include "SeekingShuriken.h"

NinjaMonkey::NinjaMonkey(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::NinjaMonkey, 400), shinobiStack(0), hasShinobiTactics(false) {
    /**
     * cost = 400
     */

    tag = "NinjaMonkey";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 120.0f
     * * cooldown = 0.62f
     * * * damage = 1
     * * * speed = 750
     * * * pierce = 2
     * * * lifeSpan = 0.25f
     * * * properties = BulletProperties::normal()
     */
    attacks.push_back(std::make_unique<ShurikenAttack>(120.0f, 0.62f, position, towerId, 1, 750, 2, 20.5f, BulletProperties::shuriken(), BloonDebuff(), BloonDebuff())); 
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>()); // Set the attack pattern to NormalAttack
    skill = nullptr;
    passiveSkills.clear(); // Clear any existing passive skills

    // Upgrade Path
    upgradeTop = std::make_unique<NinjaDiscipline>();
    upgradeMiddle = std::make_unique<Distraction>();
    upgradeBottom = std::make_unique<SeekingShuriken>();

    // Info section
    info["name"] = "Ninja Monkey";
    info["description"] = "Stealthy and fast Monkey that throws bladed shurikens to pop the Bloons. Can target Camo Bloons.";
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

NinjaMonkey::NinjaMonkey(const NinjaMonkey& other)
: Tower(other) {
}

std::unique_ptr<Tower> NinjaMonkey::clone() const {
    return std::make_unique<NinjaMonkey>(*this);
}

void NinjaMonkey::loadTexture() {
    // Load the texture for the Dart Monkey tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/Ninja_Monkey.png");
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {60.0f, 60.0f}; // Set the size of the Ninja Monkey tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures();
}

void NinjaMonkey::update() {
    // Ninja Monkey has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update(); 
}

void NinjaMonkey::setRotation(float rotation) {
    this->rotation = rotation;
}

void NinjaMonkey::draw() const {
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

void NinjaMonkey::drawRange() const {
    // Draw the range of attacks
    float maxRange = 0.0f;
    for(const auto& attack : attacks) {
        maxRange = std::max(maxRange, attack->getRange() * attackBuff.rangeRatio + attackBuff.range);
    }

    DrawCircleV(position, maxRange, Fade(GRAY, 0.5f)); // Draw the attack range
}

void NinjaMonkey::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void NinjaMonkey::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Dart Monkey
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo NinjaMonkey::getInfo() {
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
    } else {
        info["skillName"] = "No Skill";
        info["skillCooldown"] = "0";
        info["skillTimer"] = "0";
    }

    return this->info;
}

bool NinjaMonkey::isPlaceable(Point::Type pointType) const {
    // Check if the tower can be placed based on the point type
    return pointType == Point::Type::None; // Ninja Monkey can only be placed on land
}

Rectangle NinjaMonkey::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool NinjaMonkey::isActive() const {
    return isActiveFlag;
}

void NinjaMonkey::setActive(bool active) {
    isActiveFlag = active;
}

void NinjaMonkey::addShinobiStatck() {
    shinobiStack++;
    if(shinobiStack <= MAXShinobiStack) {
        attackBuff.cooldownRatio *= 0.92;
        attackBuff.pierceRatio += 0.08;
    }
}

void NinjaMonkey::delShinobiStack() {
    shinobiStack--;
    if(shinobiStack < MAXShinobiStack) {
        attackBuff.cooldownRatio /= 0.92;
        attackBuff.pierceRatio -= 0.08;
    }
}

void NinjaMonkey::activateShinobiTactics() {
    // Check whenever this Ninja Monkey has Shinobi Tactics upgrade
    if(upgradeMiddle->getName() == "Bloon Sabotage" && !hasShinobiTactics) {
        hasShinobiTactics = true;
        addApplideShinobiTactics(towerId); // add itself
        addShinobiStatck();
    }
}

bool NinjaMonkey::getHasShinobiTactics() {
    return hasShinobiTactics;
}

bool NinjaMonkey::addApplideShinobiTactics(int towerId) {
    if(!hasShinobiTactics || appliedShinobiTactics[towerId]) return 0;
    appliedShinobiTactics[towerId] = 1;
    return 1; 
}
