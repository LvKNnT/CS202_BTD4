#ifndef TOWER_MODIFIER_H
#define TOWER_MODIFIER_H

#include "DifficultyUnits.h"
#include "TowerModifies.h"

#include <map>
#include <memory>

class TowerModifier {
private:
    struct DifficultyCompare {
        bool operator()(const Difficulty& a, const Difficulty& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<Difficulty, TowerModifies, DifficultyCompare> towerModifiesTemplates;

public:
    TowerModifier();
    TowerModifier(const TowerModifier& other);
    ~TowerModifier() = default;

    TowerModifier& operator=(const TowerModifier& other);
    std::unique_ptr<TowerModifier> clone() const;

    void init();

    // Returns a reference to the TowerModifies for the given type
    const TowerModifies& getDifficultyUnits(Difficulty type) const;
};

#endif // TOWER_MODIFIER_H