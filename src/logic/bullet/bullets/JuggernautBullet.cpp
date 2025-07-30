#include "JuggernautBullet.h"
#include "../../../core/Game.h"

JuggernautBullet::JuggernautBullet()
    : Bullet(BulletType::Juggernaut) {
    tag = "JuggernautBullet";
}

std::unique_ptr<Bullet> JuggernautBullet::clone() const {
    return std::make_unique<JuggernautBullet>(*this);
}

void JuggernautBullet::loadTexture() {
    // Load the texture for the Juggernaut bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/JuggernautBullet.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

void JuggernautBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff attackBuff, int towerId) {
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

bool JuggernautBullet::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void JuggernautBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the juggernaut bullet

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(texture, 
                   {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Juggernaut texture with the specified position and rotation
}

int JuggernautBullet::die() {
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

std::vector<std::unique_ptr<Bullet>> JuggernautBullet::getChild() {
    // JuggernautBullet does not spawn child bullets, so return an empty vector
    return {};
}

Rectangle JuggernautBullet::getBoundingBox() const {
    return { position.x, position.y, size.x, size.y };
}

bool JuggernautBullet::isActive() const {
    return isActiveFlag;
}

void JuggernautBullet::setActive(bool active) {
    isActiveFlag = active;
}

void JuggernautBullet::setRotation(float rotation) {
    this->rotation = rotation;
}