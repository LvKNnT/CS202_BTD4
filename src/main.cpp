#include "raylib.h"
#include <iostream>

#include "utils/Properties.h"
#include "utils/Timer.h"

#include "core/Game.h"

// testing..
#include "logic/map/Map.h"
#include "logic/GameLogic.h"
#include "logic/GameObjectManager.h"
#include "logic/enemy/Red.h"

int main() {
    InitWindow(Properties::screenWidth, Properties::screenHeight, "BTD4");
    SetTargetFPS(60);         

    Game game;
    game.initialize();
    game.LoadContent();
    
    // just for easy coding, will be removed later when GameLogic is finished
    Map map(Map::Type::MonkeyLane);
    
    // same here lmao
    Timer timer;
    LogicManager logicManager;
    logicManager.Init();
    

    timer.reset();
    while (!WindowShouldClose())  
    {
        logicManager.Update();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.render();
        
        map.draw();
        logicManager.Draw();
        EndDrawing();
    }

    game.UnloadContent();
    CloseWindow();    

    return 0;
}