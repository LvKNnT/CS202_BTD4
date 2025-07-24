#ifndef RESOURCE_SPAWNER_H
#define RESOURCE_SPAWNER_H

#include <map>
#include "Resource.h"
#include "../level/DifficultyUnits.h"

class ResourceSpawner {
private:
    // Resource templates for different difficulties
    struct DifficultyCompare {
        bool operator()(const Difficulty& a, const Difficulty& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<Difficulty, Resource> resourceTemplates;

public:
    ResourceSpawner();
    ~ResourceSpawner() = default;

    void init();

    const Resource& getResource(Difficulty difficulty) const;
};

#endif // RESOURCE_SPAWNER_H