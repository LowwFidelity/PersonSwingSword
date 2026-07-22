#include <cstdlib>
#include <string>
#include "raylib.h"
#include "config.h"

using namespace std;

const int screenWidth = 1920;
const int screenHeight = 1080;

struct weapon {
    string name;
    float damage;
    float speed;
    float defense;
    float weight;
};

void PlayerMovement(Vector2& playerPostion, float& playerSpeed, float& dt);
void WeaponSwing(Texture2D& swordTexture, Vector2& swordPosition, float& cooldown, bool& isInventory, int& attackDuration, bool& swordAttack, Vector2& playerPostion, Vector2& playerSize, Vector2& swordSize);

int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    //Textures
    Image img = LoadImage("assets/graphics/Arrow.png");
    ImageResizeNN(&img, 32, 32);
    Texture2D swordTexture = LoadTextureFromImage(img);

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
	Vector2 swordPosition = { playerPostion.x + playerSize.x / 2, playerPostion.y + playerSize.y / 2 };
	weapon type = { "Crap Sword", 10.0f, 1.0f, 0.0f, 5.0f };

    // Main game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

		if (isInventory) dt = 0.0f;

        //player movement
        PlayerMovement(playerPostion, playerSpeed, dt);
        
        //player inventory
        if (IsKeyPressed(KEY_TAB))
        {
            if (isInventory == false) isInventory = true;
            else if (isInventory == true) isInventory = false;
        }

        BeginDrawing();
        ClearBackground(WHITE);

		//player attack
		DrawRectangleV(playerPostion, playerSize, RED);
        WeaponSwing(swordTexture, swordPosition, cooldown, isInventory, attackDuration, swordAttack, playerPostion, playerSize, swordSize);

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

void PlayerMovement (Vector2& playerPostion, float& playerSpeed, float& dt)
{
    //player movement
    if (IsKeyDown(KEY_D)) playerPostion.x += playerSpeed * dt;
    if (IsKeyDown(KEY_A)) playerPostion.x -= playerSpeed * dt;
    if (IsKeyDown(KEY_W)) playerPostion.y -= playerSpeed * dt;
    if (IsKeyDown(KEY_S)) playerPostion.y += playerSpeed * dt;
}

void WeaponSwing(Texture2D& swordTexture, Vector2& swordPosition, float& cooldown, bool& isInventory, int& attackDuration, bool& swordAttack, Vector2& playerPostion, Vector2& playerSize, Vector2& swordSize)
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
            UnloadTexture(swordTexture);
        }
        if (cooldown > 0.0f) {
            cooldown--;
        }

        if (swordAttack) {
            DrawTextureV(swordTexture, playerPostion, WHITE);
            cooldown = 30.0f;
        }
}