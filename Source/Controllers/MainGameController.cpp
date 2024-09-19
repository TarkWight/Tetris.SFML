#include "MainGameController.hpp"
#include <iostream>
MainGameController::MainGameController() : mainMenuView() {}
MainGameController::~MainGameController() {}

void MainGameController::startGame() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				handleMainMenuEvent(event);
			}
		}
        window.clear();
        mainMenuView.draw(window);
        window.display();
	}	
}

void MainGameController::handleMainMenuEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mainMenuView.isStartButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            // startTetrisGame();
            std::cout << "startTetrisGame/n";
        }
        else if (mainMenuView.isChangeColorButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            // Change color
            std::cout << "Change color/n";
         } else if (mainMenuView.isLeaderboardButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
             // Show leaderboard
                std::cout << "Show leaderboard/n";
        }
        else if (mainMenuView.isExitButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "exit/n";
            exit(0);
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        mainMenuView.handleMouseMove(event.mouseMove.x, event.mouseMove.y);
    }
    else if (event.type == sf::Event::KeyPressed) {
        mainMenuView.handleKeyboardInput(event);
    }
}