#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include "Cells.h"
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window; // use smart pointers
	sf::Event event;
	sf::VideoMode videoMode;
	Cells cells;
	void initWindow();

public:
	Game();
	~Game();
	const bool isRunning() const;
	void pollEvents();

	void update();
	void render();
};