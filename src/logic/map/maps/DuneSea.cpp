#include "DuneSea.h"

DuneSea::DuneSea() : pathIdxCount(0) {
    mapType = MapType::DuneSea; 
    MAXPATHS = 2;
    // path 0
    enemyPath[0].push_back(Point(-50, 37, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(24, 25)); 
    enemyPath[0].push_back(Point(101, 16)); 
    enemyPath[0].push_back(Point(228, 71)); 
    enemyPath[0].push_back(Point(341, 77)); 
    enemyPath[0].push_back(Point(513, 150)); 
    enemyPath[0].push_back(Point(553, 185)); 
    enemyPath[0].push_back(Point(607, 254)); 
    enemyPath[0].push_back(Point(715, 265)); 
    enemyPath[0].push_back(Point(802, 288)); 
    enemyPath[0].push_back(Point(830, 300)); 
    enemyPath[0].push_back(Point(950, 330)); 
    enemyPath[0].push_back(Point(965, 340)); 
    enemyPath[0].push_back(Point(964, 350)); 
    enemyPath[0].push_back(Point(963, 372)); 
    enemyPath[0].push_back(Point(872, 385)); 
    enemyPath[0].push_back(Point(631, 458)); 
    enemyPath[0].push_back(Point(582, 485)); 
    enemyPath[0].push_back(Point(517, 500)); 
    enemyPath[0].push_back(Point(432, 497)); 
    enemyPath[0].push_back(Point(310, 531)); 
    enemyPath[0].push_back(Point(63, 505)); 
    enemyPath[0].push_back(Point(2, 492)); 
    enemyPath[0].push_back(Point(-100, 518, Point::Type::Exit)); // player gets damage here
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {70, 30}, 90.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
    
    // path 1
    enemyPath[1].push_back(Point(1050, 8, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[1].push_back(Point(972, 20)); 
    enemyPath[1].push_back(Point(835, 29)); 
    enemyPath[1].push_back(Point(797, 47)); 
    enemyPath[1].push_back(Point(664, 95)); 
    enemyPath[1].push_back(Point(605, 100)); 
    enemyPath[1].push_back(Point(478, 163)); 
    enemyPath[1].push_back(Point(352, 170)); 
    enemyPath[1].push_back(Point(209, 258)); 
    enemyPath[1].push_back(Point(73, 274)); 
    enemyPath[1].push_back(Point(14, 309)); 
    enemyPath[1].push_back(Point(18, 360)); 
    enemyPath[1].push_back(Point(76, 350)); 
    enemyPath[1].push_back(Point(152, 355)); 
    enemyPath[1].push_back(Point(238, 420)); 
    enemyPath[1].push_back(Point(338, 428)); 
    enemyPath[1].push_back(Point(582, 520)); 
    enemyPath[1].push_back(Point(675, 525)); 
    enemyPath[1].push_back(Point(824, 535)); 
    enemyPath[1].push_back(Point(980, 516)); 
    enemyPath[1].push_back(Point(1100, 571, Point::Type::Exit)); // player gets damage here
    
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {930, 40}, -90.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
}

std::unique_ptr<Map> DuneSea::clone() const {
    return std::make_unique<DuneSea>(*this);
}

Point::Type DuneSea::getPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    int tolerance = 10;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));

    // check Water 500 650
    Color waterColor = GetImageColor(mapImage, 500, 650);  
    bool isWater = Utils::isColorDiffByTolerance(waterColor, pixelColor, tolerance);
    if(isWater) return Point::Type::Water;

    // check for path
    Color pathColor = GetImageColor(mapImage, 40, 39); // 40 39 - an enemy path point
    bool isPath = Utils::isColorDiffByTolerance(pathColor, pixelColor, tolerance);
    if(isPath) return Point::Type::Enemy;

    return Point::Type::None; // can place tower here
}

void DuneSea::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("DuneSeaThumb");
    mapImage = LoadImage("../assets/map/Dune_sea_path_mask.png"); // MUST BE LOADED
}

std::pair<Vector2, int> DuneSea::getPositionAndPathIdx(BloonType type) {
    pathIdxCount = (pathIdxCount + 1) % MAXPATHS;
    return {getCurrentPoint(0, pathIdxCount), pathIdxCount}; // Default position and path index for this map
}
