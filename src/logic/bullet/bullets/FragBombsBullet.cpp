#include "FragBombsBullet.h"
#include "../../../core/Game.h"

#include "BombFragment.h"
#include "BombExplosion.h"
#include "raymath.h"

FragBombsBullet::FragBombsBullet()
    : Bullet(BulletType::FragBombs) {
    tag = "FragBombs";
}

std::unique_ptr<Bullet> FragBombsBullet::clone() const {
    return std::make_unique<FragBombsBullet>(*this);
}

void FragBombsBullet::loadTexture() {
    // Load the texture for the Frag Bombs bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Bomb.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void FragBombsBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int FragBombsBullet::run() {
    float elapsedTime = GetFrameTime();

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

void FragBombsBullet::update(std::vector<std::unique_ptr<Enemy>>& enemyList) {
    // no special update
}

bool FragBombsBullet::hit(int damage) {
    // only 1 pierce

    return true;
}

void FragBombsBullet::draw() const {
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

Rectangle FragBombsBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool FragBombsBullet::isActive() const {
    return isActiveFlag;
}

void FragBombsBullet::setActive(bool active) {
    isActiveFlag = active;
}

int FragBombsBullet::die() {
    isActiveFlag = false; // Mark the bullet as inactive
    return 0; // Return 0 to indicate the bullet has died
}

std::vector<std::unique_ptr<Bullet>> FragBombsBullet::getChild() {
    std::vector<std::unique_ptr<Bullet>> children;

    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());
    children.push_back(std::make_unique<BombFragment>());

    BulletProperties fragmentProperties = BulletProperties(false, true, true, false, false, true);
    fragmentProperties.canCamo = properties.canCamo;
    fragmentProperties += attackBuff.properties;

    for(int i = 0; i < 8; ++i) {
        children[i]->loadTexture();
        children[i]->init(position, 
                          {10.0f, 10.0f}, 
                          fmodf(rotation + i * 45.0f, 360.0f),
                          1 + attackBuff.damage * 2, 
                          600 * attackBuff.speedRatio + attackBuff.speed, 
                          1 * attackBuff.pierceRatio + attackBuff.pierce, 
                          0.25f * attackBuff.lifeSpanRatio, 
                          fragmentProperties,
                          normalDebuff, 
                          moabDebuff, 
                          attackBuff, 
                          towerId);
    }

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


    return children; 
}

void FragBombsBullet::setRotation(float rotation) {
    this->rotation = rotation;
}
