//
// Created by Toudonou on 5/23/2024.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "Agent.h"
#include "Tile.h"
#include "defines.h"

class Level {

public:
    Level(int nbrTilesRow, int nbrTilesColumn, Vector2 position);

    ~Level();

    void Update();

private:

    Agent *m_agent = nullptr;

    // Level position
    Vector2 m_position{};

    // Store the number of tiles by side
    int m_tilesRow;
    int m_tilesColumn;

    // Store the index of actual target
    Vector2 m_targetIndex{};

    // Store the current mode of the level
    MODE m_mode;

    // Store all the tile in the game
    Tile ***m_tiles = nullptr;

    // Update tiles orientation
    void UpdateTilesDirection() const;
};


#endif //LEVEL_H
