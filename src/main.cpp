#include "raylib.h"
#include <iostream>

#include "managers/TextureManager.h"
#include "map/Map.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Load map
    Map map(Map::MonkeyLane);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // set background texture i want to scale texture to fit the screen
            // Draw a texture to the screen
            Texture2D backgroundTexture = map.getTexture();
            DrawTextureEx(backgroundTexture, {0, 0}, 0.0f, (float)screenWidth / backgroundTexture.width, WHITE);

            // get mouse position
            Vector2 mousePosition = GetMousePosition();
            std::cerr<<mousePosition.x<<" "<<mousePosition.y<<" ";
            auto type = map.getPointType(mousePosition);
            std::cerr<<type<<"\n";

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}