#ifndef DART_H
#define DART_H

#include "../../../core/Game.h"
#include "../Bullet.h"

class Dart : public Bullet {
public:
    Dart();
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