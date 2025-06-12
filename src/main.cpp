#include "raylib.h"
#include <iostream>

#include "Properties.h"
#include "core/Game.h"
#include "logic/map/Map.h"

int main() {
    InitWindow(Properties::screenWidth, Properties::screenHeight, "BTD4");
    SetTargetFPS(60);         

    Game &game = Game::Instance();
    game.LoadContent();
    game.initialize();
    
    while (!WindowShouldClose())    
    {
        if(game.isExit()) break;
        float deltaTime = GetFrameTime();
        game.update(deltaTime);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            game.render();
        EndDrawing();
    }

    game.UnloadContent();
    CloseWindow();    

    return 0;
}