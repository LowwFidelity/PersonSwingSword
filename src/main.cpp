#include <iostream>
#include <cstdlib>
#include <string>
#include <raylib.h>
#include "config.h"
#include "player.h"
#include "entity.h"
#include "tilemap.h"
#include "weapon.h"


const int screenWidth = 1920;
const int screenHeight = 1080;

void OpenInventory(float& slide, float maxSlide, float realDt, player& protag);
void IsGameOver(player& protag, float& realDt, Vector2& spawn);

int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, Game::PROJECT_NAME);
    ToggleFullscreen();
    SetTargetFPS(60);

    //Textures
    Image img = LoadImage("assets/graphics/CrapSword.png"); //crapsword texture
    ImageResizeNN(&img, 32, 32);
    Texture2D swordTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    //Tilemap Variables
    tileMap map;
    map.load("assets/Tiles/Test Tile.png");
    Vector2 mapBoundary = map.getWorldSize();
    Vector2 spawn = { mapBoundary.x / 2, mapBoundary.y / 2 };

    //Player Variables
    bool isDead = false;
    player protag{ "Dusk", spawn, "right"};
    playerStats stats = protag.getstats();
    entity enemy{ "Enemy", 10, spawn, "right" };
	Camera2D camera = { 0 };
	camera.target = protag.getPosition();
	camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.zoom = 3.0f;
    
    //Inventory Variables
    bool isInventory = false;
    float slide = 0;
    float maxSlide = screenWidth - 1140;

    //Sword Variables    
    weapons crapSword;
    crapSword.setName("Crap Sword");
    crapSword.WeaponSwing(protag, isInventory);

    // Main game loop

    while (!WindowShouldClose())
    {
        float realDt = GetFrameTime();
        float gameDt;
        if (isInventory || isDead) {
            gameDt = 0.0f;
        }
        else {
            gameDt = realDt;
        }

        //player movement
        protag.movement(gameDt);
        camera.target = { protag.getPosition() };
        camera.zoom = camera.zoom * (1.0f + (static_cast<float>(GetMouseWheelMove()) * 0.05f));
        if (camera.zoom > 4.0f) camera.zoom = 4.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        crapSword.WeaponSwing(protag, isInventory);

        //player inventory
        if (IsKeyPressed(KEY_TAB))
        {
            if (isInventory == false) isInventory = true;
            else if (isInventory == true) isInventory = false, slide = 0;
        }

        //Draw
        BeginDrawing();
        ClearBackground(BLACK);

        
        //Camera
        BeginMode2D(camera);
        map.draw();
        protag.draw();
        enemy.setAggro(protag);

        //Player Attack
        if (crapSword.getSwordAttack()) {
            DrawTextureEx(swordTexture, crapSword.getPosition(), crapSword.getAngle(), 1.0f, WHITE);
        }

        EndMode2D();

        if (isInventory) {
            protag.OpenInventory(slide, maxSlide, realDt, screenWidth, screenHeight);
        }
        protag.displayStats(protag, gameDt, screenHeight);

        if (protag.getHealth(0) <= 0) {
            isDead = true;
            protag.IsDead(screenWidth, screenHeight, spawn);
            realDt = 0;
        }
        else {
            isDead = false;
            realDt = GetFrameTime();
        }
        EndDrawing();
    }
    map.unload();
    CloseWindow();

    return EXIT_SUCCESS;
}
