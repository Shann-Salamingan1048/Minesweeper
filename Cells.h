#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
typedef struct {
	static constexpr int Columns = 1;
	static constexpr int Rows = 1;
} ByCells;
class Cells
{
private:
	void initCells();
	sf::RectangleShape cell;
	std::vector<sf::RectangleShape> CellsVector;
	
public:
	Cells();
	~Cells();

	void renderCells(const sf::RenderWindow& window);

};