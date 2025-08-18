#ifndef SUBMERGE_H
#define SUBMERGE_H

#include "../Bullet.h"

class Submerge : public Bullet {
public:
    Submerge();
    std::unique_ptr<Bullet> clone() const override;
    ~Submerge() override = default;

    // Override all methods from Bullet
    void loadTexture() override;

    void init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properites, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) override;
    int run() override;
    void update(std::vector<std::shared_ptr<Enemy>>& enemyList) override;
    bool hit(int damage) override;
    int getDamage(BloonType type, bool isCamo) override;

    void draw() const override;
    int die() override;
    std::vector<std::unique_ptr<Bullet>> getChild() override;

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
    
    void setRotation(float rotation) override;
private:
    int initialLifeSpan;
};

#endif // SUBMERGE_H