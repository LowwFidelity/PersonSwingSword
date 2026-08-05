#pragma once
#include <string>
#include <raylib.h>

struct playerStats {
    std::string name;
    int health;
    float stamina;
    float speed;
    Vector2 size;
    Vector2 position;
    std::string direction;
};

class player {
private:
    std::string name;
    int health = 100;
    float stamina = 100.0f;
    float speed = 200.0f;
    Vector2 size = { 16, 16 };
    Vector2 position;
    std::string direction;

public:
    player(std::string n, Vector2 pos, std::string dir) {
        name = n;
        position = pos;
        direction = dir;
    }
    playerStats getstats() const {
        return { name, health, stamina, speed, size, position, direction };
    }
    void movement(float dt) {
        float currentSpeed = speed;
        float sprint = 25.0f * dt;
        float recover = -10.0f * dt;
        if (IsKeyDown(KEY_LEFT_SHIFT) && stamina > 0.0f) {
            currentSpeed = speed * 1.5f;            
            modifyStamina(sprint);
        }  
        else if (IsKeyUp(KEY_LEFT_SHIFT)) {
            modifyStamina(recover);
        }
        if (IsKeyDown(KEY_D)) {
            position.x += currentSpeed * dt;
            direction = "right";
        }
        if (IsKeyDown(KEY_A)) {
            position.x -= currentSpeed * dt;
            direction = "left";
        }

        if (IsKeyDown(KEY_W)) {
            position.y -= currentSpeed * dt;
            direction = "up";
        }
        if (IsKeyDown(KEY_S)) {
            position.y += currentSpeed * dt;
            direction = "down";
        }
    }
    Vector2 getPosition() const {
        return position;
    }
	std::string getDirection() const {
		return direction;
	}
    int getHealth(int chg) {
        if (health >= chg) {
            health -= chg;
        }
        return health;
    }
    float modifyStamina(float chg) {
        stamina -= chg;
        if (stamina < 0) {
            stamina = 0;
        }
        else if (stamina > 100) {
            stamina = 100;
        }
        return stamina;
    }
    Rectangle getHitbox() {
        Rectangle hitbox = { position.x,position.y, size.x, size.y };
        return hitbox;
    }
    void displayStats(player& protag, float gameDt, int screenHeight) {
    #define PlayerBanner CLITERAL(Color){ 251, 194, 84, 190 } //custom color for player stats banner
    #define Health CLITERAL(Color){ 231, 67, 67, 255 } //custom color for player stats banner
    #define Stamina CLITERAL(Color){ 22, 149, 64, 255 } //custom color for player stats banner

        DrawRectangle(0, screenHeight - 150, 500, 250, PlayerBanner);
        //Health bar
        DrawRectangle(20, screenHeight - 140, protag.getHealth(0) * 4, 30, Health);
        DrawText(TextFormat("Health: %4i", protag.getHealth(0)), 25, screenHeight - 140, 30, BLACK);
        //Stamina bar
        DrawRectangle(20, screenHeight - 80, static_cast<float>(stamina) * 4, 30, Stamina);
        DrawText(TextFormat("Stamina: %.0f", static_cast<float>(stamina)), 25, screenHeight - 80, 30, BLACK);

        if (IsKeyPressed(KEY_H)) {
            int dmg = 10;
            protag.getHealth(dmg);
        }
    }
    void draw() {
        DrawRectangleV(getstats().position, size, RED);
    }
};