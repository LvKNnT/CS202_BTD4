#ifndef ENEMYUNITS_H
#define ENEMYUNITS_H

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

#endif // ENEMYUNITS_H