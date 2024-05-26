//
// Created by Toudonou on 5/23/2024.
//

#ifndef TILE_H
#define TILE_H
#include "Sprite.h"
#include "defines.h"


class Tile {
public:
    Tile(Vector2 position, TILE type);

    ~Tile();

    void Update();

    void SetType(TILE type);
    [[nodiscard]] __forceinline TILE GetType() const { return m_type; }

    void SetColor(COLOR color);
    [[nodiscard]] __forceinline COLOR GetColor() const { return m_color; }

    [[nodiscard]] __forceinline Vector2 GetPosition() const { return m_position; }

    void AddDistanceToTarget(int distance);
    [[nodiscard]] __forceinline int GetDistanceToTarget() const { return m_distanceToTarget; }

    void SetDirectionToTarget(Vector2 directionToTarget);
    [[nodiscard]] __forceinline Vector2 GetDirectionToTarget() const { return m_directionToTarget; }

private:
    Vector2 m_position{};

    // Store the tile's sprite
    Sprite *m_sprite = nullptr;

    // Store the tile's type
    TILE m_type{};

    COLOR m_color;

    int m_distanceToTarget;
    Vector2 m_directionToTarget{};
};


#endif //TILE_H
