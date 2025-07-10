#ifndef MONKEYLANE_H
#define MONKEYLANE_H

#include "../../../core/Game.h"
#include "../Map.h"

class MonkeyLane : public Map {
public:
    MonkeyLane();
    std::unique_ptr<Map> clone() const override;
    ~MonkeyLane() override = default;

    void loadTexture() override;
    void update() override;
};

#endif // MONKEYLANE_H