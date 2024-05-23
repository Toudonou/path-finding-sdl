//
// Created by Toudonou on 5/23/2024.
//

#ifndef TILE_H
#define TILE_H
#include "Sprite.h"
#include "Vector2.h"

enum TILE {
    WALL, EMPTY, TARGET, UP, DOWN, DOWN_LEFT, DOWN_RIGHT, LEFT, RIGHT, UP_LEFT, UP_RIGHT
};

class Tile {
public:
    Tile(Vector2 position, TILE type);

    ~Tile();

    void Update();

    void SetType(TILE type);

    [[nodiscard]] inline TILE GetType() const { return m_type; };

private:
    Vector2 m_position{};

    // Store the tile's sprite
    Sprite *m_sprite = nullptr;

    // Store the tile's type
    TILE m_type;
};


#endif //TILE_H
