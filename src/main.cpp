#include <cstdlib>
#include "raylib.h"
#include "config.h"
#include "weapons.h"
#include "string.h"

using namespace std;

const int screenWidth = 1920;
const int screenHeight = 1080;

void WeaponSwing(float& cooldown, bool& isInventory, struct& sword, int& attackDuration, bool& swordAttack, Vector2& playerPostion, Vector2& playerSize, Vector2& swordPosition, Vector2& swordSize);

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
    bool isInventory = false, crash = true;

    // Main game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

		if (isInventory) dt = 0.0f;
        
		//player movement
        if (IsKeyDown(KEY_D)) playerPostion.x += playerSpeed * dt;
        if (IsKeyDown(KEY_A)) playerPostion.x -= playerSpeed * dt;
        if (IsKeyDown(KEY_W)) playerPostion.y -= playerSpeed * dt;
        if (IsKeyDown(KEY_S)) playerPostion.y += playerSpeed * dt;

        //player inventory
        if (IsKeyPressed(KEY_TAB))
        {
            if (isInventory == false) isInventory = true;
            else if (isInventory == true) isInventory = false;
        }

        BeginDrawing();
        ClearBackground(WHITE);

		//player attack
        WeaponSwing(cooldown, isInventory, sword, attackDuration, swordAttack, playerPostion, playerSize, swordPosition, swordSize);

        Vector2 swordPosition = { playerPostion.x + playerSize.x, playerPostion.y + (playerSize.y / 2) };

        if (isInventory) {
            #define INVENTORY       CLITERAL(Color){ 130, 130, 130, 200 } //custom color for inventory panel
            #define BACKGROUND      CLITERAL(Color){ 40, 40, 40, 200 }    //custom color for creating background fading
            DrawRectangle(0, 0, screenWidth, screenHeight, BACKGROUND);
            for (int i = 0; i < screenWidth - 400; i++) {
                DrawRectangle(200, 200, i, screenHeight - 400, INVENTORY);
            }
            DrawRectangle(240, 240, 400, 600, BLACK);
        }

        EndDrawing();
    }


    CloseWindow();

    return EXIT_SUCCESS;
}

void WeaponSwing(float& cooldown, bool& isInventory, struct& sword, int& attackDuration, bool& swordAttack, Vector2& playerPostion, Vector2& playerSize, Vector2& swordPosition, Vector2& swordSize)
{
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cooldown <= 0.0f && !isInventory) {
            swordAttack = true;
            attackDuration = 15;
        }
        if (attackDuration > 0) {
            attackDuration--;
        }
        else if (!isInventory) {
            swordAttack = false;
        }
        if (cooldown > 0.0f) {
            cooldown--;
        }

        DrawRectangleV(playerPostion, playerSize, RED);
        if (swordAttack) {
            DrawRectangleV(swordPosition, swordSize, BLUE);
            cooldown = 30.0f;
        }

    };
}