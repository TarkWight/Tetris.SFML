//
// Created by Tark Wight on 07.08.2024.
//

#ifndef TETRISMODEL_HPP
#define TETRISMODEL_HPP

#include <vector>
#include <cstdint>

class TetrisModel {
public:
    static constexpr std::uint32_t LINES{ 20 };
    static constexpr std::uint32_t COLS{ 10 };
    static constexpr std::uint32_t SQUARES{ 4 };
    static constexpr std::uint32_t SHAPES{ 7 };

    std::vector<std::vector<std::uint32_t>> area;
    std::vector<std::vector<std::uint32_t>> shapes;

    struct Coordinates {
        std::uint32_t x, y;
    };

    int directionX;
    int currentColor;
    int currentScore;
    bool isRotate;
    bool isGameOver;
    float timerCount;
    float moveDelay;

    Coordinates currentShapeCoordinates[SQUARES];
    Coordinates previousShapeCoordinates[SQUARES];

    TetrisModel();

    bool maxLimit();

    bool checkCollision() const;
    int getScore() const;
    void initializeShape();
    void updateScore();
    void moveShapeHorizontal();
    void rotateShape();
    void moveShapeDown();
};

#endif // TETRISMODEL_HPP

