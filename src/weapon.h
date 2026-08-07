#pragma once
#include <string>
#include <cmath>
#include <raylib.h>
#include "player.h"

class weapons {
private:
    std::string name;
    int attackDuration;
    bool swordAttack = false;
    float cooldown;
    Vector2 swordPosition;
    Vector2 swordSize;
    float angle;
public:
    std::string setName(std::string nam) {
        name = nam;
        return name;
    }
    void WeaponSwing(player& protag, bool& isInventory, Camera2D& camera)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cooldown <= 0.0f && !isInventory) {
            swordAttack = true;
            attackDuration = 15;
            cooldown = 30.0f;
        }

        if (swordAttack) {
            angle = getAngle(protag, camera);
            swordPosition.x = (protag.getPosition().x + 8) + 16 * cosf(angle * DEG2RAD);
            swordPosition.y = (protag.getPosition().y + 8) + 16 * sinf(angle * DEG2RAD);
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
    }
    bool getSwordAttack() {
        return swordAttack;
    }
    Vector2 getPosition() {
        return swordPosition;
    }
    float getAngle(player& protag, Camera2D& camera) { 
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        float dx = mouseWorldPos.x - protag.getPosition().x;
        float dy = mouseWorldPos.y - protag.getPosition().y;

        angle = atan2f(dy, dx) * RAD2DEG; 


        return angle;
    }
};