#include <raylib.h>
#include "config.h"


int main() {
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);


    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Hello World", 20, 20, 20, RED);
        DrawTexture(myTexture, 10, 100, WHITE);

        EndDrawing();
    }

    UnloadTexture(myTexture);

    CloseWindow();

    return 1;
}
