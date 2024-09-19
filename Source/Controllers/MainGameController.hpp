#ifndef MAINGAMECONTROLLER_HPP
#define MAINGAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "../Views/MainMenuView.hpp"

class MainGameController{
public:
	MainGameController();
	~MainGameController();
	void startGame();

protected:
	MainMenuView mainMenuView;
	void handleMainMenuEvent(const sf::Event& event);
};

#endif // MAINGAMECONTROLLER_HPP