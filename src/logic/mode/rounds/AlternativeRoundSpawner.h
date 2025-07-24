#ifndef ALTERNATIVE_ROUND_SPAWNER_H
#define ALTERNATIVE_ROUND_SPAWNER_H

#include "../Round.h"
#include <map>

class AlternativeRoundSpawner {
private:
    // Round templates for different rounds
    std::map<int, Round> roundTemplates; 
public:
    AlternativeRoundSpawner();
    ~AlternativeRoundSpawner() = default;

    void init();

    const Round& getRound(int roundNumber) const;
};

#endif // REGULAR_ROUND_SPAWNER_H