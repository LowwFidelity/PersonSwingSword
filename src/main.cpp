#include <iostream>
#include <cstdlib>
#include <string>
#include <raylib.h>
#include "config.h"
#include "player.h"

using namespace std;

const int screenWidth = 1920;
const int screenHeight = 1080;

struct weapon {
    string name;
    int attackDuration;
    bool swordAttack;
    float cooldown;
    float damage;
    float speed;
    float defense;
    float weight;
};

void WeaponSwing(Vector2& swordPosition, weapon& type, Vector2& playerPostion, Vector2& playerSize, Vector2& swordSize, float& angle, bool& isInventory);
void OpenInventory(float& slide, float maxSlide, float realDt);
//void WeaponSwing(Vector2& swordPosition, float& cooldown, bool& isInventory, int& attackDuration, bool& swordAttack, Vector2& playerPostion, Vector2& playerSize, Vector2& swordSize, float& angle);


int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, Game::PROJECT_NAME);
    ToggleFullscreen();
    SetTargetFPS(60);

    //Textures

    Image img = LoadImage("assets/graphics/CrapSword.png");
    ImageResizeNN(&img, 32, 32);
    Texture2D swordTexture = LoadTextureFromImage(img);
    UnloadImage(img);


    //Player Variables

    player protag{ "Dusk", 100, 100, 10.0f, 200.0f, { (float)screenWidth / 2, (float)screenHeight / 2 } };
    Vector2 playerSize = { 50, 50 };

    //Sword Variables

    Vector2 swordSize = { 32, 32 };
    bool swordAttack = false;
    int attackDuration = 0;
    float cooldown = 0.0f;
    bool isInventory = false, crash = true;
    Vector2 swordPosition = { protag.getPosition().x + playerSize.x, protag.getPosition().y + playerSize.y / 2 };
    float angle = 0;

    weapon crapSword = { "Crap Sword", 15, false, 30.0f, 10.0f, 1.0f, 0.0f, 0.0f };

    //Inventory Variables

    float slide = 0;
    float maxSlide = screenWidth - 1140;


    // Main game loop

    while (!WindowShouldClose())
    {
        float realDt = GetFrameTime();
        float gameDt;

        if (isInventory) {
            gameDt = 0.0f;
        }
        else {
            gameDt = realDt;
        }
        //player movement

        protag.movement(gameDt);

        //player inventory

        if (IsKeyPressed(KEY_TAB))
        {
            if (isInventory == false) isInventory = true;
            else if (isInventory == true) isInventory = false, slide = 0;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        //player attack

        DrawRectangleV(protag.getPosition(), playerSize, RED);
        WeaponSwing(swordPosition, crapSword, protag.getPosition(), playerSize, swordSize, angle, isInventory);

        if (crapSword.swordAttack) {
            DrawTextureEx(swordTexture, swordPosition, angle, 1.0f, WHITE);
        }

        if (isInventory) {
            OpenInventory(slide, maxSlide, realDt);
        }

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

void WeaponSwing(Vector2& swordPosition, weapon& type, Vector2& playerPostion, Vector2& playerSize, Vector2& swordSize, float& angle, bool& isInventory)
{
   

    if (IsKeyDown(KEY_D)) {
        swordPosition = { playerPostion.x + playerSize.x, playerPostion.y + playerSize.y / 2 };
        if (!type.swordAttack) {
            angle = 00.0;
        }
    }
    if (IsKeyDown(KEY_A)) {
        swordPosition = { playerPostion.x, playerPostion.y + playerSize.y / 2 };
        if (!type.swordAttack) {
            angle = 180.0;
        }
    }
    if (IsKeyDown(KEY_W)) {
        swordPosition = { playerPostion.x + playerSize.x / 2, playerPostion.y };
        if (!type.swordAttack) {
            angle = 270.0;
        }
    }
    if (IsKeyDown(KEY_S)) {
        swordPosition = { playerPostion.x + playerSize.x, playerPostion.y + playerSize.y };
        if (!type.swordAttack) {
            angle = 90.0;
        }
    }
 

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && type.cooldown <= 0.0f && !isInventory) {
        type.swordAttack = true;
        type.attackDuration = 15;
        type.cooldown = 30.0f;
    }
    if (type.attackDuration > 0) {
        type.attackDuration--;
    }
    else if (!isInventory) {
        type.swordAttack = false;
    }
    if (type.cooldown > 0.0f) {
        type.cooldown--;
    }
}

void OpenInventory(float& slide, float maxSlide, float realDt) {
#define INVENTORY       CLITERAL(Color){ 130, 130, 130, 200 } //custom color for inventory panel
#define BACKGROUND      CLITERAL(Color){ 40, 40, 40, 200 }    //custom color for creating background fading

    DrawRectangle(0, 0, screenWidth, screenHeight, BACKGROUND);

    if (slide <= maxSlide) {
        DrawRectangle(570, 100, slide, screenHeight - 180, INVENTORY);
        if (slide - 100 <= maxSlide) {
            DrawRectangle(670, 140, slide - 200.0f, 500, BLACK);
        }
        if (slide < maxSlide) {
            slide += 2000.0f * realDt;
            if (slide > maxSlide) {
                slide = maxSlide;
            }
        }
    }
}
