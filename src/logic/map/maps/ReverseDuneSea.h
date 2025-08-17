#ifndef REVERSE_DUNE_SEA_H
#define REVERSE_DUNE_SEA_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseDuneSea : public Map {
public:    
    ReverseDuneSea();
    std::unique_ptr<Map> clone() const override;
    ~ReverseDuneSea() override = default;

    Point::Type getPointType(Vector2 position) const override;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // DUNE_SEA_H