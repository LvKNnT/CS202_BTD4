#ifndef ENEMYUNITS_H
#define ENEMYUNITS_H

#include "raylib.h"
#include <string>

// Bloons types
enum class BloonType {
    Red,
    Blue,
    Green,
    Yellow,
    Pink,
    Black,
    White,
    Purple,
    Lead,
    Zebra,
    Rainbow,
    Ceramic,
    Moab, // Massive Object Air Blimp
    Bfb,  // Big Floating Blimp
    Zomg, // Zeppelins of Mighty Gargantuaness
    Ddt,   // Dark Dirigible Titan
    Bad // Big Airship of Doom
};

class BloonProperties {
public:
    bool isFortified;
    bool isCamo;
    bool isRegrow;

    // other properties
    bool isGlue = false;
    bool isStun = false;
    bool isFrozen = false;
    bool isKnockback = false;

    BloonProperties(bool fortified = false, bool camo = false, bool regrow = false)
        : isFortified(fortified), isCamo(camo), isRegrow(regrow) {}
    BloonProperties(const BloonProperties& other)
        : isFortified(other.isFortified), isCamo(other.isCamo), isRegrow(other.isRegrow) {}
    ~BloonProperties() = default;

    BloonProperties& operator=(const BloonProperties& other) {
        if (this != &other) {
            isFortified = other.isFortified;
            isCamo = other.isCamo;
            isRegrow = other.isRegrow;
        }
        return *this;
    }

    std::string getFullTag(std::string tag) const {
        std::string fullTag = "BTD6";
        if(isFortified) fullTag += "Fortified";
        if(isCamo) fullTag += "Camo";
        if(isRegrow) fullTag += "Regrow";
        fullTag += tag;

        return fullTag;
    }
    std::string getPath() const {
        if(!isFortified && !isCamo && !isRegrow) {
            return "../assets/enemy/Normal Bloons/default/";
        }

        std::string path = "../assets/enemy/Normal Bloons/";
        if(isFortified) path += "fortified";
        if(isCamo) path += "camo";
        if(isRegrow) path += "regrow";
        path += "/";

        return path;
    }
};

class BloonDebuff {
public:
    // for normal bloons
    float slowRatio = 0.0f;
    float slowDuration = 0.0f;
    float stunDuration = 0.0f; 
    float freezeDuration = 0.0f;
    float knockbackDuration = 0.0f;
    float knockbackSpeed = 1.0f;

    // for damage
    int bonusDamage = 0; // Bonus damage for the bloon
    int bonusFortifiedDamage = 0; // Bonus damage for fortified bloon
    int bonusLeadDamage = 0; // Bonus damage for lead bloon
    int bonusCamoDamage = 0; // Bonus damage for camo bloon

    BloonDebuff(float slowRatio = 0.0f, float slowDuration = 0.0f, float stunDuration = 0.0f, float freezeDuration = 0.0f, float knockbackDuration = 0.0f, float knockbackSpeed = 1.0f, int bonusDamage = 0, int bonusFortifiedDamage = 0, int bonusLeadDamage = 0, int bonusCamoDamage = 0)
        : slowRatio(slowRatio), slowDuration(slowDuration), stunDuration(stunDuration), freezeDuration(freezeDuration), knockbackDuration(knockbackDuration), knockbackSpeed(knockbackSpeed), bonusDamage(bonusDamage), bonusFortifiedDamage(bonusFortifiedDamage), bonusLeadDamage(bonusLeadDamage), bonusCamoDamage(bonusCamoDamage) {}
    BloonDebuff(const BloonDebuff& other)
        : slowRatio(other.slowRatio), slowDuration(other.slowDuration), stunDuration(other.stunDuration), freezeDuration(other.freezeDuration), knockbackDuration(other.knockbackDuration), knockbackSpeed(other.knockbackSpeed), bonusDamage(other.bonusDamage), bonusFortifiedDamage(other.bonusFortifiedDamage), bonusLeadDamage(other.bonusFortifiedDamage), bonusCamoDamage(bonusCamoDamage) {}
    ~BloonDebuff() = default;

    BloonDebuff& operator=(const BloonDebuff& other) {
        if (this != &other) {
            slowRatio = other.slowRatio;
            slowDuration = other.slowDuration;
            stunDuration = other.stunDuration;
            freezeDuration = other.freezeDuration;
            knockbackDuration = other.knockbackDuration;
            knockbackSpeed = other.knockbackSpeed;
            bonusDamage = other.bonusDamage;
        }
        return *this;
    }

