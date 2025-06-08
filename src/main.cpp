#include "raylib.h"
#include <iostream>

#include "Properties.h"
#include "core/Game.h"
#include "logic/map/Map.h"

int main() {
    InitWindow(Properties::screenWidth, Properties::screenHeight, "BTD4");
    SetTargetFPS(60);         

    Game game;
    game.initialize();
    game.LoadContent();
    
    // just for easy coding, will be removed later when GameLogic is finished
    Map map(Map::Type::MonkeyLane);
    while (!WindowShouldClose())    
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            game.render();

            map.draw();
        EndDrawing();
    }

    game.UnloadContent();
    CloseWindow();    

    return 0;
}