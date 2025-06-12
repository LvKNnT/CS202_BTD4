#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "raylib.h"
#include "LogicManager.h"

class GameLogic {
public:
    GameLogic() = default;
    ~GameLogic() = default;
    
    void Init();
    void Update();

private:
    LogicManager logicManager; // Manages the game logic, including enemies and other game elements
};

#endif // GAME_LOGIC_H