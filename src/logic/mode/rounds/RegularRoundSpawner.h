#ifndef REGULAR_ROUND_SPAWNER_H
#define REGULAR_ROUND_SPAWNER_H

#include "../Round.h"
#include <map>

class RegularRoundSpawner {
private:
    // Round templates for different rounds
    std::map<int, Round> roundTemplates; 
public:
    RegularRoundSpawner();
    ~RegularRoundSpawner() = default;

    void init();

    const Round& getRound(int roundNumber) const;
};

#endif // REGULAR_ROUND_SPAWNER_H