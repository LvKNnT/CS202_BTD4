#include "Airburst.h"
#include "../../../core/Game.h"

#include "raymath.h"
#include <fstream>

#include "Sub.h"

Airburst::Airburst()
    : Bullet(BulletType::Airburst) {
    tag = "Airburst";
}

std::unique_ptr<Bullet> Airburst::clone() const {
    return std::make_unique<Airburst>(*this);
}

void Airburst::loadTexture() {
    // Load the texture for the Airburst bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/ArmourPiercingAirburstDart.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void Airburst::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
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

int Airburst::run() {
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

void Airburst::update(std::vector<std::shared_ptr<Enemy>>& enemyList) {
    // no special update
}

bool Airburst::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void Airburst::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    // DrawCircleV(position, 10, RED); // Example drawing a red circle for the Airburst

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
                   WHITE); // Draw the Airburst texture with the specified position and rotation
}

int Airburst::die() {
    // Logic for when the Airburst bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Airburst bullet reached the end of its life!" << std::endl;
    flog.close();

    return -1;
}

std::vector<std::unique_ptr<Bullet>> Airburst::getChild() {
    if(hasReleased) {
        return {}; // If already released, return empty vector
    }

    hasReleased = true; // Mark as released

    std::vector<std::unique_ptr<Bullet>> children;
    float baseAngle = rotation;
    float spread = 30.0f; // degrees between each sub-bullet

    BulletProperties childProperties = properties;
    childProperties.canTrace = false; // Sub-bullets do not trace

    for (int i = 0; i < 3; ++i) {
        float angle = baseAngle + spread * (i - 1); // -1, 0, 1 for left, center, right
        auto child = std::make_unique<Sub>();

        if(i == 0) child->loadTexture();

        child->init(
            position,
            {20.0f, 20.0f},
            angle,
            damage,
            speed,
            1, // Each sub-bullet has 1 pierce
            lifeSpan * 0.5f, // Shorter lifespan for sub-bullets
            childProperties,
            normalDebuff,
            moabDebuff,
            attackBuff,
            towerId
        );
        children.push_back(std::move(child));
    }

    return children;

    return {};
}

Rectangle Airburst::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Airburst::isActive() const {
    // Logic to determine if the Airburst bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the Airburst is always active for this example
}

void Airburst::setActive(bool active) {
    // Logic to set the active state of the Airburst bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Airburst bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void Airburst::setRotation(float rotation) {
    // Set the rotation of the Airburst bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}

