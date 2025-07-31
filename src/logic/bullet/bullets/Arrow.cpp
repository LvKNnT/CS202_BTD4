#include "Arrow.h"
#include "../../../core/Game.h"

Arrow::Arrow()
    : Bullet(BulletType::Arrow) {
    tag = "Arrow";
}

std::unique_ptr<Bullet> Arrow::clone() const {
    return std::make_unique<Arrow>(*this);
}

void Arrow::loadTexture() {
    // Load the texture for the Arrow bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Arrow.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void Arrow::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff attackBuff, int towerId) {
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

bool Arrow::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void Arrow::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the arrow

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
                   WHITE); // Draw the Arrow texture with the specified position and rotation
}

int Arrow::die() {
    // Reset the enemy's id memory
    hitEnemies.clear();

    return 0; // Indicating that the bullet has ended its life
}

std::vector<std::unique_ptr<Bullet>> Arrow::getChild() {
    // Arrow bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle Arrow::getBoundingBox() const {
    return { position.x, position.y, size.x, size.y };
}

bool Arrow::isActive() const {
    return isActiveFlag;
}

void Arrow::setActive(bool active) {
    isActiveFlag = active;
}

void Arrow::setRotation(float rotation) {
    this->rotation = rotation;
}