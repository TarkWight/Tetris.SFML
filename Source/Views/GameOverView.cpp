#include "GameOverView.hpp"

GameOverView::GameOverView(const std::function<void()>& onRestart, const std::function<void()>& onExit)
    : onRestart(onRestart), onExit(onExit) {
    if (!font.loadFromFile(resourcePath + "/Fonts/ShoraiSansStdNVar.ttf")) {
        throw std::runtime_error("Failed to load font for GameOverView");
    }

    background.setFillColor(sf::Color(0, 0, 0, 150));
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");

    scoreText.setFont(font);
    restartText.setFont(font);
    restartText.setString("Restart");
    exitText.setFont(font);
    exitText.setString("Exit");

    // Установите размеры и позиции кнопок
    restartButton.setSize(sf::Vector2f(200, 50));
    exitButton.setSize(sf::Vector2f(200, 50));
    // Позиции кнопок можно задать на основе размера окна или других параметров
}

void GameOverView::draw(sf::RenderWindow& window, const std::string& playerName, int currentScore, const std::vector<ScoreEntry>& leaderboard) {
    // Отрисовка фона и текста
    window.draw(background);
    window.draw(gameOverText);
    scoreText.setString("Score: " + std::to_string(currentScore));
    window.draw(scoreText);

    // Отрисовка кнопок
    window.draw(restartText);
    window.draw(exitText);
}

void GameOverView::handleMouseClick(int mouseX, int mouseY) {
    if (isRestartButtonClicked(mouseX, mouseY)) {
        onRestart(); // Вызов функции перезапуска
    }
    else if (isExitButtonClicked(mouseX, mouseY)) {
        onExit(); // Вызов функции выхода
    }
}

bool GameOverView::isRestartButtonClicked(int mouseX, int mouseY) {
    return restartButton.getGlobalBounds().contains(mouseX, mouseY);
}

bool GameOverView::isExitButtonClicked(int mouseX, int mouseY) {
    return exitButton.getGlobalBounds().contains(mouseX, mouseY);
}
