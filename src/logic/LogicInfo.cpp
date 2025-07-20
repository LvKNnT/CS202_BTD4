#include "LogicInfo.h"

std::string& LogicInfo::operator[](std::string key) {
    return infos[key];
}

bool LogicInfo::operator=(const LogicInfo& other) {
    if (this != &other) {
        infos = other.infos; // Copy the map of infos
    }

    return !infos.empty(); // Return true if the map is not empty
}