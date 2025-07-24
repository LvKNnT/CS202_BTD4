#ifndef REVERSE_ROUND_SPAWNER_H
#define REVERSE_ROUND_SPAWNER_H

#include "../Round.h"
#include <map>

class ReverseRoundSpawner {
private:
    // Round templates for different rounds
    std::map<int, Round> roundTemplates; 
public:
    ReverseRoundSpawner();
    ~ReverseRoundSpawner() = default;

    void init();

    const Round& getRound(int roundNumber) const;
};

#endif // REVERSE_ROUND_SPAWNER_H