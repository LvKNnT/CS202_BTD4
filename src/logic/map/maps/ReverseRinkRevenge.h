#ifndef REVERSE_RINK_REVENGE_H
#define REVERSE_RINK_REVENGE_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseRinkRevenge : public Map {
public:
    ReverseRinkRevenge();
    std::unique_ptr<Map> clone() const override;
    ~ReverseRinkRevenge() override = default;

    Point::Type getPointType(Vector2 position) const override; // For Tower

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // REVERSE_RINK_REVENGE_H