// #ifndef JUNGLE_H
// #define JUNGLE_H

// #include "../../../core/Game.h"
// #include "../Map.h"

// // 0 is normal path 1 is reverse path 
// class Jungle : public Map {
// public:
//     Jungle();
//     std::unique_ptr<Map> clone() const override;
//     ~Jungle() override = default;

//     void loadTexture() override;
//     void update() override;

//     std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) override;
// };

// #endif // JUNGLE_H