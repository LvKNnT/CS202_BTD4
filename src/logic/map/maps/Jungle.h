#ifndef JUNGLE_H
#define JUNGLE_H

#include "../../../core/Game.h"
#include "../Map.h"

class Jungle : public Map {
public:
    Jungle();
    std::unique_ptr<Map> clone() const override;
    ~Jungle() override = default;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // JUNGLE_H