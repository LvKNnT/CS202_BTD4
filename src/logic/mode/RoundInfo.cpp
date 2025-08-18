#include "RoundInfo.h"

RoundInfo::RoundInfo() {
    // Initialize round information
    // when there is no info, the round detail will be info of the difficulty
    // the first round should not have tip and trip :>
    info[2]["detail"] = "Round 1 is so easy huh, did someone even lose a life? I should make it harder.\n";
    info[3]["detail"] = "You can see a tower stats by clicking on that tower.\n";
    info[4]["detail"] = "You can press ESC key to cancel placing towers or back to game info.\n";
    info[5]["detail"] = "You can press ESC key to cancel placing towers or back to game info.\n";
    info[6]["detail"] = "You can see infomation of towers or their upgrades by hovering info buttons.\n";
    info[7]["detail"] = "Infomation of upgrades is very important for strategy, so read it carefully.\n";
    info[8]["detail"] = "Boring to click play round button every round, huh? You can automate it in the settings.\n";
    info[9]["detail"] = "Tower's target prioriy can be changed in order (First - Last - Close - Strong).\n";
    info[10]["detail"] = "Jiggle is a fun mechanic that adds randomness to the game. You can set it in the settings!\n";
}

RoundInfo& RoundInfo::Instance() {
    static RoundInfo instance;
    return instance;
}

LogicInfo RoundInfo::getRoundInfo(int roundNum) {
    return info[roundNum];
}