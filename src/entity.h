#pragma once
#include <string>
#include <raylib.h>
#include "player.h"

class entity {
private:
	std::string name;
	int health;
	Vector2 position;
	std::string direction;


public:
	entity(std::string n, int hp, Vector2 pos, std::string dir) {
		name = n;
		health = hp;
		position = pos;
		direction = dir;
	}
	std::string getDirection() {
		return direction;
	}
	void setAggro(player protag) {
		if (CheckCollisionCircleRec(position, 100.0f, protag.getHitbox())) {
			DrawCircleLines(1920 / 2, 1080 / 2, 100.0f, BLACK);
			DrawText("Works", position.x + 50, position.y + 50, 30, BLACK);
		}
	}
};

