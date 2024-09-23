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

    restartButton.setSize(sf::Vector2f(200, 50));
    exitButton.setSize(sf::Vector2f(200, 50));
}

void GameOverView::draw(sf::RenderWindow& window, const std::string& playerName, int currentScore, const std::vector<ScoreEntry>& leaderboard) {
    window.draw(background);
    window.draw(gameOverText);
    scoreText.setString("Score: " + std::to_string(currentScore));
    window.draw(scoreText);

    window.draw(restartText);
    window.draw(exitText);
}