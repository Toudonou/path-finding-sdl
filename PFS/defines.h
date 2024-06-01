//
// Created by Toudonou on 5/23/2024.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>

struct Vector2 {
    int x;
    int y;
    static Vector2 ZERO;
    static Vector2 UP;
    static Vector2 DOWN;
    static Vector2 LEFT;
    static Vector2 RIGHT;


    bool operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    Vector2 operator+(const Vector2 &other) const {
        return {x + other.x, y + other.y};
    }

    void operator+=(const Vector2 &other) {
        x += other.x;
        y += other.y;
    }

    Vector2 operator-(const Vector2 &other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(const int scalar) const {
        return {x * scalar, y * scalar};
    }
};

enum TILE {
    WALL, EMPTY, TARGET, UP, DOWN, DOWN_LEFT, DOWN_RIGHT, LEFT, RIGHT, UP_LEFT, UP_RIGHT
};

enum COLOR {
    UNVISITED, VISITED, PROCESSED
};

enum MODE {
    EDIT, SIMULATION
};

// To generate a random string, especially for the IDs of our components
std::string randomStringGenerator(int stringLength = 26);

std::string getCurrentWorkingDirectory();

#endif //VECTOR2_H
