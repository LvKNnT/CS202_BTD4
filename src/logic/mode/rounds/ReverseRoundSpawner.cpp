#include "ReverseRoundSpawner.h"
#include <iostream>

ReverseRoundSpawner::ReverseRoundSpawner() {
    init();
}

void ReverseRoundSpawner::init() {
    // Initialize the round templates for different rounds
    
    roundTemplates[1] = Round(121, {
        {BloonType::Red, {false, false, false}, 20, 0.0f, 17.51f}
    });
    roundTemplates[2] = Round(137, {
        {BloonType::Red, {false, false, false}, 35, 0.0f, 19.00f}
    });
    roundTemplates[3] = Round(138, {
        {BloonType::Red, {false, false, false}, 15, 0.0f, 7.00f}, 
        {BloonType::Blue, {false, false, false}, 5, 8.76f, 11.01f}, 
        {BloonType::Red, {false, false, false}, 10, 11.61f, 16.71f}
    });
    roundTemplates[4] = Round(175, {
        {BloonType::Red, {false, false, false}, 10, 0.0f, 2.80f},
        {BloonType::Red, {false, false, false}, 25, 5.31f, 17.31f},
        {BloonType::Red, {false, false, false}, 18, 6.91f, 9.41f}
    });
    roundTemplates[5] = Round(164, {
        {BloonType::Blue, {false, false, false}, 15, 0.0f, 7.90f},
        {BloonType::Red, {false, false, false}, 5, 8.52f, 10.80f},
        {BloonType::Blue, {false, false, false}, 15, 11.36f, 16.50f}
    });
}

const Round& ReverseRoundSpawner::getRound(int roundNumber) const {
    // Find the round for the given round number
    auto it = roundTemplates.find(roundNumber);
    if (it != roundTemplates.end()) {
        return it->second;
    }

    // Should not be there
    std::cerr << "Round number not found: " << roundNumber << std::endl;
    return roundTemplates.at(1); // Return the first round as a fallback
}