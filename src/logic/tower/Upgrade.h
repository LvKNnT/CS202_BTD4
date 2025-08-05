#ifndef UPGRADE_H
#define UPGRADE_H

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

#include "../../interfaces/Drawable.h"
#include "../attack/Attack.h"

class Skill;

class Upgrade {
public:
    Upgrade(const std::string& name = "NoUpgrade", int cost = 0, const std::string& description = "");
    Upgrade(const Upgrade& other);
    virtual ~Upgrade() = default;
    
    virtual std::unique_ptr<Upgrade> clone() const; // Pure virtual function for cloning the upgrade

    // Getters
    const std::string& getName() const;
    int getCost() const;
    const std::string& getDescription();

    // Setters
    void setCost(int newCost);

    virtual void loadTexture();
    virtual void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill); // Update the upgrade effects on attacks and attack pattern
    virtual std::unique_ptr<Upgrade> buy();

protected:
    std::string name;        // Name of the upgrade
    int cost;                // Cost of the upgrade
    std::string description; // Description of the upgrade

    std::string tag;

    std::unique_ptr<Upgrade> nextUpgrade;
};

#endif // UPGRADE_H