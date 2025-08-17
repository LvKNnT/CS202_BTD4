#include "TackShooter.h"

#include "../../../../core/Game.h"

#include "../../../attack/attacks/DartAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "../../../skill/Skill.h"
TackShooter::TackShooter(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::TackShooter, 260) {
    /**
     * cost = 260
     */

    tag = "TackShooter";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = full map
     * * cooldown = 1.59f
     * * * damage = 2
     * * * speed = 2000
     * * * pierce = 1
     * * * lifeSpan = 0.1f
     * * * properties = BulletProperties::normal()
     */
    attacks.push_back(std::make_unique<DartAttack>(2000.0f, 1.59f, position, towerId, 2, 2000, 1, 0.1f, BulletProperties::normal().getITracing(0.0f, TargetPriority::First, true), BloonDebuff(), BloonDebuff()));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>()); // Set the attack pattern to NormalAttack 
    skill = nullptr;
    passiveSkills.clear(); // Clear any existing passive skills

    // Upgrade Path
    upgradeTop = std::make_unique<Upgrade>();
    upgradeMiddle = std::make_unique<Upgrade>();
    upgradeBottom = std::make_unique<Upgrade>();

    // Info section
    info["name"] = "Tack Shooter";
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

TackShooter::TackShooter(const TackShooter& other)
: Tower(other) {
}

std::unique_ptr<Tower> TackShooter::clone() const {
    return std::make_unique<TackShooter>(*this);
}

void TackShooter::loadTexture() {
    // Load the texture for the Tack Shooter tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Tack_Shooter/TackShooter.png");
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {60.0f, 60.0f}; // Set the size of the Tack Shooter tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures();
}

void TackShooter::update() {
    // Tack Shooter has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update(); 
}

void TackShooter::setRotation(float rotation) {
    this->rotation = rotation;
}

void TackShooter::draw() const {
    // Draw the Tack Shooter tower using raylib functions
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
                   WHITE); // Draw the Tack Shooter texture with the specified position and rotation

    // Draw the upgrades
    upgradeTextureHandler.draw(getBoundingBox());

    // draw the hitbox
    // Rectangle hitbox = getBoundingBox();
    // hitbox.x += size.x / 2.0f; // Adjust hitbox position
    // hitbox.y += size.y / 2.0f; // Adjust hitbox position
    // DrawRectanglePro(hitbox, {size.x / 2.0f, size.y / 2.0f}, rotation, Fade(GREEN, 0.5f)); // Draw the hitbox with a semi-transparent green color
}

void TackShooter::drawRange() const {
    // Use dummy range
    float range = 40.0f;
    DrawCircleV(position, range * attackBuff.rangeRatio + attackBuff.range, Fade(GRAY, 0.5f)); // Draw the attack range
}

void TackShooter::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void TackShooter::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Tack Shooter
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo TackShooter::getInfo() {
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

bool TackShooter::isPlaceable(Point::Type pointType) const {
    // Check if the tower can be placed based on the point type
    return pointType == Point::Type::None; // Tack Shooter can only be placed on land
}

Rectangle TackShooter::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool TackShooter::isActive() const {
    return isActiveFlag;
}

void TackShooter::setActive(bool active) {
    isActiveFlag = active;
}