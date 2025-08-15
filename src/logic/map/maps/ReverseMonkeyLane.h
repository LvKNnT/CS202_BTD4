#ifndef REVERSEMONKEYLANE_H
#define REVERSEMONKEYLANE_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseMonkeyLane : public Map {
public:
    ReverseMonkeyLane();
    std::unique_ptr<Map> clone() const override;
    ~ReverseMonkeyLane() override = default;

    Point::Type getPointType(Vector2 position) const override; // For Tower
    
    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
};

#endif // REVERSEMONKEYLANE_H