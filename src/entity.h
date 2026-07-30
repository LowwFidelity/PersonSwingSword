#pragma once
#include <string>
#include <raylib.h>
#include "player.h"

class entity {
private:
	std::string name;
	int health;
	float damage;
	float defense;
	float poise;
	Vector2 position;
	string direction;


public:
	entity(std::string n, int hp, float dmg, float def, float poi, Vector2 pos, string dir) {
		std::string name;
		health = hp;
		damage = dmg;
		defense = def;
		poise = poi;
		position = pos;
		direction = dir;
	}
	string getDirection() {
		return direction;
	}
	void aggro(player protag) {
		if (CheckCollisionCircleRec(position, 100.0f, protag.getHitbox())) { //still needs work figuring out the logic
			DrawText("Works", position.x + 50, position.y + 50, 30, BLACK);
		}
	}
	void invincibility() {

	}
};