#include "raylib.h"
#include <iostream>

#include "utils/Properties.h"
#include "utils/Timer.h"

#include "core/Game.h"

// testing..
#include "logic/map/Map.h"
#include "logic/GameLogic.h"
#include "logic/GameObjectManager.h"
#include "logic/enemy/Enemy.h"

int main() {
    InitWindow(Properties::screenWidth, Properties::screenHeight, "BTD4");
    SetTargetFPS(60);         
    SetExitKey(0);
    
    InitAudioDevice();  
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