#include "RoundInfo.h"

RoundInfo::RoundInfo() {
    // Initialize round information
    // when there is no info, the round detail will be info of the difficulty
    // the first round should not have tip and trip :>
    info[2]["detail"] = "Round 1 is so easy huh, did someone even lose a life? I should make it harder.\n";
    info[3]["detail"] = "You can see a tower stats by clicking on that tower.\n";
    info[4]["detail"] = "You can press ESC key to cancel placing or back to game info.\n";
    info[5]["detail"] = "Spike and Pineapple bullet are useful, you can place them on enemy path for small attack, but they will be cleared at the end of the round.\n";
    info[7]["detail"] = "You can see infomation of towers or their upgrades by hovering info buttons.\n";
    info[8]["detail"] = "Infomation of upgrades is very important for strategy, so read it carefully.\n";
    info[9]["detail"] = "Boring to click play round button every round, huh? You can automate it in the settings.\n";
    info[10]["detail"] = "Tower's target prioriy can be changed in order (First - Last - Close - Strong).\n";
    info[11]["detail"] = "The current map is saved after every round, you can quit anytime and continue later\n";
    info[12]["detail"] = "Jiggle is a fun mechanic that adds randomness to the game. You can set it in the settings!\n";

    info[20]["detail"] = "You can see a tower stats by clicking on that tower.\n";
    info[21]["detail"] = "You can press ESC key to cancel placing or back to game info.\n";
    info[22]["detail"] = "Spike and Pineapple bullet are useful, you can place them on enemy path for small attack, but they will be cleared at the end of the round.\n";
    info[23]["detail"] = "You can see infomation of towers or their upgrades by hovering info buttons.\n";
    info[24]["detail"] = "Infomation of upgrades is very important for strategy, so read it carefully.\n";
    info[25]["detail"] = "Boring to click play round button every round, huh? You can automate it in the settings.\n";
    info[26]["detail"] = "Tower's target prioriy can be changed in order (First - Last - Close - Strong).\n";
    info[27]["detail"] = "The current map is saved after every round, you can quit anytime and continue later\n";
    info[28]["detail"] = "Jiggle is a fun mechanic that adds randomness to the game. You can set it in the settings!\n";

    info[40]["detail"] = "You can see a tower stats by clicking on that tower.\n";
    info[41]["detail"] = "You can press ESC key to cancel placing or back to game info.\n";
    info[42]["detail"] = "Spike and Pineapple bullet are useful, you can place them on enemy path for small attack, but they will be cleared at the end of the round.\n";
    info[43]["detail"] = "You can see infomation of towers or their upgrades by hovering info buttons.\n";
    info[44]["detail"] = "Infomation of upgrades is very important for strategy, so read it carefully.\n";
    info[45]["detail"] = "Boring to click play round button every round, huh? You can automate it in the settings.\n";
    info[46]["detail"] = "Tower's target prioriy can be changed in order (First - Last - Close - Strong).\n";
    info[47]["detail"] = "The current map is saved after every round, you can quit anytime and continue later\n";
    info[48]["detail"] = "Jiggle is a fun mechanic that adds randomness to the game. You can set it in the settings!\n";
}

RoundInfo& RoundInfo::Instance() {
    static RoundInfo instance;
    return instance;
}

LogicInfo RoundInfo::getRoundInfo(int roundNum) {
    return info[roundNum];
}