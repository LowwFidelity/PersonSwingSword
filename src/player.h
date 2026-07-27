#include <string>
#include <raylib.h>

using namespace std;

class player {
private:
    string name;
    int health;
    int stamina;
    float defense;
    float speed;
    Vector2 position;

public:
    player(string n, int hp, int stm, float def, float spe, Vector2 pos) {
        name = n;
        health = hp;
        stamina = stm;
        defense = def;
        speed = spe;
        position = pos;
    }
    void movement(float dt) {
        if (IsKeyDown(KEY_D)) {
            position.x += speed * dt;
        }
        if (IsKeyDown(KEY_A)) {
            position.x -= speed * dt;
        }

        if (IsKeyDown(KEY_W)) {
            position.y -= speed * dt;
        }
        if (IsKeyDown(KEY_S)) {
            position.y += speed * dt;
        }
    }
    Vector2 getPosition() const {
        return position;
    }

};