#include <cstdlib>
#include "raylib.h"
#include "config.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);


    //Player Variables
    Vector2 playerPostion = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 playerSize = { 50, 50 };
    float playerSpeed = 200.0f;

    //Sword Variables
    Vector2 swordSize = { 40, 10 };
    bool swordAttack = false;
    int attackDuration = 0;
    float cooldown = 0.0f;

    // Main game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_D)) playerPostion.x += playerSpeed * dt;
        if (IsKeyDown(KEY_A)) playerPostion.x -= playerSpeed * dt;
        if (IsKeyDown(KEY_W)) playerPostion.y -= playerSpeed * dt;
        if (IsKeyDown(KEY_S)) playerPostion.y += playerSpeed * dt;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cooldown <= 0.0f) {
            swordAttack = true;
            attackDuration = 15;
        }
        if (attackDuration > 0) {
            attackDuration--;
        }
        else {
            swordAttack = false;
        }
        if (cooldown > 0.0f) {
            cooldown--;
        }

        Vector2 swordPosition = { playerPostion.x + playerSize.x, playerPostion.y + (playerSize.y / 2) };

        BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangleV(playerPostion, playerSize, RED);
        if (swordAttack) {
            DrawRectangleV(swordPosition, swordSize, BLUE);
            cooldown = 30.0f;
        }

        EndDrawing();
    }


    CloseWindow();

    return EXIT_SUCCESS;
}