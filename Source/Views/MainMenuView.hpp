#ifndef MAINMENUVIEW_HPP
#define MAINMENUVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../Utils/ColorPalette.hpp"

class MainMenuView {
public:
    MainMenuView();
    void draw(sf::RenderWindow& window);
    bool isStartButtonClicked(int mouseX, int mouseY);
    bool isChangeColorButtonClicked(int mouseX, int mouseY);
    bool isLeaderboardButtonClicked(int mouseX, int mouseY);
    bool isExitButtonClicked(int mouseX, int mouseY);

    void handleMouseMove(int mouseX, int mouseY);
    void handleKeyboardInput(const sf::Event& event);

private:
    sf::RectangleShape startButton;
    sf::RectangleShape changeColorButton;
     sf::RectangleShape leaderboardButton;
    sf::RectangleShape exitButton;

    sf::Font font;
    sf::Text startText;
    sf::Text changeColorText;
     sf::Text leaderboardText;
    sf::Text exitText;
    ColorPalette palette;
    sf::RectangleShape* hoveredButton;
    int selectedButtonIndex;

    std::string resourcePath = RESOURCE_DIR;
    void initializeButtons();
    void updateButtonAppearance();
    void selectButton(int index);
};

#endif // MAINMENUVIEW_HPP