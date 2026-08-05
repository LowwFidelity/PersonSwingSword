#pragma once
#include <string>
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
    void WeaponSwing(player& protag, bool& isInventory)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cooldown <= 0.0f && !isInventory) {
            swordAttack = true;
            attackDuration = 15;
            cooldown = 30.0f;
            protag.getDirection();
        }

        if (swordAttack && protag.getDirection() == "right") {
            swordPosition = { protag.getPosition().x + protag.getstats().size.x, protag.getPosition().y + protag.getstats().size.y / 2};
            angle = 00.0;
        }

        if (swordAttack && protag.getDirection() == "left") {
            swordPosition = { protag.getPosition().x, protag.getPosition().y + protag.getstats().size.y / 2};
            angle = 180.0;
        }

        if (swordAttack && protag.getDirection() == "up") {
            swordPosition = { protag.getPosition().x + protag.getstats().size.x / 2, protag.getPosition().y};
            angle = 270.0;
        }

        if (swordAttack && protag.getDirection() == "down") {
            swordPosition = { protag.getPosition().x + protag.getstats().size.x, protag.getPosition().y + protag.getstats().size.y};
            angle = 90.0;
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
    float getAngle() {
        return angle;
    }
};