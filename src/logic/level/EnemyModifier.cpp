#include "EnemyModifier.h"
#include <iostream>

EnemyModifier::EnemyModifier() {
    init();
}

EnemyModifier::EnemyModifier(const EnemyModifier& other) {
    if (this != &other) {
        enemyModifiesTemplates = other.enemyModifiesTemplates; // Use the map's copy constructor
    } else {
        // should not be here
    }
}

EnemyModifier& EnemyModifier::operator=(const EnemyModifier& other) {
    if (this != &other) {
        enemyModifiesTemplates = other.enemyModifiesTemplates; // Use the map's assignment operator
    } else {
        // should not be here
    }
    return *this;
}

std::unique_ptr<EnemyModifier> EnemyModifier::clone() const {
    return std::make_unique<EnemyModifier>(*this);
}

void EnemyModifier::init() {
    /**
     * Initialize difficulty modifiers
     * Since the modifiers are static, we can hardcode them here
     * These values are adjusted based on game design
     */

    enemyModifiesTemplates[Difficulty::Easy] = EnemyModifies(1.0f, 1.0f, 1.0f);
    enemyModifiesTemplates[Difficulty::Medium] = EnemyModifies(1.1f, 1.1f, 1.0f);
    enemyModifiesTemplates[Difficulty::Hard] = EnemyModifies(1.25f, 1.25f, 1.0f);
    enemyModifiesTemplates[Difficulty::Impoppable] = EnemyModifies(1.25f, 1.25f, 1.0f);
}

const EnemyModifies& EnemyModifier::getDifficultyUnits(Difficulty type) const {
    // Find the difficulty modifier for the given type
    auto it = enemyModifiesTemplates.find(type);
    if (it != enemyModifiesTemplates.end()) {
        return it->second;
    } 

    // should not be here
    std::cerr << "Difficulty type not found: " << static_cast<int>(type) << std::endl;
    return enemyModifiesTemplates.at(Difficulty::Easy); // Return default modifier if not found
}