//
// Created by Tark Wight on 07.08.2024.
//

#include "TetrisController.hpp"

TetrisController::TetrisController() {}

Leaderboard leaderboard;

void TetrisController::run() {
    while (view.window->isOpen()) {
        events();
        if (!model.isGameOver) {
            model.moveShapeHorizontal();
            model.rotateShape();
            model.moveShapeDown();
            model.updateScore();
            model.initializeShape();
        } else {
            // Добавляем результат в таблицу лидеров
            std::string playerName = "Player"; // Замените на имя игрока
            leaderboard.addScore(playerName, model.currentScore);
            leaderboard.print();
            view.window->close();
        }
        view.draw(model);
    }
}

void TetrisController::events() {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    model.timerCount += time;

    auto e = std::make_shared<sf::Event>();
    while (view.window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            view.window->close();
        }

        if (e->type == sf::Event::KeyPressed) {
            if (e->key.code == sf::Keyboard::Up) {
                model.isRotate = true;
            } else if (e->key.code == sf::Keyboard::Right) {
                ++model.directionX;
            } else if (e->key.code == sf::Keyboard::Left) {
                --model.directionX;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        model.moveDelay = 0.05f;
    }
}

