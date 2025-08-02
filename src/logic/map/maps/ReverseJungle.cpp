#include "ReverseJungle.h"

ReverseJungle::ReverseJungle() {
    mapType = MapType::ReverseJungle; 

    //path 0
    enemyPath[0].push_back(Point(-50, 188, Point::Type::SpawnEnenmy));
    enemyPath[0].push_back(Point(504, 190));
    enemyPath[0].push_back(Point(532, 197));
    enemyPath[0].push_back(Point(558, 207));
    enemyPath[0].push_back(Point(592, 232));
    enemyPath[0].push_back(Point(615, 261));
    enemyPath[0].push_back(Point(626, 295));
    enemyPath[0].push_back(Point(626, 345));
    enemyPath[0].push_back(Point(621, 398));
    enemyPath[0].push_back(Point(621, 449));
    enemyPath[0].push_back(Point(681, 483));
    enemyPath[0].push_back(Point(710, 479));
    enemyPath[0].push_back(Point(733, 455));
    enemyPath[0].push_back(Point(738, 440));
    enemyPath[0].push_back(Point(747, 420));
    enemyPath[0].push_back(Point(757, 378));
    enemyPath[0].push_back(Point(761, 360));
    enemyPath[0].push_back(Point(760, 347));
    enemyPath[0].push_back(Point(754, 299));
    enemyPath[0].push_back(Point(751, 283));
    enemyPath[0].push_back(Point(741, 242));
    enemyPath[0].push_back(Point(726, 221));
    enemyPath[0].push_back(Point(714, 198));
    enemyPath[0].push_back(Point(694, 170));
    enemyPath[0].push_back(Point(672, 148));
    enemyPath[0].push_back(Point(626, 117));
    enemyPath[0].push_back(Point(600, 105));
    enemyPath[0].push_back(Point(590, 101));
    enemyPath[0].push_back(Point(581, 97));
    enemyPath[0].push_back(Point(564, 93));
    enemyPath[0].push_back(Point(513, 90));
    enemyPath[0].push_back(Point(470, 81));
    enemyPath[0].push_back(Point(0, 86));
    enemyPath[0].push_back(Point(-100, 86, Point::Type::Exit));

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

std::unique_ptr<Map> ReverseJungle::clone() const {
    return std::make_unique<ReverseJungle>(*this);
}

void ReverseJungle::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("JungleThumb");
    mapImage = LoadImage("../assets/map/Jungle_thumb_path_mask.png"); // MUST BE LOADED
    pathImage = LoadImage("../assets/map/Jungle_thumb.png"); // Path image for collision detection
}

void ReverseJungle::update() {
    // This map has no dynamic elements to update
}

std::pair<Vector2, int> ReverseJungle::getPositionAndPathIdx(BloonType type) {
    return {getCurrentPoint(0, 0), 0}; // Default position and path index for this map
}
