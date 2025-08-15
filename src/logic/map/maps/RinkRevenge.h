#ifndef RINK_REVENGE_H
#define RINK_REVENGE_H

#include "../../../core/Game.h"
#include "../Map.h"

class RinkRevenge : public Map {
public:    
    RinkRevenge();
    std::unique_ptr<Map> clone() const override;
    ~RinkRevenge() override = default;

    Point::Type getPointType(Vector2 position) const override;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // RINK_REVENGE_H