#include "ShrapnelShotBullet.h"
#include "../../../core/Game.h"

#include "Shrapnel.h"

#include "raymath.h"
#include <fstream>

ShrapnelShotBullet::ShrapnelShotBullet()
    : Bullet(BulletType::ShrapnelShot) {
    tag = "ShrapnelShotBullet";
}

std::unique_ptr<Bullet> ShrapnelShotBullet::clone() const {
    return std::make_unique<ShrapnelShotBullet>(*this);
}

void ShrapnelShotBullet::loadTexture() {
    // Load the texture for the ShrapnelShotBullet bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Dart.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void ShrapnelShotBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int ShrapnelShotBullet::run() {
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

void ShrapnelShotBullet::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool ShrapnelShotBullet::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void ShrapnelShotBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    // DrawCircleV(position, 10, RED); // Example drawing a red circle for the ShrapnelShotBullet

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
                   WHITE); // Draw the ShrapnelShotBullet texture with the specified position and rotation
}

int ShrapnelShotBullet::die() {
    // Logic for when the ShrapnelShotBullet bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "ShrapnelShotBullet bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> ShrapnelShotBullet::getChild() {
    std::vector<std::unique_ptr<Bullet>> children;

    // Create 5 Shrapnel bullets as children in a 45 degree cone
    BulletProperties childProperties = BulletProperties::normal();
    for (int i = -2; i <= 2; ++i) {
        auto shrapnelBullet = std::make_unique<Shrapnel>();
        if(i == -2) shrapnelBullet->loadTexture();
        
        shrapnelBullet->init(position, {10.0f, 10.0f}, rotation + i * 9.0f, damage / 5 + 1, speed, 2, 0.1f, childProperties, normalDebuff, moabDebuff, attackBuff, towerId);
        children.push_back(std::move(shrapnelBullet));
    }

    return children;
}

Rectangle ShrapnelShotBullet::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool ShrapnelShotBullet::isActive() const {
    // Logic to determine if the ShrapnelShotBullet bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the ShrapnelShotBullet is always active for this example
}

void ShrapnelShotBullet::setActive(bool active) {
    // Logic to set the active state of the ShrapnelShotBullet bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "ShrapnelShotBullet bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void ShrapnelShotBullet::setRotation(float rotation) {
    // Set the rotation of the ShrapnelShotBullet bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}


