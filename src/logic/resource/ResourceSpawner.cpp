#include "ResourceSpawner.h"
#include <iostream>

ResourceSpawner::ResourceSpawner() {
    init();
}

void ResourceSpawner::init() {
    // Initialize the resource templates for different difficulties
    resourceTemplates[Difficulty::Easy] = Resource(650, 200, 1, 1, 40);
    resourceTemplates[Difficulty::Medium] = Resource(650, 150, 1, 1, 60);
    resourceTemplates[Difficulty::Hard] = Resource(650, 100, 6, 6, 80);
    resourceTemplates[Difficulty::Impoppable] = Resource(650, 1, 6, 6, 100);
}

const Resource& ResourceSpawner::getResource(Difficulty difficulty) const {
    // Find the resource for the given difficulty type
    auto it = resourceTemplates.find(difficulty);
    if (it != resourceTemplates.end()) {
        return it->second;
    }

    // should not be here
    std::cerr << "Difficulty type not found: " << static_cast<int>(difficulty) << std::endl;
    return resourceTemplates.at(Difficulty::Easy); 
}