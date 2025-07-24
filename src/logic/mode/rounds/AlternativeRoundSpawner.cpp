#include "AlternativeRoundSpawner.h"
#include <iostream>

AlternativeRoundSpawner::AlternativeRoundSpawner() {
    init();
}

void AlternativeRoundSpawner::init() {
    // Initialize the round templates for different rounds
    
    roundTemplates[1] = Round(121, {
        {BloonType::Blue, {false, false, false}, 10, 0.0f, 23.00f}
    });
    roundTemplates[2] = Round(157, {
        {BloonType::Red, {false, false, false}, 35, 0.0f, 15.00f},
        {BloonType::Red, {false, false, false}, 35, 18.0f, 25.00f}
    });
    roundTemplates[3] = Round(140, {
        {BloonType::Blue, {false, false, false}, 6, 0.0f, 5.10f}, 
        {BloonType::Blue, {false, false, true}, 5, 5.70f, 7.95f}, 
        {BloonType::Red, {false, false, false}, 15, 9.71f, 16.71f}
    });
    roundTemplates[4] = Round(180, {
        {BloonType::Blue, {false, false, false}, 15, 0.0f, 12.00f},
        {BloonType::Blue, {false, false, false}, 18, 7.90f, 10.40f},
        {BloonType::Red, {false, false, false}, 10, 14.51f, 17.31f}
    });
    roundTemplates[5] = Round(164, {
        {BloonType::Red, {false, true, false}, 12, 0.0f, 5.14f},
        {BloonType::Green, {false, false, false}, 3, 5.70f, 7.98f},
        {BloonType::Blue, {false, false, true}, 15, 8.60f, 16.50f},
        {BloonType::Red, {false, true, false}, 1, 19.40f, 19.40f}
    });
}

const Round& AlternativeRoundSpawner::getRound(int roundNumber) const {
    // Find the round for the given round number
    auto it = roundTemplates.find(roundNumber);
    if (it != roundTemplates.end()) {
        return it->second;
    }

    // Should not be there
    std::cerr << "Round number not found: " << roundNumber << std::endl;
    return roundTemplates.at(1); // Return the first round as a fallback
}