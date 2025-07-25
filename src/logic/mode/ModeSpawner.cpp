#include "ModeSpawner.h"
#include <iostream>

#include "modes/ClassicMode.h"
#include "modes/ApopalypseMode.h"
#include "modes/AlternativeMode.h"
#include "modes/ReverseMode.h"

ModeSpawner::ModeSpawner() {
    init();
}

void ModeSpawner::init() {
    // Initialize mode templates
    modeTemplates[ModeType::Classic] = std::make_unique<ClassicModePlayer>();
    modeTemplates[ModeType::Apopalypse] = std::make_unique<ApopalypseModePlayer>();
    modeTemplates[ModeType::Alternative] = std::make_unique<AlternativeModePlayer>();
    modeTemplates[ModeType::Reverse] = std::make_unique<ReverseModePlayer>();
}

const Mode& ModeSpawner::getMode(ModeType type) const {
    auto it = modeTemplates.find(type);
    if (it != modeTemplates.end()) {
        return *(it->second);
    }
    

    // should not be here
    std::cerr << "Mode type not found!\n";
    return *(modeTemplates.at(ModeType::Classic)); // Default to Classic mode if not found
}