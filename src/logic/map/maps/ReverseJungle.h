#ifndef REVERSEJUNGLE_H
#define REVERSEJUNGLE_H

#include "../../../core/Game.h"
#include "../Map.h"

class ReverseJungle : public Map {
public:
    ReverseJungle();
    std::unique_ptr<Map> clone() const override;
    ~ReverseJungle() override = default;

    void loadTexture() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
private:
    int pathIdxCount;
};

#endif // REVERSEJUNGLE_H