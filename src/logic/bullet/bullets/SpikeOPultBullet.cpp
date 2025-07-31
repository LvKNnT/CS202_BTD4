#include "SpikeOPultBullet.h"
#include "../../../core/Game.h"

#include "../../../utils/Utils.h"

#include <fstream>

SpikeOPultBullet::SpikeOPultBullet()
    : Bullet(BulletType::SpikeOPult) {
    tag = "SpikeOPultBullet";
}

std::unique_ptr<Bullet> SpikeOPultBullet::clone() const {
    return std::make_unique<SpikeOPultBullet>(*this);
}

void SpikeOPultBullet::loadTexture() {
    // Load the texture for the SpikeOPult bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/SpikeOPultBullet.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void SpikeOPultBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properites, AttackBuff attackBuff, int towerId) {
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
    this->pierce = pierce;
    this->lifeSpan = lifeSpan;
    this->properties = properties; 
    this->attackBuff = attackBuff; 
    this->towerId = towerId; 
}

bool SpikeOPultBullet::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void SpikeOPultBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the spike o pult bullet

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
                   WHITE); // Draw the SpikeOPultBullet texture with the specified position and rotation
}

int SpikeOPultBullet::die() {
    // Change rotation based on which edge was hit and bounce back based on incoming angle
    Rectangle bulletBox = getBoundingBox();
    bool isTopLeft = !Utils::isPositionInMap({bulletBox.x, bulletBox.y});
    bool isTopRight = !Utils::isPositionInMap({bulletBox.x + bulletBox.width, bulletBox.y});
    bool isBottomLeft = !Utils::isPositionInMap({bulletBox.x, bulletBox.y + bulletBox.height});
    bool isBottomRight = !Utils::isPositionInMap({bulletBox.x + bulletBox.width, bulletBox.y + bulletBox.height});
    
    // Top edge
    if(isTopLeft && isTopRight) {
        if(rotation < 90.0f) rotation = 360.0f - (rotation - 0.0f);
        else rotation = 270.0f - (rotation - 90.0f);
    }
    // Right edge
    if(isTopRight && isBottomRight) {
        if(rotation > 270.0f) rotation = 270.0f - (rotation - 270.0f);
        else rotation = 180.0f - (rotation - 0.0f);
    }
    // Bottom edge
    if(isBottomLeft && isBottomRight) {
        if(rotation > 270.0f) rotation = 90.0f - (rotation - 270.0f);
        else rotation = 180.0f - (rotation - 180.0f);
    }
    // Left edge
    if(isTopLeft && isBottomLeft) {
        if(rotation < 180.0f) rotation = 90.0f - (rotation - 90.0f);
        else rotation = 360.0f - (rotation - 180.0f);
    }

    // Reset the enemy's id memory
    hitEnemies.clear();

    return 0;
}

std::vector<std::unique_ptr<Bullet>> SpikeOPultBullet::getChild() {
    // SpikeOPultBullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle SpikeOPultBullet::getBoundingBox() const {
    return { position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y };
}

bool SpikeOPultBullet::isActive() const {
    return isActiveFlag; // Return the active state of the bullet
}

void SpikeOPultBullet::setActive(bool active) {
    isActiveFlag = active; // Set the active state of the bullet
}

void SpikeOPultBullet::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the bullet
}