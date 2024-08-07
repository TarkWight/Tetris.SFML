//
// Created by Tark Wight on 07.08.2024.
//

#include "TetrisModel.hpp"
#include <cstdlib>

TetrisModel::TetrisModel() 
    : directionX(0),
      currentColor(1),
      currentScore(0),
      isRotate(false),
      isGameOver(false),
      timerCount(0.f),
      moveDelay(0.3f) {
    area.resize(LINES);
    for (std::size_t i{}; i < area.size(); i++) {
        area[i].resize(COLS);
    }

    shapes = {
        {1, 3, 5, 7}, // I
        {2, 4, 5, 7}, // Z
        {3, 5, 4, 6}, // S
        {3, 5, 4, 7}, // T
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4, 5}  // O
    };

    std::uint32_t number = std::rand() % SHAPES;
    for (std::size_t i{}; i < SQUARES; i++) {
        currentShapeCoordinates[i].x = shapes[number][i] % 2;
        currentShapeCoordinates[i].y = shapes[number][i] / 2;
    }
}

bool TetrisModel::checkCollision() const {
    for (std::size_t i{}; i < SQUARES; i++) {
        if (currentShapeCoordinates[i].x < 0 ||
            currentShapeCoordinates[i].x >= COLS ||
            currentShapeCoordinates[i].y >= LINES ||
            area[currentShapeCoordinates[i].y][currentShapeCoordinates[i].x]) {
            return true;
        }
    }
    return false;
}

void TetrisModel::initializeShape() {
    directionX = 0;
    isRotate = false;
    moveDelay = 0.3f;
}

void TetrisModel::updateScore() {
    std::uint32_t match = LINES - 1;
    for (std::size_t i = match; i >= 1; --i) {
        std::uint32_t sum{};
        for (std::size_t j{}; j < COLS; j++) {
            if (area[i][j]) {
                if (i == 1) {
                    isGameOver = true;
                }
                ++sum;
            }
            area[match][j] = area[i][j];
        }
        if (sum < COLS) {
            match--;
        } else {
            currentScore++;
        }
    }
}

void TetrisModel::moveShapeHorizontal(int directionX) {
    for (std::size_t i{}; i < SQUARES; i++) {
        previousShapeCoordinates[i] = currentShapeCoordinates[i];
        currentShapeCoordinates[i].x += directionX;
    }

    if (checkCollision()) {
        for (std::size_t i{}; i < SQUARES; i++) {
            currentShapeCoordinates[i] = previousShapeCoordinates[i];
        }
    }
}

void TetrisModel::rotateShape() {
    if (isRotate) {
        Coordinates coords = currentShapeCoordinates[1];
        for (std::size_t i{}; i < SQUARES; i++) {
            int x = currentShapeCoordinates[i].y - coords.y;
            int y = currentShapeCoordinates[i].x - coords.x;

            currentShapeCoordinates[i].x = coords.x - x;
            currentShapeCoordinates[i].y = coords.y + y;
        }

        if (checkCollision()) {
            for (std::size_t i{}; i < SQUARES; i++) {
                currentShapeCoordinates[i] = previousShapeCoordinates[i];
            }
        }
    }
}

void TetrisModel::moveShapeDown() {
    if (timerCount > moveDelay) {
        for (std::size_t i{}; i < SQUARES; i++) {
            previousShapeCoordinates[i] = currentShapeCoordinates[i];
            ++currentShapeCoordinates[i].y;
        }

        if (checkCollision()) {
            for (std::size_t i{}; i < SQUARES; i++) {
                area[previousShapeCoordinates[i].y][previousShapeCoordinates[i].x] = currentColor;
            }

            currentColor = std::rand() % SHAPES + 1;
            std::uint32_t number = std::rand() % SHAPES;
            for (std::size_t i{}; i < SQUARES; i++) {
                currentShapeCoordinates[i].x = shapes[number][i] % 2;
                currentShapeCoordinates[i].y = shapes[number][i] / 2;
            }
        }

        timerCount = 0;
    }
}
