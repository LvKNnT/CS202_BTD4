#ifndef ENEMITYMODIFIER_H
#define ENEMITYMODIFIER_H

#include "DifficultyUnits.h"
#include "EnemyModifies.h"

#include <map>
#include <memory>

class EnemyModifier {
private:
    struct DifficultyCompare {
        bool operator()(const Difficulty& a, const Difficulty& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<Difficulty, EnemyModifies, DifficultyCompare> enemyModifiesTemplates;

public:
    EnemyModifier();
    EnemyModifier(const EnemyModifier& other);
    ~EnemyModifier() = default;

    EnemyModifier& operator=(const EnemyModifier& other);
    std::unique_ptr<EnemyModifier> clone() const;

    void init();

    // Returns a reference to the DifficultyUnits for the given type
    const EnemyModifies& getDifficultyUnits(Difficulty type) const;
};

#endif // ENEMITYMODIFIER_H