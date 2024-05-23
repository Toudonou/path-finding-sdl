//
// Created by Toudonou on 5/23/2024.
//

#include "defines.h"

std::string randomStringGenerator(const int stringLength) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
    const int charactersLength = characters.length();
    std::string result;

    for (int i = 0; i < stringLength; ++i) {
        result += characters[rand() % charactersLength];
    }
    return result;
}
