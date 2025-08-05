#include "TracingDart.h"
#include "../../../core/Game.h"

#include "raymath.h"
#include <fstream>

TracingDart::TracingDart()
    : Bullet(BulletType::TracingDart) {
    tag = "TracingDart";
}

std::unique_ptr<Bullet> TracingDart::clone() const {
    return std::make_unique<TracingDart>(*this);
}

void TracingDart::loadTexture() {
    // Load the texture for the TracingDart bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Dart.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void TracingDart::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int TracingDart::run() {
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

void TracingDart::update(std::vector<std::unique_ptr<Enemy>>& enemyList) {
    if(tracingId != -1) return;

    float distance = 1000000.0f; // just a large number
    float range = 100.0f;
    int closestEnemyId = -1;
    float closestEnemyDistance = range; // just a large number
    Vector2 closestEnemyPosition = {-1.0f, -1.0f};
    for(auto& enemy : enemyList) {
        if(enemy->isActive() 
        && hitEnemies.find(enemy->getId()) == hitEnemies.end() 
        && Vector2Distance(position, enemy->getPosition()) <= closestEnemyDistance) {
            closestEnemyDistance = Vector2Distance(position, enemy->getPosition());
            closestEnemyPosition = enemy->getPosition();
            closestEnemyId = enemy->getId();   
        }
    }

    if(closestEnemyId == -1) {
        tracingId = -2;
        return;
    }
    tracingId = closestEnemyId;
    rotation = atan2f(closestEnemyPosition.y - position.y, closestEnemyPosition.x - position.x) * (180.0f / PI);
}

bool TracingDart::hit(int damage) {
    pierce -= damage;

    tracingId = -1;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void TracingDart::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the dart

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
                   WHITE); // Draw the TracingDart texture with the specified position and rotation
}

int TracingDart::die() {
    // Logic for when the TracingDart bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "TracingDart bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> TracingDart::getChild() {
    // TracingDart bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle TracingDart::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool TracingDart::isActive() const {
    // Logic to determine if the TracingDart bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the dart is always active for this example
}

void TracingDart::setActive(bool active) {
    // Logic to set the active state of the TracingDart bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "TracingDart bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void TracingDart::setRotation(float rotation) {
    // Set the rotation of the TracingDart bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}

