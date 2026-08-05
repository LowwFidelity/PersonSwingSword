#pragma once
#include <raylib.h>
#include <vector>


const int TILE_SIZE = 16;

class tileMap {
private:
    Texture2D tileset;
    std::vector<std::vector<int>> grid;
  

public:
    void load(const char* filePath) {
        tileset = LoadTexture(filePath);

        int dynamicRows = tileset.height / TILE_SIZE;
        int dynamicCols = tileset.width / TILE_SIZE;

        grid.resize(dynamicRows);
        for (int i = 0; i < dynamicCols; i++) {
            grid[i].resize(dynamicCols);
        }
    }

    void unload() {
        UnloadTexture(tileset);
    }

    void draw() const {
        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid[y].size(); x++) {
                int worldX = x * TILE_SIZE;
                int worldY = y * TILE_SIZE;
                Vector2 position = { worldX, worldY };
                Rectangle source = { worldX, worldY, TILE_SIZE, TILE_SIZE };
                DrawTextureRec(tileset, source, position, WHITE);
            }
        }
    }
    Vector2 getWorldSize() const{
        float worldHeight = grid.size() * TILE_SIZE;
        float worldWidth = grid[0].size() * TILE_SIZE;
        return Vector2{ worldWidth, worldHeight };
    }
};
