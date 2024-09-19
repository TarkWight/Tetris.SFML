#include "MainMenuView.hpp"

MainMenuView::MainMenuView() : palette(), hoveredButton(nullptr), selectedButtonIndex(0) {
    initializeButtons();


    if (!font.loadFromFile(resourcePath + "/Fonts/ShoraiSansStdNVar.ttf"))
    {
        throw std::runtime_error("Failed to load Fonts for MainMenuView");
    }

    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(24);
    startText.setFillColor(palette.defaultTextColor);
    startText.setPosition(startButton.getPosition().x + 10, startButton.getPosition().y + 10);

    changeColorText.setFont(font);
    changeColorText.setString("Change Color");
    changeColorText.setCharacterSize(24);
    changeColorText.setFillColor(palette.defaultTextColor);
    changeColorText.setPosition(changeColorButton.getPosition().x + 10, changeColorButton.getPosition().y + 10);

    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(24);
    leaderboardText.setFillColor(palette.defaultTextColor);
    leaderboardText.setPosition(leaderboardButton.getPosition().x + 10, leaderboardButton.getPosition().y + 10);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(palette.defaultTextColor);
    exitText.setPosition(exitButton.getPosition().x + 10, exitButton.getPosition().y + 10);

    selectButton(selectedButtonIndex);
}

void MainMenuView::initializeButtons() {
    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setPosition(300, 150);
    startButton.setFillColor(palette.defaultButtonColor);

    changeColorButton.setSize(sf::Vector2f(200, 50));
    changeColorButton.setPosition(300, 220);
    changeColorButton.setFillColor(palette.defaultButtonColor);

    leaderboardButton.setSize(sf::Vector2f(200, 50));
    leaderboardButton.setPosition(300, 290);
    leaderboardButton.setFillColor(palette.defaultButtonColor);

    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setPosition(300, 360);
    exitButton.setFillColor(palette.defaultButtonColor);
}

void MainMenuView::draw(sf::RenderWindow& window) {
    window.clear(palette.background);
    window.draw(startButton);
    window.draw(changeColorButton);
    window.draw(leaderboardButton);
    window.draw(exitButton);
    window.draw(startText);
    window.draw(changeColorText);
    window.draw(leaderboardText);
    window.draw(exitText);
}

bool MainMenuView::isStartButtonClicked(int mouseX, int mouseY) {
    return startButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool MainMenuView::isChangeColorButtonClicked(int mouseX, int mouseY) {
    return changeColorButton.getGlobalBounds().contains(mouseX, mouseY);
}

 bool MainMenuView::isLeaderboardButtonClicked(int mouseX, int mouseY) {
     return leaderboardButton.getGlobalBounds().contains(mouseX, mouseY);
 }

bool MainMenuView::isExitButtonClicked(int mouseX, int mouseY) {
    return exitButton.getGlobalBounds().contains(mouseX, mouseY);
}

void MainMenuView::handleMouseMove(int mouseX, int mouseY) {
    if (startButton.getGlobalBounds().contains(mouseX, mouseY)) {
        hoveredButton = &startButton;
        selectedButtonIndex = 0;
    }
    else if (changeColorButton.getGlobalBounds().contains(mouseX, mouseY)) {
        hoveredButton = &changeColorButton;
        selectedButtonIndex = 1;
    }
    else if (leaderboardButton.getGlobalBounds().contains(mouseX, mouseY)) {
        hoveredButton = &leaderboardButton;
        selectedButtonIndex = 2;
    }
    else if (exitButton.getGlobalBounds().contains(mouseX, mouseY)) {
        hoveredButton = &exitButton;
        selectedButtonIndex = 2;
    }
    else {
        hoveredButton = nullptr;
    }

    updateButtonAppearance();
}

void MainMenuView::handleKeyboardInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedButtonIndex = (selectedButtonIndex + 3) % 4; // Move up, wrap around
            selectButton(selectedButtonIndex);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedButtonIndex = (selectedButtonIndex + 1) % 4; // Move down, wrap around
            selectButton(selectedButtonIndex);
        }
    }
}

void MainMenuView::selectButton(int index) {
    switch (index) {
    case 0:
        hoveredButton = &startButton;
        break;
    case 1:
        hoveredButton = &changeColorButton;
        break;
    case 2:
        hoveredButton = &leaderboardButton;
        break;
    case 3:
        hoveredButton = &exitButton;
        break;
    default:
        hoveredButton = nullptr;
        break;
    }
    updateButtonAppearance();
}

void MainMenuView::updateButtonAppearance() {
    startButton.setFillColor(hoveredButton == &startButton ? palette.selectedButtonColor : palette.defaultButtonColor);
    changeColorButton.setFillColor(hoveredButton == &changeColorButton ? palette.selectedButtonColor : palette.defaultButtonColor);
    leaderboardButton.setFillColor(hoveredButton == &leaderboardButton ? palette.selectedButtonColor : palette.defaultButtonColor);
    exitButton.setFillColor(hoveredButton == &exitButton ? palette.selectedButtonColor : palette.defaultButtonColor);

    startText.setFillColor(hoveredButton == &startButton ? palette.selectedTextColor : palette.defaultTextColor);
    changeColorText.setFillColor(hoveredButton == &changeColorButton ? palette.selectedTextColor : palette.defaultTextColor);
    leaderboardText.setFillColor(hoveredButton == &leaderboardButton ? palette.selectedTextColor : palette.defaultTextColor);
    exitText.setFillColor(hoveredButton == &exitButton ? palette.selectedTextColor : palette.defaultTextColor);
}