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
	this->UnknownCellSprite.setScale(4, 4); // 30 * 4 = 120 (x) , 30 * 4 = 120 (y) .. 120 x 120



	for (uint16_t i = 0; i < Rows; i++)
	{
		for (uint16_t k = 0; k < Columns; k++)
		{
			this->UnknownCellSprite.setPosition(sf::Vector2(i * this->UnknownCellSprite.getGlobalBounds().width
				, k * this->UnknownCellSprite.getGlobalBounds().height));
			this->CellsVector[i][k] = this->UnknownCellSprite;
		}
	}

	// Empty Cell Sprite
	this->EmptyCellSprite.setTexture(this->TextureAllTypeCells);
	this->EmptyCellSprite.setTextureRect(sf::IntRect(43, 30, Width, Height)); // left, top, width, height
	this->EmptyCellSprite.setScale(4, 4);  // 30 * 4 = 120 (x) , 30 * 4 = 120 (y) .. 120 x 120

	// Bomb Cell Sprite
	this->BombCellSprite.setTexture(this->TextureAllTypeCells);
	this->BombCellSprite.setTextureRect(sf::IntRect(340, 30, Width, Height));
	this->BombCellSprite.setScale(4, 4);

	// not Bomb Cell Sprite
	this->NotBombCellSprite.setTexture(this->TextureAllTypeCells);
	this->NotBombCellSprite.setTextureRect(sf::IntRect(373, 30, Width, Height));
	this->NotBombCellSprite.setScale(4, 4);

	// Numbers indicator Cell Vector
	this->NumberSpriteVector.resize(Number_ofNumberCellsSprite); // resize
	this->NumberSprite.setTexture(this->TextureAllTypeCells);
	for (uint16_t i = 0; i < Number_ofNumberCellsSprite; i++)
	{
		this->NumberSprite.setTextureRect(sf::IntRect((76 + (i * 33)), 30, Width, Height));
		this->NumberSprite.setScale(4, 4);

		this->NumberSpriteVector[i] = this->NumberSprite;
	}
	// Flagged Sprite Cell
	this->FlaggedSprite.setTexture(this->TextureAllTypeCells);
	this->FlaggedSprite.setTextureRect(sf::IntRect(400, 675, Width, Height));
	this->FlaggedSprite.setScale(4, 4);
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
			for (uint16_t i = 0; i < Rows; i++)
			{
				for (uint16_t k = 0; k < Columns; k++)
				{
					sf::FloatRect cellBounds = this->CellsVector[i][k].getGlobalBounds();
					if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
					{
						std::cout << "Clicked: " << i << ":" << k << "\n";
						//std::cout << "Rect Text: " << this->SpriteCell.getTextureRect().height << "\n";

						this->NumberSpriteVector[this->count % Number_ofNumberCellsSprite].setPosition(this->CellsVector[i][k].getPosition());
						this->CellsVector[i][k] = this->NumberSpriteVector[this->count % Number_ofNumberCellsSprite];
						this->count++;
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
			for (uint16_t i = 0; i < Rows; i++)
			{
				for (uint16_t k = 0; k < Columns; k++)
				{
					sf::FloatRect cellBounds = this->CellsVector[i][k].getGlobalBounds();
					if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
					{
						std::cout << "Clicked: " << i << ":" << k << "\n";
						this->FlaggedSprite.setPosition(this->CellsVector[i][k].getPosition());
						this->CellsVector[i][k] = this->FlaggedSprite;

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
	this->CalculationsBombNumbers();
}
inline void Cells::CalculationsBombNumbers()
{
	// o o o
	// o B o
	// o o o
	// Blocks anatomy up

	// experimentation for knowing how many bombs
	for (uint16_t i = 0; i < Rows; i++)
	{
		for (uint16_t k = 0; k < Columns; k++)
		{
			if (this->tp.TileMapVector_Init[i][k] == 0) // empty
			{
				continue;
			}
			else if (this->tp.TileMapVector_Init[i][k] == 10) // bomb
			{
				if ((i != 0 && i != Rows - 1) && (k != 0 && k != Columns - 1)) // if it is in 8 blocks check , not in beginning
					// not in the very right or very left and not in last
				{
					for (uint16_t l = 0; l < 3; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 3; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((i == 0) && (k == 0)) // Upper Left edge, 3 blocks check
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if (k == 0 && (i != 0 && i != Rows - 1)) // very left , no uppper or lower edge, 5 blocks 
				{ 
					for (uint16_t l = 0; l < 3; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((i == Rows - 1) && (k == 0)) // Lower Left Edge, 3 blocks
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((i == 0) && (k != 0 && k != Columns - 1)) // very upper , no left edge and right edge, 5 blocks
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i + l;
						for (uint16_t p = 0; p < 3; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((i == 0) && (k == Columns - 1)) // upper right edge , 3 blocks 
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((k == Columns - 1) && (i != 0 && i != Rows - 1)) // very right, 5 blocks
				{
					for (uint16_t l = 0; l < 3; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((k == Columns - 1) && (i == Rows - 1)) // Lower Right Edge,  3 blocks
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 2; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k);
						}
					}
				}
				else if ((i == Rows - 1) && ((k != 0 && k != Columns - 1)))
				{
					for (uint16_t l = 0; l < 2; l++)
					{
						uint16_t Check_i = i - 1 + l;
						for (uint16_t p = 0; p < 3; p++)
						{
							uint16_t Check_k = k - 1 + p;
							subCalBomb(Check_i, Check_k, i, k); 
						}
					}
				}
			}

		}
	}
	for (const auto& i : tp.TileMapVector_Init)
	{
		for (const auto& k : i)
		{
			std::cout << std::setw(5) << "" << k << ", ";
		}
		std::cout << "\n";
	}
}
inline void Cells::subCalBomb(const uint16_t& Check_i, const uint16_t& Check_k, const uint16_t& i, const uint16_t& k)
{
	if (Check_k == k && Check_i == i) // if it is center then skip
		return;
	else
	{
		if (tp.TileMapVector_Init[Check_i][Check_k] == 10) // if bomb
		{
			return;
		}
		else // if it is 0 - 7
		{
			std::cout << "Check i : " << Check_i << ", Check K: " << Check_k << "\n";
			tp.TileMapVector_Init[Check_i][Check_k]++;
		}
	}
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