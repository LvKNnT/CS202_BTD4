#include "MasterBomberBullet.h"
#include "BombExplosion.h"
#include "FlashBombExplosionBullet.h"
#include "../../../core/Game.h"

#include <fstream>

MasterBomberBullet::MasterBomberBullet()
    : Bullet(BulletType::MasterBomber) {
    tag = "MasterBomber";
}

std::unique_ptr<Bullet> MasterBomberBullet::clone() const {
    return std::make_unique<MasterBomberBullet>(*this);
}

void MasterBomberBullet::loadTexture() {
    // Load the texture for the MasterBomberBullet bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/MasterBomber.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void MasterBomberBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int MasterBomberBullet::run() {
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

void MasterBomberBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool MasterBomberBullet::hit(int damage) {
    // only 1 pierce
    return true;
}

int MasterBomberBullet::getDamage(BloonType type, bool isCamo) {
    // the projectile deals no dmg, only the explosion does
    return 0;
}

void MasterBomberBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    //DrawCircleV(position, 10, RED); // Example drawing a red circle for the MasterBomberBullet

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

int MasterBomberBullet::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "MasterBomberBullet bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> MasterBomberBullet::getChild() {
    // should be only one pierce so no condition is needed
    std::vector<std::unique_ptr<Bullet>> children;
    children.push_back(std::make_unique<BombExplosion>());
    children.back()->loadTexture();
    children.back()->init(position, 
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

    children.push_back(std::make_unique<BombExplosion>());
    children.back()->loadTexture();
    children.back()->init(position, 
                        {size.x * 2, size.y * 2}, 
                        rotation, 
                        600, 
                        0, 
                        10, 
                        0.1f, 
                        properties, 
                        normalDebuff, 
                        moabDebuff, 
                        attackBuff, 
                        towerId);

    return children;
}

Rectangle MasterBomberBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool MasterBomberBullet::isActive() const {
    // Logic to determine if the Bomb bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the Bomb is always active for this example
}

void MasterBomberBullet::setActive(bool active) {
    // Logic to set the active state of the Bomb bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "MasterBomberBullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void MasterBomberBullet::setRotation(float rotation) {
    // Set the rotation of the Bomb bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}