#ifndef TOWERUNITS_H
#define TOWERUNITS_H

enum class TowerUnits {
    None = 0,
    Tower1 = 1,
    Tower2 = 2,
    Tower3 = 3,
    Tower4 = 4,
    Tower5 = 5,
    Tower6 = 6,
    Tower7 = 7,
    Tower8 = 8,
    Tower9 = 9,
    Tower10 = 10
};

enum class TowerType {
    None = 0,
    DartMonkey = 1,
    TackShooter = 2,
    SniperMonkey = 3,
    BoomerangMonkey = 4,
    NinjaMonkey = 5,
    WizardMonkey = 6,
    SuperMonkey = 7,
    MonkeyAce = 8,
    HeliPilot = 9,
    MortarMonkey = 10
};

enum class TargetPriority {
    First = 0,
    Last = 1,
    Close = 2,
    Strong = 3,
};

#endif // TOWERUNITS_H