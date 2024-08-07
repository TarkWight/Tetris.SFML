//
// Created by Tark Wight on 07.08.2024.
//

#ifndef TETRISCONTROLLER_HPP
#define TETRISCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Models/TetrisModel.hpp"
#include "Views/TetrisView.hpp"

class TetrisController {
private:
    TetrisModel model;
    TetrisView view;
    sf::Clock clock;

public:
    TetrisController();
    void run();
    void events();
};

#endif //TETRISCONTROLLER_HPP
