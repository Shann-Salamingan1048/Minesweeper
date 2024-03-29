#include "Cells.h"
void Cells::initCells()
{
	this->isLeftMouseClicked = false;
	this->TextureAllTypeCells.loadFromFile("MinesweeperSprite/MinesweeperSpriteSheet.png");
	this->SpriteCell.setTexture(this->TextureAllTypeCells);

	this->SpriteCell.setTextureRect(sf::IntRect(10, 30, CellsDimensions::Width, CellsDimensions::Height)); // left, top, width, height
	// Resize CellsVector to match the dimensions
	this->CellsVector.resize(CellsDimensions::Rows);
	for (auto& row : this->CellsVector)
	{
		row.resize(CellsDimensions::Columns);
	}
	this->SpriteCell.setScale(4, 4); // 30 * 4 = 120 (x) , 30 * 4 = 120 (y) .. 120 x 120
	this->UnknownCellSprite = this->SpriteCell;
	for (uint16_t i = 0; i < CellsDimensions::Rows; i++)
	{
		for (uint16_t k = 0; k < CellsDimensions::Columns; k++)
		{
			this->SpriteCell.setPosition(sf::Vector2(i * this->SpriteCell.getGlobalBounds().width
				, k * this->SpriteCell.getGlobalBounds().height));
			this->CellsVector[i][k] = this->SpriteCell;
		}
	}
}
void Cells::ifMouseInClicked(sf::RenderWindow& window) {
	// Get the mouse position relative to the window
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	
	// Check if the mouse is within the bounds of any cell
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->isLeftMouseClicked)
		{
			//std::cout << "Clicked!\n"; 
			isLeftMouseClicked = true;
			for (uint16_t i = 0; i < CellsDimensions::Rows; i++)
			{
				for (uint16_t k = 0; k < CellsDimensions::Columns; k++)
				{
					sf::FloatRect cellBounds = this->CellsVector[i][k].getGlobalBounds();
					if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
					{
						std::cout << "Clicked: " << i << ":" << k << "\n";
						

					return; // Exit function if mouse is inside any cell
					}
				}
			}
		}
	}
	else
	{
		this->isLeftMouseClicked = false;
	}
}

Cells::Cells()
{
	this->initCells();
	
}
Cells :: ~Cells()
{
	std::cout << "Cells.h Destructor!\n";
}
void Cells::renderCells( sf::RenderWindow& window)
{
	for (uint16_t i = 0; i < CellsDimensions::Rows; i++)
	{
		for (uint16_t k = 0; k < CellsDimensions::Columns; k++)
		{
			window.draw(this->CellsVector[i][k]);
		}
	}
}