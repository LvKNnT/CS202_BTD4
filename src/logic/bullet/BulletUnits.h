#ifndef BULLETUNITS_H
#define BULLETUNITS_H

// #include <../enemy/Enemy.h>
#include <memory>
#include "../tower/TowerUnits.h"
#include "raylib.h"

class Enemy;

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
    BombFragment,
    TracingShuriken,
    Caltrops,
    FlashBomb,
    FlashBombExplosion, 
    StickyBomb,
    MasterBomber,
    Shrapnel,
    ShrapnelShot
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

    // for tracing bullets
    bool canTrace = false;
    bool isOnlyFollowing = false;
    std::weak_ptr<Enemy> targetEnemy; 
    float range = 0.0f;
    bool isFocus = false;
    TargetPriority targetPriority = TargetPriority::First;

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
        return BulletProperties{false, true, false, false, false, false, true};
    }
    static BulletProperties magic() {
        return BulletProperties{false, true, true, false, false, false, false};
    }
    static BulletProperties shuriken() {
        return BulletProperties{false, true, true, false, true, true, false};
    }

    BulletProperties() = default;
    BulletProperties(bool canLead, bool canBlack, bool canWhite, bool canFrozen, bool canCamo, bool canPurple, bool canStripCamo = false)
        : canLead(canLead), canBlack(canBlack), canWhite(canWhite), canFrozen(canFrozen), canCamo(canCamo), canPurple(canPurple), canStripCamo(canStripCamo) {}
    ~BulletProperties() = default;

    BulletProperties& operator+= (const BulletProperties& other);

    BulletProperties operator+ (const BulletProperties& other);

    BulletProperties& operator= (const BulletProperties& other);

    BulletProperties& getITracing(float range, TargetPriority targetPriority, bool isFocus = false, bool isFollowing = false);
    BulletProperties& removeITracing();
    BulletProperties& getITracing(std::shared_ptr<Enemy> enemy);
    float getRotation(float rotation, Vector2 position);
};

#endif // BULLETUNITS_H