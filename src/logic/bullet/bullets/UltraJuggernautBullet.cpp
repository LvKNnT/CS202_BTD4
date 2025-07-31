#include "UltraJuggernautBullet.h"
#include "../../../core/Game.h"

#include "JuggernautBullet.h"

UltraJuggernautBullet::UltraJuggernautBullet()
    : Bullet(BulletType::UltraJuggernaut) {
    tag = "UltraJuggernautBullet";
}

std::unique_ptr<Bullet> UltraJuggernautBullet::clone() const {
    return std::make_unique<UltraJuggernautBullet>(*this);
}

void UltraJuggernautBullet::loadTexture() {
    // Load the texture for the Ultra Juggernaut bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/UltraJuggernautBullet.png");
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

void UltraJuggernautBullet::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff attackBuff, int towerId) {
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

    this->maxPierce = pierce; 
    this->counter = 0; 
}

bool UltraJuggernautBullet::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void UltraJuggernautBullet::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the ultra juggernaut bullet

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
                   WHITE); // Draw the Ultra Juggernaut texture with the specified position and rotation
}

int UltraJuggernautBullet::die() {
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

std::vector<std::unique_ptr<Bullet>> UltraJuggernautBullet::getChild() {
    if(pierce > maxPierce * (1.0f - 1.0f / (2.0f - counter))) return {};
    std::cerr << "pierce: " << pierce << ", maxPierce: " << maxPierce << ", counter: " << counter << std::endl;

    std::vector<std::unique_ptr<Bullet>> children;

    children.push_back(std::make_unique<JuggernautBullet>());
    children.push_back(std::make_unique<JuggernautBullet>());
    children.push_back(std::make_unique<JuggernautBullet>());
    children.push_back(std::make_unique<JuggernautBullet>());
    children.push_back(std::make_unique<JuggernautBullet>());
    children.push_back(std::make_unique<JuggernautBullet>());

    for(int i = 0; i < 6; ++i) {
        children[i]->init(position, size, rotation + i * 60.0f, 2, 300, 50, 1.0f, properties, attackBuff, towerId);
    }

    ++counter;
    return children; 
}

Rectangle UltraJuggernautBullet::getBoundingBox() const {
    return { position.x, position.y, size.x, size.y };
}

bool UltraJuggernautBullet::isActive() const {
    return isActiveFlag;
}

void UltraJuggernautBullet::setActive(bool active) {
    isActiveFlag = active;
}

void UltraJuggernautBullet::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation of the bullet
}