//
// Created by Toudonou on 5/23/2024.
//

#ifndef LEVEL_H
#define LEVEL_H
#include "Vector2.h"


class Level {

public:
    Level(int nbrTiles, Vector2 position);
    ~Level();

    void Update();

private:
    Vector2 m_position{};
    int m_nbrTile;

    // Store all the tile in the game

};



#endif //LEVEL_H
