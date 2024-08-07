//
// Created by Tark Wight on 07.08.2024.
//

#ifndef TETRISVIEW_HPP
#define TETRISVIEW_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Models/TetrisModel.hpp"

class TetrisView {
public:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Texture tiles, bg;
    std::shared_ptr<sf::Sprite> sprite, background;
    sf::Font font;
    sf::Text txtScore, txtGameOver;

    TetrisView();
    void draw(const TetrisModel& model);
    void initializeWindow();
};


#endif //TETRISVIEW_HPP
