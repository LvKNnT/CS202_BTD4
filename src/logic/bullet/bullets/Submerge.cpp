#include "Submerge.h"
#include "../../../core/Game.h"

#include <fstream>

Submerge::Submerge()
    : Bullet(BulletType::Submerge) {
    tag = "Submerge";
}

std::unique_ptr<Bullet> Submerge::clone() const {
    return std::make_unique<Submerge>(*this);
}

void Submerge::loadTexture() {
    // Load the texture for the Submerge bullet
    // Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Submerge.png");
    
    // Update size based on the loaded texture
    // size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    // size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void Submerge::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
    this->pierce = pierce;
    this->lifeSpan = lifeSpan;
    this->initialLifeSpan = lifeSpan; // Store the initial life span for later use
    this->properties = properties; 
    this->normalDebuff = normalDebuff;
    this->moabDebuff = moabDebuff;
    this->attackBuff = attackBuff; 
    this->towerId = towerId; 
}

int Submerge::run() {
    float elapsedTime = GetFrameTime();

    // update rotation if canTracing
    rotation = properties.getRotation(rotation, position);

    Vector2 direction = {cosf(rotation * (PI / 180.0f)), sinf(rotation * (PI / 180.0f))};
    position.x += direction.x * speed * elapsedTime;
    position.y += direction.y * speed * elapsedTime;

    Rectangle bulletBoundingBox = getBoundingBox();

    // Check if the bullet is still within the bounds of the map
    if(!Utils::isPositionInMap({bulletBoundingBox.x, bulletBoundingBox.y})
    || !Utils::isPositionInMap({bulletBoundingBox.x + bulletBoundingBox.width, bulletBoundingBox.y + bulletBoundingBox.height})) {
        return die();
    }

    // If the bullet is still active, return 0
    return 0;
}

void Submerge::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool Submerge::hit(int damage) {
    MySound hitSound("Submerge");
    hitSound.start();
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

int Submerge::getDamage(BloonType type, bool isCamo) {
    // only deal dmg at the moment it spawns
    if(lifeSpan < initialLifeSpan) return 0;

    int damage = this->damage;

    if(isCamo) damage += normalDebuff.bonusCamoDamage;
    if(type == BloonType::Lead || type == BloonType::Ddt) damage += normalDebuff.bonusLeadDamage;

    if(type < BloonType::Moab) return damage + normalDebuff.bonusDamage; 

    return damage + moabDebuff.bonusDamage; // moab class
}

void Submerge::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    //DrawCircleV(position, 10, RED); // Example drawing a red circle for the Submerge

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    float shrinkRatio = lifeSpan / initialLifeSpan;
    float radius = (size.x / 2.0f) * shrinkRatio;
    DrawCircleV(draw_position, radius, Color{173, 216, 230, 255}); // Light blue (RGB: 173,216,230)
}

int Submerge::die() {
    // Logic for when the Submerge bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Submerge bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> Submerge::getChild() {
    // Submerge bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle Submerge::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Submerge::isActive() const {
    // Logic to determine if the Submerge bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the Submerge is always active for this example
}

void Submerge::setActive(bool active) {
    // Logic to set the active state of the Submerge bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Submerge bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void Submerge::setRotation(float rotation) {
    // Set the rotation of the Submerge bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}