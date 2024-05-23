//
// Created by Toudonou on 5/23/2024.
//

#include "Level.h"

Level::Level(int nbrTiles, Vector2 position) {
    m_position = position;
    m_nbrTile = nbrTiles;
}

Level::~Level() = default;

void Level::Update() {
}
