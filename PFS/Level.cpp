//
// Created by Toudonou on 5/23/2024.
//

#include <queue>
#include <cstdlib>

#include "Level.h"
#include "InputManager.h"


Level::Level(const int nbrTilesBySide, const Vector2 position) {
    m_position = position;
    m_nbrTileBySide = nbrTilesBySide;
    m_targetIndex = {m_nbrTileBySide / 2, m_nbrTileBySide / 2};
    m_mode = MODE::SIMULATION;

    m_tiles = static_cast<Tile ***>(calloc(m_nbrTileBySide, sizeof(Tile **)));
    // TODO: To Improve
    if (m_tiles == nullptr) {
        SDL_Log("Error during m_tiles initialization");
        exit(-1);
    }

    for (int i = 0; i < m_nbrTileBySide; i++) {
        m_tiles[i] = static_cast<Tile **>(calloc(m_nbrTileBySide, sizeof(Tile *)));
        // TODO: To Improve
        if (m_tiles[i] == nullptr) {
            SDL_Log("Error during m_tiles initialization");
            exit(-1);
        }

        for (int j = 0; j < m_nbrTileBySide; ++j) {
            m_tiles[i][j] = new Tile({m_position.x + 48 * i, m_position.y + 48 * j}, TILE::EMPTY);
        }
    }
}

Level::~Level() {
    // TODO: To Improve
    delete [] m_tiles;
};

void Level::Update() {
    const Vector2 mousePosition = {InputManager::GetInstance()->GetMouseX(), InputManager::GetInstance()->GetMouseY()};
    bool targetSet = false;
    Tile *tempSprite = nullptr;

    if (InputManager::GetInstance()->KeyDown(SDL_SCANCODE_ESCAPE)) {
        m_mode = m_mode == MODE::EDIT
                     ? MODE::SIMULATION
                     : MODE::EDIT;
        m_mode == MODE::EDIT ? SDL_Log("Edit mode") : SDL_Log("Simulation mode");
    }

    // Reset all the tiles
    for (int i = 0; i < m_nbrTileBySide; i++) {
        for (int j = 0; j < m_nbrTileBySide; ++j) {
            tempSprite = m_tiles[i][j];
            tempSprite->SetDirectionToTarget(Vector2::ZERO);
            tempSprite->SetColor(COLOR::UNVISITED); // Reset all the tiles color
            if (tempSprite->GetType() != TILE::WALL) tempSprite->SetType(TILE::EMPTY);
        }
    }

    // Update the tiles direction
    UpdateTilesDirection();

    for (int i = 0; i < m_nbrTileBySide; i++) {
        for (int j = 0; j < m_nbrTileBySide; ++j) {
            tempSprite = m_tiles[i][j];

            switch (m_mode) {
                case MODE::EDIT:
                    if (tempSprite->GetPosition().x < mousePosition.x && mousePosition.x < tempSprite->GetPosition().x +
                        48 &&
                        tempSprite->GetPosition().y < mousePosition.y && mousePosition.y < tempSprite->GetPosition().
                        y + 48) {
                        if (InputManager::GetInstance()->MouseButtonPressed(SDL_BUTTON_LEFT) && tempSprite->GetType() !=
                            TILE::WALL) {
                            tempSprite->SetType(TILE::WALL);
                        }
                        if (InputManager::GetInstance()->MouseButtonPressed(SDL_BUTTON_RIGHT) && tempSprite->GetType()
                            == TILE::WALL) {
                            tempSprite->SetType(TILE::EMPTY);
                        }
                    }
                    break;

                case MODE::SIMULATION:
                    m_tiles[m_targetIndex.x][m_targetIndex.y]->SetType(TILE::TARGET);

                // To avoid overwriting on the target at the begining of the game
                    if (m_targetIndex.x == i && m_targetIndex.y == j) continue;

                // Do not set the wall
                    if (tempSprite->GetType() == TILE::WALL) continue;

                // Only one tile should be the target
                    if (!targetSet) {
                        if (tempSprite->GetPosition().x < mousePosition.x && mousePosition.x < tempSprite->GetPosition()
                            .x +
                            48 &&
                            tempSprite->GetPosition().y < mousePosition.y && mousePosition.y < tempSprite->GetPosition()
                            .
                            y + 48) {
                            m_targetIndex = {i, j};
                            targetSet = true;
                        }
                    }

                    Vector2 direction = tempSprite->GetDirectionToTarget();
                    if (direction == Vector2::UP) {
                        tempSprite->SetType(TILE::UP);
                    } else if (direction == Vector2::DOWN) {
                        tempSprite->SetType(TILE::DOWN);
                    } else if (direction == Vector2::LEFT) {
                        tempSprite->SetType(TILE::LEFT);
                    } else if (direction == Vector2::RIGHT) {
                        tempSprite->SetType(TILE::RIGHT);
                    } else if (direction == Vector2::UP + Vector2::LEFT) {
                        tempSprite->SetType(TILE::UP_LEFT);
                    } else if (direction == Vector2::DOWN + Vector2::LEFT) {
                        tempSprite->SetType(TILE::DOWN_LEFT);
                    } else if (direction == Vector2::UP + Vector2::RIGHT) {
                        tempSprite->SetType(TILE::UP_RIGHT);
                    } else if (direction == Vector2::DOWN + Vector2::RIGHT) {
                        tempSprite->SetType(TILE::DOWN_RIGHT);
                    }
                    break;
            }
        }

        // tempSprite->Update();
    }
}

