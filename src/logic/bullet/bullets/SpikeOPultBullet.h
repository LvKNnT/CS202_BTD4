#ifndef SPIKE_O_PULT_BULLET_H
#define SPIKE_O_PULT_BULLET_H

#include "../Bullet.h"

class SpikeOPultBullet : public Bullet {
public:
    SpikeOPultBullet();
    std::unique_ptr<Bullet> clone() const override;
    ~SpikeOPultBullet() override = default;

    // Override all methods from Bullet
    void loadTexture() override;

    void init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properites, AttackBuff attackBuff, int towerId) override;
    bool hit(int damage) override;
    void draw() const override;
    int die() override;
    std::vector<std::unique_ptr<Bullet>> getChild() override;

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
    
    void setRotation(float rotation) override;
};

#endif // SPIKE_O_PULT_BULLET_H