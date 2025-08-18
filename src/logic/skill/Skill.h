#ifndef SKIL_H
#define SKIL_H

#include <vector>
#include <memory>

#include "SkillUnits.h"

class Skill {
    friend class LogicManager;

protected:
    // Skill properties
    float cooldown; 
    float timer; 
    bool isSkillActivating;
    std::string name; 

public:
    Skill(float cooldown, const std::string& name);
    virtual ~Skill();

    virtual std::unique_ptr<Skill> clone() const = 0; 

    virtual void loadTexture() = 0; // Load the texture for the skill

    virtual void update() = 0;
    virtual bool canActivateSkill() const = 0;
    virtual float getCooldown() const = 0;
    virtual void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) = 0;
    virtual void inActivateSkill() = 0; 

    const std::string& getName() const;
    float getCooldownTime() const;
    float getTimer() const;
    bool getISkillsActivating() const;
    void setCooldown(float newCooldown);
    void setTimer(float newTimer);
    void setIsSkillActivating(float newIsSkillActivating);
};

#endif // SKIL_H