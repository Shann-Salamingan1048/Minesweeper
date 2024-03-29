#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

struct CellsDimensions {
	static constexpr int Columns = 10;
	static constexpr int Rows = 10;
	static constexpr int Height = 30; //for the image texture
	static constexpr int Width = 30; // for the image texture
};
class Cells 
{
private:
	void initCells();
	sf::Texture TextureAllTypeCells;
	sf::Texture CursorGlove;
	sf::Sprite SpriteCell;
	sf::Sprite UnknownCellSprite;
	std::vector<std::vector<sf::Sprite>> CellsVector;

	bool isLeftMouseClicked;
	
public:
	Cells();
	~Cells();
	void ifMouseInClicked(sf::RenderWindow& window);
	void renderCells( sf::RenderWindow& window);

};