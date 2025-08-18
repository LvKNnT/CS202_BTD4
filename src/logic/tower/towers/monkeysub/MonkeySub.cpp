#include "MonkeySub.h"

#include "../../../../core/Game.h"

#include "../../../attack/attacks/SubAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "../../../skill/Skill.h"

#include "LongerRange.h"
#include "BarbedDarts.h"
#include "TwinGuns.h"

MonkeySub::MonkeySub(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::MonkeySub, 350) {
    /**
     * cost = 350
     */

    tag = "MonkeySub";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 84.0f
     * * cooldown = 0.75f
     * * * damage = 1
     * * * speed = 340
     * * * pierce = 2
     * * * lifeSpan = 10.0f
     * * * properties = BulletProperties::normal()
     */
    attacks.push_back(std::make_unique<SubAttack>(84.0f, 1.59f, position, towerId, 1, 340, 2, 10.0f, BulletProperties::normal().getITracing(104.0f, TargetPriority::First), BloonDebuff(), BloonDebuff()));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>()); // Set the attack pattern to NormalAttack 
    skill = nullptr;
    passiveSkills.clear(); // Clear any existing passive skills

    // Upgrade Path
    upgradeTop = std::make_unique<LongerRange>();
    upgradeMiddle = std::make_unique<BarbedDarts>();
    upgradeBottom = std::make_unique<TwinGuns>();

    // Info section
    info["name"] = "Monkey Sub";
    info["description"] = "Can shoot Bloons it can see anywhere on the screen with a long-range rifle, and pops 2 layers off Bloons hit by it.";
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

MonkeySub::MonkeySub(const MonkeySub& other)
: Tower(other) {
}

std::unique_ptr<Tower> MonkeySub::clone() const {
    return std::make_unique<MonkeySub>(*this);
}

void MonkeySub::loadTexture() {
    // Load the texture for the Monkey Sub tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/MonkeySub.png");
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {60.0f, 80.0f}; // Set the size of the Monkey Sub tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures();
}

void MonkeySub::update() {
    // Monkey Sub has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update(); 
}

void MonkeySub::setRotation(float rotation) {
    this->rotation = rotation;
}

void MonkeySub::draw() const {
    // Draw the Monkey Sub tower using raylib functions
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
                   WHITE); // Draw the Monkey Sub texture with the specified position and rotation

    // Draw the upgrades
    upgradeTextureHandler.draw(getBoundingBox());

    // draw the hitbox
    // Rectangle hitbox = getBoundingBox();
    // hitbox.x += size.x / 2.0f; // Adjust hitbox position
    // hitbox.y += size.y / 2.0f; // Adjust hitbox position
    // DrawRectanglePro(hitbox, {size.x / 2.0f, size.y / 2.0f}, rotation, Fade(GREEN, 0.5f)); // Draw the hitbox with a semi-transparent green color
}

void MonkeySub::drawRange() const {
    // Draw the range of attacks
    float maxRange = 0.0f;
    for(const auto& attack : attacks) {
        maxRange = std::max(maxRange, attack->getRange() * attackBuff.rangeRatio + attackBuff.range);
    }

    DrawCircleV(position, maxRange, Fade(GRAY, 0.5f)); // Draw the attack range
}

void MonkeySub::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void MonkeySub::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Monkey Sub
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo MonkeySub::getInfo() {
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

bool MonkeySub::isPlaceable(Point::Type pointType) const {
    // Check if the tower can be placed based on the point type

    return pointType == Point::Type::None; // Temporary
    
    return pointType == Point::Type::Water; // Monkey Sub can only be placed on water
}

Rectangle MonkeySub::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool MonkeySub::isActive() const {
    return isActiveFlag;
}

void MonkeySub::setActive(bool active) {
    isActiveFlag = active;
}