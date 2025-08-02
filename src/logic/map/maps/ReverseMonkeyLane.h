#ifndef REVERSEMONKEYLANE_H
#define REVERSEMONKEYLANE_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseMonkeyLane : public Map {
public:
    ReverseMonkeyLane();
    std::unique_ptr<Map> clone() const override;
    ~ReverseMonkeyLane() override = default;

    void loadTexture() override;
    void update() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
};

#endif // REVERSEMONKEYLANE_H