#ifndef ATTACK_H
#define ATTACK_H

#include "../bullet/BulletManager.h"

// We use Strategy Pattern to create different attack types

class Attack {
    friend class LogicManager; // Allow LogicManager to access private members
    friend class TowerSpawner; // Allow TowerSpawner to access private members

protected:
    // Attack properties
    float range;
    float cooldown;
    float timer;
    Vector2 position;

    // Bullet properties
    int damage; 
    int speed; 
    int pierce; 
    float lifeSpan;

    int towerId; // ID of the tower that created this attack, if applicable
public:
    Attack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan);
    Attack(const Attack& other) = default;
    virtual ~Attack() = default;

    virtual std::unique_ptr<Attack> clone() const = 0; // Pure virtual function for cloning the attack

    virtual bool isInRange(const Rectangle& rec, const float rotation) const = 0; // Pure virtual function to check if the target is in range
    virtual void update(BulletManager& bulletManager, const Vector2& targetPosition) = 0; // Pure virtual function for executing the attack

    // Getters/Setters
    float getRange() const;
    void setRange(float newRange);
    float getCooldown() const;
    void setCooldown(float newCooldown);
    int getDamage() const;
    void setDamage(int newDamage);
    int getSpeed() const;
    void setSpeed(int newSpeed);
    int getPierce() const;
    void setPierce(int newPierce);
    float getLifeSpan() const;
    void setLifeSpan(float newLifeSpan);
};

#endif // ATTACK_H