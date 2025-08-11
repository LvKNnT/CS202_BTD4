#include "Shuriken.h"
#include "../../../core/Game.h"

#include "raymath.h"
#include <fstream>

Shuriken::Shuriken()
    : Bullet(BulletType::Shuriken) {
    tag = "Shuriken";
}

std::unique_ptr<Bullet> Shuriken::clone() const {
    return std::make_unique<Shuriken>(*this);
}

void Shuriken::loadTexture() {
    // Load the texture for the Shuriken bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Shuriken.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void Shuriken::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int Shuriken::run() {
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

void Shuriken::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool Shuriken::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void Shuriken::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    //DrawCircleV(position, 10, RED); // Example drawing a red circle for the Shuriken

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

int Shuriken::die() {
    // Logic for when the Shuriken bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Shuriken bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> Shuriken::getChild() {
    // Shuriken bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle Shuriken::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y}; 
}

bool Shuriken::isActive() const {
    // Logic to determine if the Shuriken bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the Shuriken is always active for this example
}

void Shuriken::setActive(bool active) {
    // Logic to set the active state of the Shuriken bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Shuriken bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void Shuriken::setRotation(float rotation) {
    // Set the rotation of the Dart bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}

