#include "MapUnits.h"

MapInfo::MapInfo() {
    info[MapType::MonkeyLane]["name"] = "Monkey Lane";
    info[MapType::MonkeyLane]["description"] = "A peaceful and grassy environment. The terrain is grassy, a quiet lands, filled with many flowers, trees and rocks. Non-zeppelin bloons will go through the tunnels, and towers cannot target them. MOAB-class bloons will go over the tunnel instead of through and can be hit when over the tunnels. There is a windmill at the top-left moving clockwise.";

    info[MapType::Jungle]["name"] = "Jungle";
    info[MapType::Jungle]["description"] = "As inferred from its name, it is located in a jungle, with some trees, grasses, leafy plants and small vines surrounded and covered in this track. There are two, separate paths, so you should think of your towers properly that are effective especially in hard rounds. The entrances are on the top and bottom paths, respectively. Each path the bloons will do only one U-turn. There is no water.";

    info[MapType::RinkRevenge]["name"] = "Rink Revenge";
    info[MapType::RinkRevenge]["description"] = "It seems that The Rink wants a taste of vengeance by looking different (as stated in its name). Like its easier counterpart, it pretty much looks the same with the exception of the path being different, and having a second pond on the bottom left corner. There are five trees that towers cannot be placed on.";

    info[MapType::DuneSea]["name"] = "Dune Sea";
    info[MapType::DuneSea]["description"] = "A sandy track. There are 2 hidden paths that intersects at the beginning and the end of the track. They do sometimes a curve effect. You can build water towers on a juxtaposed sea. But of course, start popping the bloons! There is also a pink starfish near the bottom left corner of the sea.";

    info[MapType::AttackOnBloon]["name"] = "Attack On Bloon";
    info[MapType::AttackOnBloon]["description"] = "This map is inspired from Attack on Titan, the path of the Bloons is hidden in this one, but they will fly from the sky. Towers can not be placed on the tall edges or on certain obstacles scattered along its width, but they can be placed on the flat surfaces. These obstacles act as natural barriers, forcing the player to carefully navigate tower placement and plan their defenses.";
}

MapInfo& MapInfo::Instance() {
    static MapInfo instance;
    return instance;
}

LogicInfo MapInfo::getMapInfo(MapType mapType) {
    return info[mapType];
}