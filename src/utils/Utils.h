#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "Properties.h"

namespace Utils {
    bool isMouseInMap();
    bool isPositionInMap(Vector2 position);
};

#endif // UTILS_H