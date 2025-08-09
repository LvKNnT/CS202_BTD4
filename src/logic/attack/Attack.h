#ifndef ATTACK_H
#define ATTACK_H

#include "../bullet/BulletManager.h"
#include "AttackUnits.h"
#include "AttackPattern.h"
#include <memory>
#include <string>

class Enemy;

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
    std::unique_ptr<AttackPattern> attackPattern; // Strategy pattern for different attack patterns

    // Bullet properties
    int damage; 
    int speed; 
    int pierce; 
    float lifeSpan;
    BulletProperties properties; 
    BloonDebuff normalDebuff; 
    BloonDebuff moabDebuff; 

    std::string tag;    
    int towerId; // ID of the tower that created this attack, if applicable
public:
    Attack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);    
    Attack(const Attack& other);
    virtual ~Attack() = default;

    virtual std::unique_ptr<Attack> clone() const = 0; // Pure virtual function for cloning the attack

    virtual bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const = 0; // Pure virtual function to check if the target is in range
    virtual void update() = 0; // for tower update
    virtual void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) = 0; // Pure virtual function for executing the attack

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

    Vector2 getPosition() const;
    std::string getTag() const;
    BulletProperties& getProperties();
    BloonDebuff& getNormalDebuff();
    BloonDebuff& getMoabDebuff();
    void setAttackPattern(std::unique_ptr<AttackPattern> newAttackPattern);
    std::unique_ptr<AttackPattern>& getAttackPattern();
    virtual bool isRotateTower() const;
    virtual float getRotateTower(float rotation);
    int getTowerId() const;
};

#endif // ATTACK_H