#ifndef MONKEYLANE_H
#define MONKEYLANE_H

#include "../../../core/Game.h"
#include "../Map.h"

class MonkeyLane : public Map {
public:
    MonkeyLane();
    std::unique_ptr<Map> clone() const override;
    ~MonkeyLane() override = default;

    Point::Type getEnemyPointType(Vector2 position) const override;

    void loadTexture() override;
    void update() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
};

#endif // MONKEYLANE_H