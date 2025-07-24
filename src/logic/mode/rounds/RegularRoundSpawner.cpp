#include "RegularRoundSpawner.h"
#include <iostream>

RegularRoundSpawner::RegularRoundSpawner() {
    init();
}

void RegularRoundSpawner::init() {
    // Initialize the round templates for different rounds
    
    roundTemplates[1] = Round(121, {
        {BloonType::Red, {false, false, false}, 20, 0.0f, 17.51f}
    });
    roundTemplates[2] = Round(137, {
        {BloonType::Red, {false, false, false}, 35, 0.0f, 19.00f}
    });
    roundTemplates[3] = Round(138, {
        {BloonType::Red, {false, false, false}, 10, 0.0f, 5.01f}, 
        {BloonType::Blue, {false, false, false}, 5, 5.70f, 7.95f}, 
        {BloonType::Red, {false, false, false}, 15, 9.71f, 16.71f}
    });
    roundTemplates[4] = Round(175, {
        {BloonType::Red, {false, false, false}, 25, 0.0f, 12.00f},
        {BloonType::Blue, {false, false, false}, 18, 7.90f, 10.40f},
        {BloonType::Red, {false, false, false}, 10, 14.51f, 17.31f}
    });
    roundTemplates[5] = Round(164, {
        {BloonType::Blue, {false, false, false}, 12, 0.0f, 5.14f},
        {BloonType::Red, {false, false, false}, 5, 5.70f, 7.98f},
        {BloonType::Blue, {false, false, false}, 15, 8.60f, 16.50f}
    });
}

const Round& RegularRoundSpawner::getRound(int roundNumber) const {
    // Find the round for the given round number
    auto it = roundTemplates.find(roundNumber);
    if (it != roundTemplates.end()) {
        return it->second;
    }

    // Should not be there
    std::cerr << "Round number not found: " << roundNumber << std::endl;
    return roundTemplates.at(1); // Return the first round as a fallback
}