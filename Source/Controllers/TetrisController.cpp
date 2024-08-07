//
// Created by Tark Wight on 07.08.2024.
//

#include "TetrisController.hpp"

TetrisController::TetrisController() {
}

void TetrisController::run() {
    while (view.window->isOpen()) {
        events();
        if (!model.isGameOver) {
            model.moveShapeHorizontal();
            model.rotateShape();
            model.moveShapeDown();
            model.updateScore();
            model.initializeShape();
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

