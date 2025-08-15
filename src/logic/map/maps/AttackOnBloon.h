#ifndef ATTACK_ON_BLOON_H
#define ATTACK_ON_BLOON_H

#include "../../../core/Game.h"
#include "../Map.h"

class AttackOnBloon : public Map {
public:    
    AttackOnBloon();
    std::unique_ptr<Map> clone() const override;
    ~AttackOnBloon() override = default;

    Point::Type getPointType(Vector2 position) const override;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // ATTACK_ON_BLOON_H