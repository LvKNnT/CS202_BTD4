#ifndef DDT_H
#define DDT_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Ddt : public Enemy {
public:
    Ddt(Vector2 position = {0.0f, 0.0f});
    ~Ddt() override;

    // Override all methods from Enemy
    void loadTexture() override;

    bool hit(int damage) override;
    void draw() const override;
    void die() override; 
    std::unique_ptr<Enemy> clone() const override;

    // Override all methods from GameObject
    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) override; // DDT has its own debuff handling
    void setRotation(float rotation) override;
    void setModifies(const EnemyModifies& modifies) override;
    void setProperties(const BloonProperties& properties) override;
    
private:

};
#endif // DDT_H
