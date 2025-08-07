#ifndef BULLETUNITS_H
#define BULLETUNITS_H

enum class BulletType {
    Dart,
    TracingDart,
    SpikeOPult,
    Juggernaut,
    UltraJuggernaut,
    Arrow,
    ArrowCrit,
    Bomb,
    ReallyBigBombs,
    MOABAssassin,
    FragBombs,
    ClusterBomb,
    RecursiveClusterBomb,
    Tack,
    Ice,
    MagicBall,
    Shuriken,
    BombExplosion,
    BombFragment
    BombExplosion, 
    TracingShuriken,
    Caltrops
};

class BulletProperties {
public:
    bool canLead = false;
    bool canBlack = false;
    bool canWhite = false;
    bool canFrozen = false;
    bool canCamo = false;
    bool canPurple = false;
    bool canStripCamo = false;

    // hit specific bloon types
    bool canNormal = true;
    bool canMoab = true;

    static BulletProperties classic() {
        return BulletProperties{false, false, false, false, false, false, false};
    }
    static BulletProperties normal() {
        return BulletProperties{false, true, true, false, false, true, false};
    }
    static BulletProperties bomb() {
        return BulletProperties{true, false, true, true, false, true, false};
    }
    static BulletProperties ice() {
        return BulletProperties{false, true, false, true, false, true, false};
    }
    static BulletProperties magic() {
        return BulletProperties{false, true, true, false, false, false, false};
    }
    

    BulletProperties() = default;
    BulletProperties(bool canLead, bool canBlack, bool canWhite, bool canFrozen, bool canCamo, bool canPurple, bool canStripCamo = false)
        : canLead(canLead), canBlack(canBlack), canWhite(canWhite), canFrozen(canFrozen), canCamo(canCamo), canPurple(canPurple), canStripCamo(canStripCamo){}
    ~BulletProperties() = default;

    BulletProperties& operator+= (const BulletProperties& other) {
        canLead = canLead || other.canLead;
        canBlack = canBlack || other.canBlack;
        canWhite = canWhite || other.canWhite;
        canFrozen = canFrozen || other.canFrozen;
        canCamo = canCamo || other.canCamo;
        canPurple = canPurple || other.canPurple;
        canStripCamo = canStripCamo || other.canStripCamo;
        return *this;
    }

    BulletProperties operator+ (const BulletProperties& other) const {
        BulletProperties result = *this;
        result += other;
        return result;
    }

    BulletProperties& operator= (const BulletProperties& other) {
        if (this != &other) {
            canLead = other.canLead;
            canBlack = other.canBlack;
            canWhite = other.canWhite;
            canFrozen = other.canFrozen;
            canCamo = other.canCamo;
            canPurple = other.canPurple;
            canStripCamo = other.canStripCamo;
        }
        return *this;
    }
};

#endif // BULLETUNITS_H