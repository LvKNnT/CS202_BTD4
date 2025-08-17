#ifndef DUNE_SEA_H
#define DUNE_SEA_H

#include "../../../core/Game.h"
#include "../Map.h"

class DuneSea : public Map {
public:    
    DuneSea();
    std::unique_ptr<Map> clone() const override;
    ~DuneSea() override = default;

    Point::Type getPointType(Vector2 position) const override;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // DUNE_SEA_H