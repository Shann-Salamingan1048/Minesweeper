#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include "Global.h"
#include <iomanip>
class Cells
{
private:
	void initCells();
	sf::Texture TextureAllTypeCells;
	sf::Texture CursorGlove;

	sf::Sprite UnknownCellSprite;
	sf::Sprite EmptyCellSprite;
	sf::Sprite BombCellSprite;
	sf::Sprite NotBombCellSprite;
	sf::Sprite NumberSprite;
	sf::Sprite FlaggedSprite;

	std::vector<std::vector<sf::Sprite>> CellsVector;
	std::vector<sf::Sprite> NumberSpriteVector;

	bool isLeftMouseClicked;
	bool isRightMouseClicked;
	TileMaps tp;
	int count; // for 1 - 9 numbers cells , experimental only
	inline void CalculationsBombNumbers();
	inline void subCalBomb(const uint16_t& Check_i, const uint16_t& Check_k, const uint16_t& i, const uint16_t& k);
public:
	Cells();
	~Cells();
	void ifMouseInClicked(sf::RenderWindow& window);
	void renderCells(sf::RenderWindow& window);

};