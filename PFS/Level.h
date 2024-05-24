//
// Created by Toudonou on 5/23/2024.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "defines.h"

class Level {
public:
    Level(int nbrTilesBySide, Vector2 position);

    ~Level();

    void Update();

private:
    Vector2 m_position{};

    // Store the number of tiles by side
    int m_nbrTileBySide;

    // Store the index of actual target
    Vector2 m_targetIndex{};

    // Store the current mode of the level
    MODE m_mode;

    // Store all the tile in the game
    Tile ***m_tiles = nullptr;

    // Update tiles orientation
    void UpdateTiles() const;
};


#endif //LEVEL_H
