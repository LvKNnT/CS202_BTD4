#ifndef REVERSEJUNGLE_H
#define REVERSEJUNGLE_H

#include "../../../core/Game.h"
#include "../Map.h"

// 0 is normal path 1 is reverse path 
class ReverseJungle : public Map {
public:
    ReverseJungle();
    std::unique_ptr<Map> clone() const override;
    ~ReverseJungle() override = default;

    void loadTexture() override;
    void update() override;

    std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
};

#endif // REVERSEJUNGLE_H