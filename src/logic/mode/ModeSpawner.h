#ifndef MODE_SPANNER_H
#define MODE_SPANNER_H

#include "Mode.h"
#include "ModeUnits.h"
#include <map>
#include <memory>

class ModeSpawner {
private:
    struct ModeTypeCompare {
        bool operator()(const ModeType& a, const ModeType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<ModeType, std::unique_ptr<Mode>, ModeTypeCompare> modeTemplates;

public:
    ModeSpawner();
    ~ModeSpawner() = default;

    void init();

    const Mode& getMode(ModeType type) const;
};

#endif // MODE_SPANNER_H