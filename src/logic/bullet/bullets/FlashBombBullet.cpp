#include "FlashBombBullet.h"
#include "FlashBombExplosionBullet.h"
#include "../../../core/Game.h"

#include <fstream>

FlashBombBullet::FlashBombBullet()
    : Bullet(BulletType::FlashBomb) {
    tag = "FlashBombBullet";
}

std::unique_ptr<Bullet> FlashBombBullet::clone() const {
    return std::make_unique<FlashBombBullet>(*this);
}

void FlashBombBullet::loadTexture() {
    // Load the texture for the FlashBombBullet bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/FlashBombBullet.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void FlashBombBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
    this->pierce = pierce;
    this->lifeSpan = lifeSpan;
    this->properties = properties;
    this->normalDebuff = normalDebuff;
    this->moabDebuff = moabDebuff;
    this->attackBuff = attackBuff; 
    this->towerId = towerId; 
}

int FlashBombBullet::run() {
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

void FlashBombBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool FlashBombBullet::hit(int damage) {
    // only 1 pierce
    
    return true;
}

int FlashBombBullet::getDamage(BloonType type, bool isCamo) {
    // the projectile deals no dmg, only the explosion does
    return 0;
}

void FlashBombBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    //DrawCircleV(position, 10, RED); // Example drawing a red circle for the FlashBombBullet

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

int FlashBombBullet::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "FlashBombBullet bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> FlashBombBullet::getChild() {
    // should be only one pierce so no condition is needed

    std::vector<std::unique_ptr<Bullet>> children;

    children.push_back(std::make_unique<FlashBombExplosionBullet>());
    for(int i = 0; i < 1; ++i) {
        children[i]->loadTexture();
        children[i]->init(position, 
                          {size.x * 2, size.y * 2}, 
                          rotation, 
                          damage, 
                          0, 
                          pierce, 
                          0.1f, 
                          properties, 
                          normalDebuff, 
                          moabDebuff, 
                          attackBuff, 
                          towerId);
    }

    return children;
}

Rectangle FlashBombBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool FlashBombBullet::isActive() const {
    // Logic to determine if the FlashBombBullet bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the FlashBombBullet is always active for this example
}

void FlashBombBullet::setActive(bool active) {
    // Logic to set the active state of the FlashBombBullet bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "FlashBombBullet bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void FlashBombBullet::setRotation(float rotation) {
    // Set the rotation of the FlashBombBullet bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}