//
// Created by Toudonou on 5/25/2024.
//

#include "Agent.h"

#include "RendererManager.h"

Agent::Agent(const Vector2 position, const int speed) {
    m_position = position;
    m_speed = speed;
    m_sprite = new Sprite(getCurrentWorkingDirectory() + R"(\assets\unit.bmp)", m_position);

    m_currentDirection = Vector2::ZERO;
    RendererManager::GetInstance()->AddSprite(m_sprite);
}

Agent::~Agent() {
    delete m_sprite;
}

void Agent::Update() {
    m_position += m_currentDirection * m_speed;

    m_sprite->SetPosition(m_position);
}

void Agent::SetDirection(const Vector2 direction) {
    m_currentDirection = direction;
}

void Agent::SetSpeed(const int speed) {
    m_speed = speed;
}
