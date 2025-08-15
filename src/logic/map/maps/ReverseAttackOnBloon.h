#ifndef REVERSE_ATTACK_ON_BLOON_H
#define REVERSE_ATTACK_ON_BLOON_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseAttackOnBloon : public Map {
public:    
    ReverseAttackOnBloon();
    std::unique_ptr<Map> clone() const override;
    ~ReverseAttackOnBloon() override = default;

    Point::Type getPointType(Vector2 position) const override;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // ATTACK_ON_BLOON_H