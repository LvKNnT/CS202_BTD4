#include "FlashBombExplosionBullet.h"
#include "../../../core/Game.h"

#include <fstream>

FlashBombExplosionBullet::FlashBombExplosionBullet()
    : Bullet(BulletType::FlashBombExplosion) {
    tag = "FlashBombExplosionBullet";
}

std::unique_ptr<Bullet> FlashBombExplosionBullet::clone() const {
    return std::make_unique<FlashBombExplosionBullet>(*this);
}

void FlashBombExplosionBullet::loadTexture() {
    // Load the texture for the FlashBombExplosionBullet bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/FlashBombExplosionBullet.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void FlashBombExplosionBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int FlashBombExplosionBullet::run() {
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

void FlashBombExplosionBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool FlashBombExplosionBullet::hit(int damage) {
    MySound hitSound("BombExplosion");
    hitSound.start();
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

int FlashBombExplosionBullet::getDamage(BloonType type, bool isCamo) {
    // only deal dmg at the moment it spawns
    if(lifeSpan < initialLifeSpan) return 0;

    int damage = this->damage;

    if(isCamo) damage += normalDebuff.bonusCamoDamage;
    if(type == BloonType::Lead || type == BloonType::Ddt) damage += normalDebuff.bonusLeadDamage;

    if(type < BloonType::Moab) return damage + normalDebuff.bonusDamage; 

    return damage + moabDebuff.bonusDamage; // moab class
}

void FlashBombExplosionBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    //DrawCircleV(position, 10, RED); // Example drawing a red circle for the FlashBombExplosionBullet

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
                   WHITE); 
}

int FlashBombExplosionBullet::die() {
    // Logic for when the FlashBombExplosionBullet bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "FlashBombExplosionBullet bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> FlashBombExplosionBullet::getChild() {
    // FlashBombExplosionBullet bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle FlashBombExplosionBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool FlashBombExplosionBullet::isActive() const {
    // Logic to determine if the FlashBombExplosionBullet bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the FlashBombExplosionBullet is always active for this example
}

void FlashBombExplosionBullet::setActive(bool active) {
    // Logic to set the active state of the FlashBombExplosionBullet bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "FlashBombExplosionBullet bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void FlashBombExplosionBullet::setRotation(float rotation) {
    // Set the rotation of the FlashBombExplosionBullet bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}