    BloonDebuff operator+(const BloonDebuff& other) const {
        return BloonDebuff(
            (slowRatio < other.slowRatio) ? other.slowRatio : slowRatio,
            (slowDuration < other.slowDuration) ? other.slowDuration : slowDuration,
            (stunDuration < other.stunDuration) ? other.stunDuration : stunDuration,
            (freezeDuration < other.freezeDuration) ? other.freezeDuration : freezeDuration,
            (knockbackDuration < other.knockbackDuration) ? other.knockbackDuration : knockbackDuration,
            (knockbackSpeed < other.knockbackSpeed) ? other.knockbackSpeed : knockbackSpeed,
            bonusDamage + other.bonusDamage,
            bonusFortifiedDamage + other.bonusFortifiedDamage,
            bonusLeadDamage + other.bonusLeadDamage,
            bonusCamoDamage + other.bonusCamoDamage
        );
    }

    BloonDebuff& operator+=(const BloonDebuff& other) {
        slowRatio = (slowRatio < other.slowRatio) ? other.slowRatio : slowRatio;
        slowDuration = (slowDuration < other.slowDuration) ? other.slowDuration : slowDuration;
        stunDuration = (stunDuration < other.stunDuration) ? other.stunDuration : stunDuration;
        freezeDuration = (freezeDuration < other.freezeDuration) ? other.freezeDuration : freezeDuration;
        knockbackDuration = (knockbackDuration < other.knockbackDuration) ? other.knockbackDuration : knockbackDuration;
        knockbackSpeed = (knockbackSpeed < other.knockbackSpeed) ? other.knockbackSpeed : knockbackSpeed;
        bonusDamage += other.bonusDamage;
        bonusFortifiedDamage += other.bonusFortifiedDamage;
        bonusLeadDamage += other.bonusLeadDamage;
        bonusCamoDamage += other.bonusCamoDamage;
        return *this;
    }

    BloonDebuff getISlow(float ratio, float duration) const {
        return *this + BloonDebuff{
            ratio,
            duration,
            0.0f, // stunDuration
            0.0f, // freezeDuration
            0.0f,  // knockbackDuration
            1.0f, // knockbackSpeed
            0, // bonusDamage
            0, // bonusFortifiedDamage
            0, // bonusLeadDamage
            0 // bonusCamoDamage
        };  
    }

    BloonDebuff getIStun(float duration) const {
        return *this + BloonDebuff{
            0.0f, // slowRatio
            0.0f, // slowDuration
            duration, // stunDuration
            0.0f, // freezeDuration
            0.0f, // knockbackDuration
            1.0f, // knockbackSpeed
            0, // bonusDamage
            0, // bonusFortifiedDamage
            0, // bonusLeadDamage
            0 // bonusCamoDamage
        };
    }

    BloonDebuff getIKnockBack(float duration, float speed) const {
        return *this + BloonDebuff{
            0.0f, // slowRatio
            0.0f, // slowDuration
            0.0f, // stunDuration
            0.0f, // freezeDuration
            duration, // knockbackDuration
            speed, // knockbackSpeed
            0, // bonusDamage
            0, // bonusFortifiedDamage
            0, // bonusLeadDamage
            0 // bonusCamoDamage
        };
    }

    BloonDebuff getIBonusDamage(int bonusDamage, int bonusFortifiedDamage, int bonusLeadDamage, int bonusCamoDamage) const {
        return *this + BloonDebuff{
            0.0f, // slowRatio
            0.0f, // slowDuration
            0.0f, // stunDuration
            0.0f, // freezeDuration
            0.0f, // knockbackDuration
            1.0f, // knockbackSpeed
            bonusDamage, // bonusDamage
            bonusFortifiedDamage, // bonusFortifiedDamage
            bonusLeadDamage, // bonusLeadDamage
            bonusCamoDamage // bonusCamoDamage
        };
    }

    void applyStun(float duration) {
        stunDuration = std::max(stunDuration, duration);
    }

    void update() {
        float deltaTime = GetFrameTime();

        slowDuration -= deltaTime;
        if (slowDuration <= 0.0f) {
            slowDuration = 0.0f;
            slowRatio = 0.0f; // Reset slow ratio when duration ends
        }
        stunDuration -= deltaTime;
        if (stunDuration < 0.0f) stunDuration = 0.0f;
        freezeDuration -= deltaTime;
        if (freezeDuration < 0.0f) freezeDuration = 0.0f;
        knockbackDuration -= deltaTime;
        if (knockbackDuration < 0.0f) knockbackDuration = 0.0f;
    }

    int calSpeed(int speed) const {
        if(freezeDuration > 0.0f
        || stunDuration > 0.0f) return 0;
        return static_cast<int>(speed * (1.0f - slowRatio));
    }

    int calKnockbackSpeed(int speed) const {
        if(knockbackDuration <= 0.0f) return 0;
        return - speed * knockbackSpeed; // negative speed for knockback
    }
};

#endif // ENEMYUNITS_H