#include <string>
#include <raylib.h>

using namespace std;

class player {
private:
    string name;
    int health;
    float stamina;
    float defense;
    float speed;
    Vector2 position;
    string direction;

public:
    player(string n, int hp, float stm, float def, float spe, Vector2 pos, string dir) {
        name = n;
        health = hp;
        stamina = stm;
        defense = def;
        speed = spe;
        position = pos;
        direction = dir;
    }
    void movement(float dt) {
        if (IsKeyDown(KEY_D)) {
            position.x += speed * dt;
            direction = "right";
        }
        if (IsKeyDown(KEY_A)) {
            position.x -= speed * dt;
            direction = "left";
        }

        if (IsKeyDown(KEY_W)) {
            position.y -= speed * dt;
            direction = "up";
        }
        if (IsKeyDown(KEY_S)) {
            position.y += speed * dt;
            direction = "down";
        }
    }
    Vector2 getPosition() const {
        return position;
    }
	string getDirection() const {
		return direction;
	}
    int getHealth(int chg) {
		if (health >= chg) health -= chg;
        return health;
    }
    float getStamina(float chg) {
		if (stamina > 0 && chg > 0) stamina -= chg;
        else if (chg < 0 && stamina < 100) stamina -= chg;
        return stamina;
    }
    float getDefense() {
        return defense;
    }
};