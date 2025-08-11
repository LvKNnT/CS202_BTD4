#include "CaltropsBullet.h"
#include "../../../core/Game.h"
#include "../../map/maps/MonkeyLane.h"
#include "raymath.h"
#include <fstream>

CaltropsBullet::CaltropsBullet()
    : Bullet(BulletType::Caltrops) {
    tag = "CaltropsBullet";
}

std::unique_ptr<Bullet> CaltropsBullet::clone() const {
    return std::make_unique<CaltropsBullet>(*this);
}

void CaltropsBullet::loadTexture() {
    // Load the texture for the CaltropsBullet bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/CaltropsBullet.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void CaltropsBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int CaltropsBullet::run() {
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

void CaltropsBullet::update(std::vector<std::unique_ptr<Enemy>>& enemyList) {
     if(!Game::Instance().getGameLogic().isRoundRun()) {
        die();
        return;
    }

    // Rectangle bulletBox = getBoundingBox();
    // for(auto& enemy : enemyList) {
    //     if(enemy->isActive() && hitEnemies.find(enemy->getId()) == hitEnemies.end()) {
    //         Rectangle enemyBox = enemy->getBoundingBox();
    //         // Simple AABB collision check
    //         if (CheckCollisionRecs(bulletBox, enemyBox)) {
    //             std::cerr<<"Yes\n";
    //             // Bullet has hit this enemy
    //             speed = 0.0f;
    //             break;
    //         }
    //     }
    // }
}

bool CaltropsBullet::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void CaltropsBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the CaltropsBullet

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(Game::Instance().getTextureManager().getTexture(tag), 
                   {0, 0, size.x, size.y},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the CaltropsBullet texture with the specified position and rotation
}

int CaltropsBullet::die() {
    // Logic for when the CaltropsBullet bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "CaltropsBullet bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> CaltropsBullet::getChild() {
    // CaltropsBullet bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle CaltropsBullet::getBoundingBox() const {
    return {
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    }; 
}

bool CaltropsBullet::isActive() const {
    // Logic to determine if the CaltropsBullet bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the CaltropsBullet is always active for this example
}

void CaltropsBullet::setActive(bool active) {
    // Logic to set the active state of the CaltropsBullet bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "CaltropsBullet bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void CaltropsBullet::setRotation(float rotation) {
    // Set the rotation of the Dart bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}

