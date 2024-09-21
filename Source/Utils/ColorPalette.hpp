#ifndef COLORPALETTE_HPP
#define COLORPALETTE_HPP

#include <SFML/Graphics.hpp>
#include <array>

struct ColorPalette{
    ColorPalette()
        : defaultButtonColor(183, 180, 242),
        selectedButtonColor(159, 110, 227),
        defaultOutlineColor(178, 73, 174),
        selectedOutlineColor(200, 100, 150),
        defaultTextColor(216, 191, 216),
        selectedTextColor(194, 88, 91),
        background(199, 222, 252) {}

   sf::Color defaultButtonColor;
    sf::Color selectedButtonColor;
    sf::Color defaultOutlineColor;
    sf::Color selectedOutlineColor;
    sf::Color defaultTextColor;
    sf::Color selectedTextColor;
    sf::Color background;
};

#endif //COLORPALETTE_HPP
