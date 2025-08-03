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
    std::string name; 

public:
    Skill(float cooldown, const std::string& name);
    virtual ~Skill();

    virtual std::unique_ptr<Skill> clone() const = 0; 

    virtual void update() = 0;
    virtual bool canActivateSkill() const = 0;
    virtual float getCooldown() const = 0;
    virtual void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers) = 0;
    virtual void inActivateSkill() = 0; 
};

#endif // SKIL_H