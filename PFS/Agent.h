//
// Created by Toudonou on 5/25/2024.
//

#ifndef AGENT_H
#define AGENT_H
#include "defines.h"
#include "Sprite.h"


class Agent {
public:
    Agent(Vector2 position, int speed);

    ~Agent();

    void Update();

    void SetDirection(Vector2 direction);

    void SetSpeed(int speed);

    [[nodiscard]] __forceinline Vector2 GetPosition() const { return m_position; }

private:
    Vector2 m_position{};

    // Store the tile's sprite
    Sprite *m_sprite = nullptr;

    Vector2 m_currentDirection{};

    int m_speed;
};


#endif //AGENT_H
