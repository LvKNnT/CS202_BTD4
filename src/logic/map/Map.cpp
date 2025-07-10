#include "Map.h"

Map::~Map() {
    
}

void Map::draw() const {
    DrawTextureEx(texture, {0, 0}, 0.0f, 1.0f, WHITE);
}

void Map::unLoad() {
    // Need to unload before closeWindow()
    UnloadImage(mapImage);
    UnloadTexture(texture);
}

Point::Type Map::getPointType(Vector2 position) const {
    for(int pathIdx = 0; pathIdx < MAXPATHS; pathIdx++) {
        for(int i = 0; i < enemyPath[pathIdx].size() - 1; i++) {
            if(enemyPath[pathIdx][i].canGetType(position, enemyPath[pathIdx][i + 1])) return enemyPath[pathIdx][i].getType();
        }

        Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));
        Color pathColor = GetImageColor(mapImage, static_cast<int>(enemyPath[pathIdx][1].position.x), static_cast<int>(enemyPath[pathIdx][1].position.y));
        int tolerance = 10;
        bool isPath = abs(pixelColor.r - pathColor.r) < tolerance && abs(pixelColor.g - pathColor.g) < tolerance && abs(pixelColor.b - pathColor.b) < tolerance;
        if(isPath) return Point::Type::Enemy;
    }

    return Point::Type::None; // can place tower here
}

Point::Type Map::getPointType(int index, int pathIdx) const {
    if(index < 0 || index >= (int) enemyPath[pathIdx].size()) return Point::Type::None;
    return enemyPath[pathIdx][index].getType();
}

Vector2 Map::getCurrentPoint(int index, int pathIdx) const {
    return enemyPath[pathIdx][index].position;
}

Vector2 Map::getNextPoint(int index, int pathIdx) const {
    if(index + 1 >= (int) enemyPath[pathIdx].size()) return enemyPath[pathIdx].back().position; 
    return enemyPath[pathIdx][index + 1].position;
}

MonkeyLane::MonkeyLane() {
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("assets/map/Monkey_lane_path_mask.png");
    enemyPath[0].push_back(Point(-50, 400, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(0, 390));
    enemyPath[0].push_back(Point(210, 390));
    enemyPath[0].push_back(Point(215, 290));
    enemyPath[0].push_back(Point(355, 285));
    enemyPath[0].push_back(Point(375, 655));
    enemyPath[0].push_back(Point(615, 660));
    enemyPath[0].push_back(Point(615, 600, Point::Type::Invisible));
    enemyPath[0].push_back(Point(615, 420));
    enemyPath[0].push_back(Point(590, 175));
    enemyPath[0].push_back(Point(215, 160));
    enemyPath[0].push_back(Point(215, 55));
    enemyPath[0].push_back(Point(725, 55));
    enemyPath[0].push_back(Point(745, 150));
    enemyPath[0].push_back(Point(890, 170));
    enemyPath[0].push_back(Point(890, 275));
    enemyPath[0].push_back(Point(750, 300));
    enemyPath[0].push_back(Point(740, 505));
    enemyPath[0].push_back(Point(480, 510, Point::Type::Invisible));
    enemyPath[0].push_back(Point(270, 510));
    enemyPath[0].push_back(Point(210, 760, Point::Type::Exit)); // player gets damage here
}

Jungle::Jungle() {
    texture = Game::Instance().getTextureManager().getTexture("JungleThumb");
    mapImage = LoadImage("assets/map/Monkey_lane_path_mask.png");

    //path 0
    enemyPath[0].push_back(Point(-50, 86, Point::Type::SpawnEnenmy));
    enemyPath[0].push_back(Point(0, 86));
    enemyPath[0].push_back(Point(470, 81));
    enemyPath[0].push_back(Point(564, 93));
    enemyPath[0].push_back(Point(626, 117));
    enemyPath[0].push_back(Point(672, 148));
    enemyPath[0].push_back(Point(694, 170));
    enemyPath[0].push_back(Point(714, 198));
    enemyPath[0].push_back(Point(715, 210));
    enemyPath[0].push_back(Point(726, 221));
    enemyPath[0].push_back(Point(741, 242));
    enemyPath[0].push_back(Point(751, 283));
    enemyPath[0].push_back(Point(754, 299));
    enemyPath[0].push_back(Point(760, 347));
    enemyPath[0].push_back(Point(761, 360));
    enemyPath[0].push_back(Point(757, 378));
    enemyPath[0].push_back(Point(747, 420));
    enemyPath[0].push_back(Point(738, 440));
    enemyPath[0].push_back(Point(733, 455));
    enemyPath[0].push_back(Point(710, 479));
    enemyPath[0].push_back(Point(681, 483));
    enemyPath[0].push_back(Point(621, 449));
    enemyPath[0].push_back(Point(618, 398));
    enemyPath[0].push_back(Point(626, 345));
    enemyPath[0].push_back(Point(626, 295));
    enemyPath[0].push_back(Point(615, 261));
    enemyPath[0].push_back(Point(592, 232));
    enemyPath[0].push_back(Point(558, 207));
    enemyPath[0].push_back(Point(532, 197));
    enemyPath[0].push_back(Point(504, 190));
    enemyPath[0].push_back(Point(20, 190));
    enemyPath[0].push_back(Point(-50, 188, Point::Type::Exit));


    //path 1
    enemyPath[1].push_back(Point(1050, 651, Point::Type::SpawnEnenmy));
    enemyPath[1].push_back(Point(480, 653));
    enemyPath[1].push_back(Point(369, 612));
    enemyPath[1].push_back(Point(331, 587));
    enemyPath[1].push_back(Point(301, 558));
    enemyPath[1].push_back(Point(275, 521));
    enemyPath[1].push_back(Point(252, 463));
    enemyPath[1].push_back(Point(240, 431));
    enemyPath[1].push_back(Point(240, 380));
    enemyPath[1].push_back(Point(244, 340));
    enemyPath[1].push_back(Point(254, 301));
    enemyPath[1].push_back(Point(272, 270));
    enemyPath[1].push_back(Point(293, 257));
    enemyPath[1].push_back(Point(308, 253));
    enemyPath[1].push_back(Point(338, 253));
    enemyPath[1].push_back(Point(362, 267));
    enemyPath[1].push_back(Point(383, 296));
    enemyPath[1].push_back(Point(373, 363));
    enemyPath[1].push_back(Point(370, 409));
    enemyPath[1].push_back(Point(375, 443));
    enemyPath[1].push_back(Point(392, 478));
    enemyPath[1].push_back(Point(422, 518));
    enemyPath[1].push_back(Point(466, 533));
    enemyPath[1].push_back(Point(481, 537));
    enemyPath[1].push_back(Point(980, 549));
    enemyPath[1].push_back(Point(1050, 545, Point::Type::Exit));
}

bool Map::isLastPoint(int index, int pathIdx) const {
    return index + 1 >= (int) enemyPath[pathIdx].size();
}

bool Map::isWithinBounds(Vector2 position) const {
    return position.x >= 0 && position.x < static_cast<float>(mapImage.width) &&
           position.y >= 0 && position.y < static_cast<float>(mapImage.height);
}

