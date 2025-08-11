#include "RecursiveClusterBullet.h"
#include "../../../core/Game.h"

#include "BombExplosion.h"
#include "Bomb.h"
#include "ClusterBombBullet.h"

#include "raymath.h"

RecursiveClusterBullet::RecursiveClusterBullet()
    : Bullet(BulletType::ClusterBomb) {
    tag = "RecursiveClusterBullet";
}

std::unique_ptr<Bullet> RecursiveClusterBullet::clone() const {
    return std::make_unique<RecursiveClusterBullet>(*this);
}

void RecursiveClusterBullet::loadTexture() {
    // Load the texture for the Cluster Bomb bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Bomb.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void RecursiveClusterBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int RecursiveClusterBullet::run() {
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

void RecursiveClusterBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // No special update logic for Cluster Bomb Bullet
}

bool RecursiveClusterBullet::hit(int damage) {
    // only 1 pierce

    return true; 
}

void RecursiveClusterBullet::draw() const {
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

Rectangle RecursiveClusterBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool RecursiveClusterBullet::isActive() const {
    return isActiveFlag;
}

void RecursiveClusterBullet::setActive(bool active) {
    isActiveFlag = active;
}

int RecursiveClusterBullet::die() {
    isActiveFlag = false; // Mark the bullet as inactive

    return 0; // Return 0 to indicate the bullet has died
}

std::vector<std::unique_ptr<Bullet>> RecursiveClusterBullet::getChild() {
    std::vector<std::unique_ptr<Bullet>> children;

    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    children.push_back(std::make_unique<ClusterBombBullet>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());
    // children.push_back(std::make_unique<Bomb>());

    // let the children move for 0.5s first
    float elapsedTime = 0.05f;
    
    for(int i = 0; i < 8; ++i) {
        float childRotation = rotation + i * 45.0f; 
        Vector2 direction = {cosf(childRotation * (PI / 180.0f)), sinf(childRotation * (PI / 180.0f))};
        Vector2 childrenPosition = position; 
        childrenPosition.x += direction.x * speed * elapsedTime;
        childrenPosition.y += direction.y * speed * elapsedTime;

        children[i]->loadTexture();
        children[i]->init(childrenPosition, 
                          Vector2Add({45.0f, 45.0f}, attackBuff.size),
                          childRotation, // Spread the bombs around the cluster
                          2 + attackBuff.damage, 
                          speed, 
                          24 * attackBuff.pierceRatio + attackBuff.pierce, 
                          0.1f * attackBuff.lifeSpanRatio, // Short lifespan for the explosion
                          properties, 
                          normalDebuff,
                          moabDebuff,
                          attackBuff,
                          towerId);
    }
    
    // Create a BombExplosion bullet as a child
    children.push_back(std::make_unique<BombExplosion>());
    children.back()->loadTexture();
    children.back()->init(position, 
                      {size.x * 2, size.y * 2}, 
                      rotation, 
                      damage, 
                      0, 
                      pierce, 
                      0.1f, // Short lifespan for the explosion
                      properties, 
                      normalDebuff,
                      moabDebuff,
                      attackBuff,
                      towerId);

    return children;
}

void RecursiveClusterBullet::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation of the bullet
}