//
// Created by Toudonou on 5/23/2024.
//

#include "defines.h"

Vector2 Vector2::ZERO = {0, 0};
Vector2 Vector2::UP = {0, -1};
Vector2 Vector2::DOWN = {0, 1};
Vector2 Vector2::LEFT = {-1, 0};
Vector2 Vector2::RIGHT = {1, 0};

std::string randomStringGenerator(const int stringLength) {
    const std::string characters =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
    const int charactersLength = characters.length();
    std::string result;

    for (int i = 0; i < stringLength; ++i) {
        result += characters[rand() % charactersLength];
    }
    return result;
}
