#ifndef DART_H
#define DART_H

#include "../../../core/Game.h"
#include "../Bullet.h"

class Dart : public Bullet {
public:
    Dart(Vector2 position = {0.0f, 0.0f}, Vector2 size = {10.0f, 10.0f}, float rotation = 0.0f, int damage = 1, int speed = 200, int pierce = 1, float lifeSpan = 60.0f);
    std::unique_ptr<Bullet> clone() const override;
    ~Dart() override = default;

    // Override all methods from Bullet
    void loadTexture() override;

    bool hit(int damage) override;
    void draw() const override;
    void die() override;

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
    
    void setRotation(float rotation) override;
private:

};

#endif // DART_H