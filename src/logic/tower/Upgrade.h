#ifndef UPGRADE_H
#define UPGRADE_H

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

#include "../../interfaces/Drawable.h"
#include "../attack/Attack.h"

class Upgrade : public Drawable {
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
    virtual void draw() const override; 
    virtual void update(std::vector<std::unique_ptr<Attack> >& attacks);
    virtual std::unique_ptr<Upgrade> buy();

protected:
    std::string name;        // Name of the upgrade
    int cost;                // Cost of the upgrade
    std::string description; // Description of the upgrade

    Texture texture; // Texture for the upgrade, if applicable
    std::string tag;

    std::unique_ptr<Upgrade> nextUpgrade;
};

#endif // UPGRADE_H