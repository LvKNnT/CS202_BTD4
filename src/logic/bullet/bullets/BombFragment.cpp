#include "BombFragment.h"
#include "../../../core/Game.h"

BombFragment::BombFragment()
    : Bullet(BulletType::BombFragment) {
    tag = "BombFragment";
}

std::unique_ptr<Bullet> BombFragment::clone() const {
    return std::make_unique<BombFragment>(*this);
}

void BombFragment::loadTexture() {
    // Load the texture for the Bomb Fragment bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/BombFragment.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void BombFragment::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int BombFragment::run() {
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

void BombFragment::update(std::vector<std::unique_ptr<Enemy>>& enemyList) {
    // no special update
}

bool BombFragment::hit(int damage) {
    MySound hitSound("BombExplosion");
    hitSound.start();
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void BombFragment::draw() const {
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

int BombFragment::die() {
    // Remove the bullet from the game
    isActiveFlag = false;

    // Return 0 to indicate that the bullet has died
    return 0;
}

std::vector<std::unique_ptr<Bullet>> BombFragment::getChild() {
    // Bomb Fragment does not spawn any child bullets
    return {};
}

Rectangle BombFragment::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool BombFragment::isActive() const {
    return isActiveFlag;
}

void BombFragment::setActive(bool active) {
    isActiveFlag = active;
}

void BombFragment::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation of the bullet
}