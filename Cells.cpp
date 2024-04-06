#include "Cells.h"
void Cells::initCells()
{
	this->count = 0; // experiment to for 1 - 9 number cells
	this->isLeftMouseClicked = false; // for opening cells
	this->isRightMouseClicked = false; // for flagging

	this->TextureAllTypeCells.loadFromFile("MinesweeperSprite/MinesweeperSpriteSheet.png");

	//Unknown Cells
	this->UnknownCellSprite.setTexture(this->TextureAllTypeCells);

	this->UnknownCellSprite.setTextureRect(sf::IntRect(10, 30, Width, Height)); // left, top, width, height
	// Resize CellsVector to match the dimensions
	this->CellsVector.resize(Rows);
	for (auto& row : this->CellsVector)
	{
		row.resize(Columns);
	}
	this->UnknownCellSprite.setScale(SetScale_Width, SetScale_Height); // 30 * 4 = 120 (x) , 30 * 4 = 120 (y) .. 120 x 120



	for (uint16_t i = 0; i < Rows; i++)
	{
		for (uint16_t k = 0; k < Columns; k++)
		{
			this->UnknownCellSprite.setPosition(sf::Vector2(k * this->UnknownCellSprite.getGlobalBounds().width
				, i * this->UnknownCellSprite.getGlobalBounds().height)); // width and height
			this->CellsVector[i][k] = this->UnknownCellSprite;
		}
	}

	// Empty Cell Sprite
	this->EmptyCellSprite.setTexture(this->TextureAllTypeCells);
	this->EmptyCellSprite.setTextureRect(sf::IntRect(43, 30, Width, Height)); // left, top, width, height
	this->EmptyCellSprite.setScale(SetScale_Width, SetScale_Height);  // 30 * 4 = 120 (x) , 30 * 4 = 120 (y) .. 120 x 120

	// Bomb Cell Sprite
	this->BombCellSprite.setTexture(this->TextureAllTypeCells);
	this->BombCellSprite.setTextureRect(sf::IntRect(340, 30, Width, Height));
	this->BombCellSprite.setScale(SetScale_Width, SetScale_Height);

	// not Bomb Cell Sprite
	this->NotBombCellSprite.setTexture(this->TextureAllTypeCells);
	this->NotBombCellSprite.setTextureRect(sf::IntRect(373, 30, Width, Height));
	this->NotBombCellSprite.setScale(SetScale_Width, SetScale_Height);

	// Flagged Sprite Cell
	this->FlaggedSprite.setTexture(this->TextureAllTypeCells);
	this->FlaggedSprite.setTextureRect(sf::IntRect(400, 675, Width, Height));
	this->FlaggedSprite.setScale(SetScale_Width, SetScale_Height);

	// Numbers indicator Cell Vector
	this->SpriteVector.resize(NumberCellsSprite); // resize(11)
	this->NumberSprite.setTexture(this->TextureAllTypeCells); 

	this->SpriteVector[0] = this->EmptyCellSprite; // 0 
	for (uint16_t i = 0; i < 8; i++) // for numbers
	{
		this->NumberSprite.setTextureRect(sf::IntRect((76 + ( (i) * 33)), 30, Width, Height));
		this->NumberSprite.setScale(SetScale_Width, SetScale_Height);

		this->SpriteVector[i + 1] = this->NumberSprite; // 1 - 8
	}
	this->SpriteVector[9] = this->FlaggedSprite; // 9 
	this->SpriteVector[10] = this->BombCellSprite; // 10

}
void Cells::ifMouseInClicked(sf::RenderWindow& window) {
	// Get the mouse position relative to the window
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);


	// Check if the mouse is within the bounds of any cell
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //left clicked mouse
	{
		if (!this->isLeftMouseClicked)
		{
			//std::cout << "Clicked!\n"; 
			isLeftMouseClicked = true;
			for (uint16_t row = 0; row < Rows; row++)
			{
				for (uint16_t column = 0; column < Columns; column++)
				{
					sf::FloatRect cellBounds = this->CellsVector[row][column].getGlobalBounds();
					if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
					{
						std::cout << "Clicked: " << row << ":" << column << "\n";
						std::cout << "Map: " << this->tp.TileMapVector_Init[row][column] << "\n";
						//std::cout << "Rect Text: " << this->SpriteCell.getTextureRect().height << "\n";
						if (this->tp.TileMapVector_Init[row][column] == 0)
						{
							std::set<std::pair<int, int>> isCheckedEmpty;
							expandEmptyCells(row, column, isCheckedEmpty);
						}
						this->SpriteVector[this->tp.TileMapVector_Init[row][column]].setPosition(this->CellsVector[row][column].getPosition());
						this->CellsVector[row][column] = this->SpriteVector[tp.TileMapVector_Init[row][column]];
						
						return; // Exit function if mouse is inside any cell
					}
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // right click mouse for flagging cells
	{
		if (!this->isRightMouseClicked)
		{
			//std::cout << "Clicked!\n"; 
			isRightMouseClicked = true;
			for (uint16_t row = 0; row < Rows; row++)
			{
				for (uint16_t column = 0; column < Columns; column++)
				{
					sf::FloatRect cellBounds = this->CellsVector[row][column].getGlobalBounds();
					if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
					{
						std::cout << "Clicked: " << row << ":" << column << "\n";
						this->FlaggedSprite.setPosition(this->CellsVector[row][column].getPosition());
						this->CellsVector[row][column] = this->FlaggedSprite;

						return; // Exit function if mouse is inside any cell
					}
				}
			}
		}
	}
	else
	{
		this->isLeftMouseClicked = false;
		this->isRightMouseClicked = false;
	}
}

Cells::Cells()
{
	this->initCells();
	this->RandomizeBombs();
	//this->printTileMap_of_Bomb();
	this->CalculationsBombNumbers();
}

Cells :: ~Cells()
{
	std::cout << "Cells.h Destructor!\n";
}
void Cells::renderCells(sf::RenderWindow& window)
{
	for (uint16_t i = 0; i < Rows; i++)
	{
		for (uint16_t k = 0; k < Columns; k++)
		{
			window.draw(this->CellsVector[i][k]);
		}
	}
}