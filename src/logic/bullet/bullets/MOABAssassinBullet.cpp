#include "MOABAssassinBullet.h"
#include "../../../core/Game.h"

#include "BombExplosion.h"

MOABAssassinBullet::MOABAssassinBullet()
    : Bullet(BulletType::MOABAssassin) {
    tag = "MOABAssassinBullet";
}

std::unique_ptr<Bullet> MOABAssassinBullet::clone() const {
    return std::make_unique<MOABAssassinBullet>(*this);
}

void MOABAssassinBullet::loadTexture() {
    // Load the texture for the MOAB Assassin bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/ZOMG_Bomb.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void MOABAssassinBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

    // only hit MOAB
    this->properties.canNormal = false; // Cannot hit normal bloons
    this->properties.canMoab = true; // Can hit MOABs
}

int MOABAssassinBullet::run() {
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

void MOABAssassinBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool MOABAssassinBullet::hit(int damage) {
    // only 1 pierce

    return true;
}

void MOABAssassinBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

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

int MOABAssassinBullet::die() {
    isActiveFlag = false; // Mark the bullet as inactive
    return 0; // Return 0 to indicate the bullet has died
}

std::vector<std::unique_ptr<Bullet>> MOABAssassinBullet::getChild() {
// should be only one pierce so no condition is needed

    std::vector<std::unique_ptr<Bullet>> children;

    children.push_back(std::make_unique<BombExplosion>());
    for(int i = 0; i < 1; ++i) {
        children[i]->loadTexture();
        children[i]->init(position, 
                          {size.x * 2, size.y * 2}, 
                          rotation, 
                          3 + attackBuff.damage, 
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

Rectangle MOABAssassinBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool MOABAssassinBullet::isActive() const {
    return isActiveFlag; // Return the active status of the bullet
}

void MOABAssassinBullet::setActive(bool active) {
    isActiveFlag = active; // Set the active status of the bullet
}

void MOABAssassinBullet::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation of the bullet
}
