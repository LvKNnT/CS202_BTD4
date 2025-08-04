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

void Arrow::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int Arrow::run() {
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

void Arrow::update(std::vector<std::unique_ptr<Enemy>>& enemyList) {
    // no special update
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

    // DrawCircleV(position, 10, RED); // Example drawing a red circle for the arrow

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
return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};}

bool Arrow::isActive() const {
    return isActiveFlag;
}

void Arrow::setActive(bool active) {
    isActiveFlag = active;
}

void Arrow::setRotation(float rotation) {
    this->rotation = rotation;
}