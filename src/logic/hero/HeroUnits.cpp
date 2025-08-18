#include "HeroUnits.h"

HeroInfo::HeroInfo() {
    info[HeroType::Quincy]["name"] = "Quincy";
    info[HeroType::Quincy]["description"] = "Your towers will shoot faster (+10% attack speed).";

    info[HeroType::Benjamin]["name"] = "Benjamin";
    info[HeroType::Benjamin]["description"] = "Your towers cost less (-10% base cost/upgrade cost).";

    info[HeroType::Rosalia]["name"] = "Rosalia";
    info[HeroType::Rosalia]["description"] = "Your towers deal more damager (+1 damage).";

    info[HeroType::Etienne]["name"] = "Etienne";
    info[HeroType::Etienne]["description"] = "Your towers have bigger range (+10% range).";
}

HeroInfo& HeroInfo::Instance() {
    static HeroInfo instance;
    return instance;
}

LogicInfo HeroInfo::getHeroInfo(HeroType heroType) {
    return info[heroType];
}