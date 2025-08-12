#include "IceMonkey.h"

#include "../../../../core/Game.h"

#include "../../../attack/attacks/DartAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "../../../skill/Skill.h"
IceMonkey::IceMonkey(Vector2 position)
    : Tower(position, {0.0f, 0.0f}, 0.0f, TowerType::IceMonkey, 500) {
    /**
     * cost = 500
     */

    tag = "IceMonkey";
    isActiveFlag = true; // Set the tower to be active by default

    // Basic attack
    /**
     * * range = 40.0f
     * * cooldown = 2.4f
     * * * damage = 1
     * * * speed = instant
     * * * pierce = 40
     * * * lifeSpan = 0.1f
     * * * properties = BulletProperties::normal()
     */
    attacks.push_back(std::make_unique<DartAttack>(40.0f, 2.4f, position, towerId, 1, 2000, 40, 0.1f, BulletProperties::ice(), BloonDebuff().getIFreeze(1.5f), BloonDebuff()));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>()); // Set the attack pattern to NormalAttack 
    skill = nullptr;
    passiveSkill = nullptr;

    // Upgrade Path
    upgradeTop = std::make_unique<Upgrade>();
    upgradeMiddle = std::make_unique<Upgrade>();
    upgradeBottom = std::make_unique<Upgrade>();

    // Info section
    info["name"] = "Ice Monkey";
    info["description"] = "Pops and freezes nearby Bloons for a short time. Frozen Bloons are immune to sharp damage. Can't freeze White, Zebra or Lead Bloons.";
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

IceMonkey::IceMonkey(const IceMonkey& other)
: Tower(other) {
}

std::unique_ptr<Tower> IceMonkey::clone() const {
    return std::make_unique<IceMonkey>(*this);
}

void IceMonkey::loadTexture() {
    // Load the texture for the Ice Monkey tower
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/IceMonkey.png");
    Game::Instance().getTextureManager().loadTexture("NoUpgrade", "../assets/tower/NoUpgradeIcon.png");
    
    // Update size based on the loaded texture
    size.x = Game::Instance().getTextureManager().getTexture(tag).width;
    size.y = Game::Instance().getTextureManager().getTexture(tag).height;
    size = {60.0f, 60.0f}; // Set the size of the Ice Monkey tower

    // Get texture for the upgrade
    upgradeTop->loadTexture();
    upgradeMiddle->loadTexture();
    upgradeBottom->loadTexture();

    upgradeTextureHandler.loadTextures();
}

void IceMonkey::update() {
    // Ice Monkey has no special update.
    for(auto& attack : attacks) {
        attack->update();
    }
    if(skill) skill->update(); 
}

void IceMonkey::setRotation(float rotation) {
    this->rotation = rotation;
}

void IceMonkey::draw() const {
    // Draw the Ice Monkey tower using raylib functions
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
                   WHITE); // Draw the Ice Monkey texture with the specified position and rotation

    // Draw the upgrades
    upgradeTextureHandler.draw(getBoundingBox());

    // draw the hitbox
    // Rectangle hitbox = getBoundingBox();
    // hitbox.x += size.x / 2.0f; // Adjust hitbox position
    // hitbox.y += size.y / 2.0f; // Adjust hitbox position
    // DrawRectanglePro(hitbox, {size.x / 2.0f, size.y / 2.0f}, rotation, Fade(GREEN, 0.5f)); // Draw the hitbox with a semi-transparent green color
}

void IceMonkey::drawRange() const {
    // Use dummy range
    float range = 40.0f;
    DrawCircleV(position, range * attackBuff.rangeRatio + attackBuff.range, Fade(GRAY, 0.5f)); // Draw the attack range
}

void IceMonkey::drawPut() const {
    // Draw the range of attacks
    for(const auto& attack : attacks) {
        if(isActive()) {
            DrawCircleV(position, attack->getRange(), Fade(GRAY, 0.5f)); // Draw the attack range
        }
        else DrawCircleV(position, attack->getRange(), Fade(RED, 0.5f)); // Draw the attack range
    }
}

void IceMonkey::setModifies(const TowerModifies& modifies) {
    // Set the tower modifies for the Ice Monkey
    cost = static_cast<int>(cost * modifies.cost);
    upgradeCost = modifies.upgradeCost;

    // Update the info with the modified cost
    info["cost"] = std::to_string(cost);
    info["upgradeCostTop"] = std::to_string(static_cast<int>(upgradeTop->getCost() * upgradeCost));
    info["upgradeCostMiddle"] = std::to_string(static_cast<int>(upgradeMiddle->getCost() * upgradeCost));
    info["upgradeCostBottom"] = std::to_string(static_cast<int>(upgradeBottom->getCost() * upgradeCost));
}

LogicInfo IceMonkey::getInfo() {
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

Rectangle IceMonkey::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool IceMonkey::isActive() const {
    return isActiveFlag;
}

void IceMonkey::setActive(bool active) {
    isActiveFlag = active;
}