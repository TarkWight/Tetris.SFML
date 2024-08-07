//
// Created by Tark Wight on 07.08.2024.
//

#include "TetrisView.hpp"

TetrisView::TetrisView() {
    initializeWindow();

    std::string resourcePath = RESOURCE_DIR;
    if (!tiles.loadFromFile(resourcePath + "/Images/squares.png") ||
        !bg.loadFromFile(resourcePath + "/Images/background.png") ||
        !font.loadFromFile(resourcePath + "/Fonts/font.ttf"))
    {
        throw std::runtime_error("Failed to load resources");
    }

    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));

    background = std::make_shared<sf::Sprite>();
    background->setTexture(bg);

    txtScore.setFont(font);
    txtScore.setPosition(100.f, 10.f);
    txtScore.setString("SCORE: 0");
    txtScore.setCharacterSize(30);
    txtScore.setOutlineThickness(3);

    txtGameOver.setFont(font);
    txtGameOver.setPosition(30.f, 300.f);
    txtGameOver.setString("GAME OVER");
    txtGameOver.setCharacterSize(50);
    txtGameOver.setOutlineThickness(3);
}

void TetrisView::initializeWindow() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(360, 720),
        "Tetris",
        sf::Style::Titlebar | sf::Style::Close
    );
    window->setPosition(sf::Vector2i(100, 100));
}

void TetrisView::draw(const TetrisModel& model) {
    window->clear(sf::Color::Black);
    window->draw(*background);

    for (std::size_t i{}; i < TetrisModel::LINES; ++i) {
        for (std::size_t j{}; j < TetrisModel::COLS; ++j) {
            if (model.area[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect(model.area[i][j] * 36, 0, 36, 36));
                sprite->setPosition(j * 36, i * 36);
                window->draw(*sprite);
            }
        }
    }

    for (std::size_t i{}; i < TetrisModel::SQUARES; ++i) {
        sprite->setTextureRect(sf::IntRect(model.currentColor * 36, 0, 36, 36));
        sprite->setPosition(model.currentShapeCoordinates[i].x * 36, model.currentShapeCoordinates[i].y * 36);
        window->draw(*sprite);
    }

    window->draw(txtScore);
    if (model.isGameOver) {
        window->draw(txtGameOver);
    }
    window->display();
}
