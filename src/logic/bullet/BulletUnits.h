#ifndef BULLETUNITS_H
#define BULLETUNITS_H

enum class BulletType {
    Dart,
    Bomb,
    Tack,
    Ice,
    MagicBall,
    Shuriken
};

class BulletProperties {
public:
    bool canLead = false;
    bool canBlack = false;
    bool canWhite = false;
    bool canFrozen = false;
    bool canCamo = false;
    bool canPurple = false;

    static BulletProperties normal() {
        return BulletProperties{false, true, true, false, false, true};
    }
    static BulletProperties bomb() {
        return BulletProperties{true, false, true, true, false, true};
    }
    static BulletProperties ice() {
        return BulletProperties{false, true, false, true, false, true};
    }
    static BulletProperties magic() {
        return BulletProperties{false, true, true, false, false, false};
    }

    BulletProperties() = default;
    BulletProperties(bool canLead, bool canBlack, bool canWhite, bool canFrozen, bool canCamo, bool canPurple)
        : canLead(canLead), canBlack(canBlack), canWhite(canWhite), canFrozen(canFrozen), canCamo(canCamo), canPurple(canPurple) {}
    ~BulletProperties() = default;
};

#endif // BULLETUNITS_H