// TODO : Can be improve
void Level::UpdateTilesDirection() const {
    std::queue<Vector2> queue;
    Tile *currentTile = nullptr;
    Vector2 currentPosition = {0, 0};

    m_tiles[m_targetIndex.x][m_targetIndex.y]->AddDistanceToTarget(-1); // distanceToTaget = 1 by default
    m_tiles[m_targetIndex.x][m_targetIndex.y]->SetDirectionToTarget(Vector2::ZERO);
    queue.push(m_targetIndex);

    while (!queue.empty()) {
        currentPosition = queue.front();
        currentTile = m_tiles[currentPosition.x][currentPosition.y];
        currentTile->SetColor(COLOR::PROCESSED);
        queue.pop();

        if (currentTile->GetType() != TILE::WALL) {
            // 0    0    0
            // j    i    0
            // 0    0    0
            if (currentPosition.x - 1 >= 0 && m_tiles[currentPosition.x - 1][currentPosition.y]->GetColor() ==
                COLOR::UNVISITED) {
                m_tiles[currentPosition.x - 1][currentPosition.y]->AddDistanceToTarget(
                    currentTile->GetDistanceToTarget());

                m_tiles[currentPosition.x - 1][currentPosition.y]->SetDirectionToTarget(
                    Vector2::RIGHT);

                m_tiles[currentPosition.x - 1][currentPosition.y]->SetColor(COLOR::VISITED);
                queue.push({currentPosition.x - 1, currentPosition.y});
            }

            // 0    0    0
            // 0    i    j
            // 0    0    0
            if (currentPosition.x + 1 < m_nbrTileBySide && m_tiles[currentPosition.x + 1][currentPosition.y]->GetColor()
                == COLOR::UNVISITED) {
                m_tiles[currentPosition.x + 1][currentPosition.y]->AddDistanceToTarget(
                    currentTile->GetDistanceToTarget());

                m_tiles[currentPosition.x + 1][currentPosition.y]->SetDirectionToTarget(
                    Vector2::LEFT);

                m_tiles[currentPosition.x + 1][currentPosition.y]->SetColor(COLOR::VISITED);
                queue.push({currentPosition.x + 1, currentPosition.y});
            }

            // 0    j    0
            // 0    i    0
            // 0    0    0
            if (currentPosition.y - 1 >= 0 && m_tiles[currentPosition.x][currentPosition.y - 1]->GetColor() ==
                COLOR::UNVISITED) {
                m_tiles[currentPosition.x][currentPosition.y - 1]->AddDistanceToTarget(
                    currentTile->GetDistanceToTarget());

                m_tiles[currentPosition.x][currentPosition.y - 1]->SetDirectionToTarget(
                    Vector2::DOWN);

                m_tiles[currentPosition.x][currentPosition.y - 1]->SetColor(COLOR::VISITED);
                queue.push({currentPosition.x, currentPosition.y - 1});
            }

            // 0    0    0
            // 0    i    0
            // 0    j    0
            if (currentPosition.y + 1 < m_nbrTileBySide && m_tiles[currentPosition.x][currentPosition.y + 1]->GetColor()
                == COLOR::UNVISITED) {
                m_tiles[currentPosition.x][currentPosition.y + 1]->AddDistanceToTarget(
                    currentTile->GetDistanceToTarget());

                m_tiles[currentPosition.x][currentPosition.y + 1]->SetDirectionToTarget(
                    Vector2::UP);

                m_tiles[currentPosition.x][currentPosition.y + 1]->SetColor(COLOR::VISITED);
                queue.push({currentPosition.x, currentPosition.y + 1});
            }

            // j    0    0
            // 0    i    0
            // k    0    0
            if (currentPosition.x - 1 >= 0 && m_tiles[currentPosition.x - 1][currentPosition.y]->GetType() !=
                TILE::WALL) {
                // j
                if (currentPosition.y - 1 >= 0 && m_tiles[currentPosition.x][currentPosition.y - 1]->GetType() !=
                    TILE::WALL && m_tiles[currentPosition.x - 1][currentPosition.y - 1]->GetColor() ==
                    COLOR::UNVISITED) {
                    m_tiles[currentPosition.x - 1][currentPosition.y - 1]->AddDistanceToTarget(
                        currentTile->GetDistanceToTarget());

                    m_tiles[currentPosition.x - 1][currentPosition.y - 1]->SetDirectionToTarget(
                        Vector2::DOWN + Vector2::RIGHT);

                    m_tiles[currentPosition.x - 1][currentPosition.y - 1]->SetColor(COLOR::VISITED);
                    queue.push({currentPosition.x - 1, currentPosition.y - 1});
                }
                // k
                if (currentPosition.y + 1 < m_nbrTileBySide && m_tiles[currentPosition.x][currentPosition.y + 1]->
                    GetType() != TILE::WALL && m_tiles[currentPosition.x - 1][currentPosition.y + 1]->GetColor() ==
                    COLOR::UNVISITED) {
                    m_tiles[currentPosition.x - 1][currentPosition.y + 1]->AddDistanceToTarget(
                        currentTile->GetDistanceToTarget());

                    m_tiles[currentPosition.x - 1][currentPosition.y + 1]->SetDirectionToTarget(
                        Vector2::UP + Vector2::RIGHT);

                    m_tiles[currentPosition.x - 1][currentPosition.y + 1]->SetColor(COLOR::VISITED);
                    queue.push({currentPosition.x - 1, currentPosition.y + 1});
                }
            }

            // 0    0    j
            // 0    i    0
            // 0    0    k
            if (currentPosition.x + 1 < m_nbrTileBySide && m_tiles[currentPosition.x + 1][currentPosition.y]->GetType()
                != TILE::WALL) {
                // j
                if (currentPosition.y - 1 >= 0 && m_tiles[currentPosition.x][currentPosition.y - 1]->GetType() !=
                    TILE::WALL && m_tiles[currentPosition.x + 1][currentPosition.y - 1]->GetColor() ==
                    COLOR::UNVISITED) {
                    m_tiles[currentPosition.x + 1][currentPosition.y - 1]->AddDistanceToTarget(
                        currentTile->GetDistanceToTarget());

                    m_tiles[currentPosition.x + 1][currentPosition.y - 1]->SetDirectionToTarget(
                        Vector2::DOWN + Vector2::LEFT);

                    m_tiles[currentPosition.x + 1][currentPosition.y - 1]->SetColor(COLOR::VISITED);
                    queue.push({currentPosition.x + 1, currentPosition.y - 1});
                }
                // k
                if (currentPosition.y + 1 < m_nbrTileBySide && m_tiles[currentPosition.x][currentPosition.y + 1]->
                    GetType() != TILE::WALL && m_tiles[currentPosition.x + 1][currentPosition.y + 1]->GetColor() ==
                    COLOR::UNVISITED) {
                    m_tiles[currentPosition.x + 1][currentPosition.y + 1]->AddDistanceToTarget(
                        currentTile->GetDistanceToTarget());

                    m_tiles[currentPosition.x + 1][currentPosition.y + 1]->SetDirectionToTarget(
                        Vector2::UP + Vector2::LEFT);

                    m_tiles[currentPosition.x + 1][currentPosition.y + 1]->SetColor(COLOR::VISITED);
                    queue.push({currentPosition.x + 1, currentPosition.y + 1});
                }
            }
        }
    }
}
