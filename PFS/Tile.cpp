//
// Created by Toudonou on 5/23/2024.
//

#include "Tile.h"

#include "RendererManager.h"

Tile::Tile(const Vector2 position, const TILE type) {
    m_position = position;
    m_sprite = new Sprite(R"(E:\Dev\path-finding-sdl\assets\tile-empty.bmp)", m_position);

    m_distanceToTarget = 1;
    m_directionToTarget = Vector2::ZERO;
    m_color = COLOR::UNVISITED;

    RendererManager::GetInstance()->AddSprite(m_sprite);
    SetType(type);
}

Tile::~Tile() {
    delete m_sprite;
}

void Tile::Update() {
}

void Tile::SetType(const TILE type) {
    m_type = type;

    switch (m_type) {
        case TILE::WALL:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-wall.bmp)");
            break;
        case TILE::EMPTY:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-empty.bmp)");
            break;
        case TILE::TARGET:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-target.bmp)");
            break;
        case TILE::UP:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-up.bmp)");
            break;
        case TILE::DOWN:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-down.bmp)");
            break;
        case TILE::DOWN_LEFT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-down-left.bmp)");
            break;
        case TILE::DOWN_RIGHT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-down-right.bmp)");
            break;
        case TILE::LEFT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-left.bmp)");
            break;
        case TILE::RIGHT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-right.bmp)");
            break;
        case TILE::UP_LEFT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-up-left.bmp)");
            break;
        case TILE::UP_RIGHT:
            m_sprite->SetTexture(R"(E:\Dev\path-finding-sdl\assets\tile-arrow-up-right.bmp)");
            break;
        default:
            break;
    }
}

void Tile::SetColor(const COLOR color) {
    m_color = color;
}

void Tile::AddDistanceToTarget(const int distance) {
    m_distanceToTarget += distance;
}

void Tile::SetDirectionToTarget(const Vector2 directionToTarget) {
    m_directionToTarget = directionToTarget;
}
