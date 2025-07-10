#include "TowerModifier.h"
#include <iostream>

TowerModifier::TowerModifier() {
    init();
}

TowerModifier::TowerModifier(const TowerModifier& other) {
    if (this != &other) {
        towerModifiesTemplates = other.towerModifiesTemplates; // Use the map's copy constructor
    } else {
        // should not be here
        std::cerr << "TowerModifier copy constructor called on self-assignment." << std::endl;
    }
}

TowerModifier& TowerModifier::operator=(const TowerModifier& other) {
    if (this != &other) {
        towerModifiesTemplates = other.towerModifiesTemplates; // Use the map's assignment operator
    } else {
        // should not be here
        std::cerr << "TowerModifier assignment operator called on self-assignment." << std::endl;
    }
    return *this;
}

std::unique_ptr<TowerModifier> TowerModifier::clone() const {
    return std::make_unique<TowerModifier>(*this);
}

void TowerModifier::init() {
    /**
     * Initialize difficulty modifiers
     * Since the modifiers are static, we can hardcode them here
     * These values are adjusted based on game design
     */

    towerModifiesTemplates[Difficulty::Easy] = TowerModifies(1.0f, 1.0f);
    towerModifiesTemplates[Difficulty::Medium] = TowerModifies(1.1f, 1.1f);
    towerModifiesTemplates[Difficulty::Hard] = TowerModifies(1.25f, 1.25f);
    towerModifiesTemplates[Difficulty::Impoppable] = TowerModifies(1.25f, 1.25f);
}

const TowerModifies& TowerModifier::getDifficultyUnits(Difficulty type) const {
    // Find the difficulty modifier for the given type
    auto it = towerModifiesTemplates.find(type);
    if (it != towerModifiesTemplates.end()) {
        return it->second;
    } 

    // should not be here
    std::cerr << "Difficulty type not found: " << static_cast<int>(type) << std::endl;
    return towerModifiesTemplates.at(Difficulty::Easy); // Return default modifier if not found
}