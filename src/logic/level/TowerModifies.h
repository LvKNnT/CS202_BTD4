#ifndef TOWER_MODIFIES_H
#define TOWER_MODIFIES_H

// This class shows the modifications that can be applied to a tower
class TowerModifies {
public:
    TowerModifies(float cost = 1.0f, float upgradeCost = 1.0f)
        : cost(cost), upgradeCost(upgradeCost) {}

    // Copy constructor
    TowerModifies(const TowerModifies& other)
        : cost(other.cost), upgradeCost(other.upgradeCost) {}

    // Assignment operator
    TowerModifies& operator=(const TowerModifies& other) {
        if (this != &other) {
            cost = other.cost;
            upgradeCost = other.upgradeCost;
        }
        return *this;
    }

    float cost;        // Cost of the tower
    float upgradeCost; // Cost to upgrade the tower
};

#endif // TOWER_MODIFIES_H