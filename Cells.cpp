#include "Cells.h"
void Cells::initCells()
{
	////////////////// Emojis ///////////////////////////////
	this->Texture_Emoji.loadFromFile("MinesweeperSprite/Emoji.png");
	this->Sprite_Emoji.setTexture(this->Texture_Emoji);
	//this->EmojiVector.resize(4);
	this->Sprite_Emoji.setScale((240.0/92.0), (120.0/92.0));
	this->Sprite_Emoji.setPosition( 480, 1200);
	this->Sprite_Emoji.setTextureRect(sf::IntRect(128, 118, 92, 92));// Sun Glasses Emoji 0
	this->EmojiVector.push_back(this->Sprite_Emoji);
	this->Sprite_Emoji.setTextureRect(sf::IntRect(128, 228, 92, 92));// Smiley Emoji 1 
	this->EmojiVector.push_back(this->Sprite_Emoji);
	this->Sprite_Emoji.setTextureRect(sf::IntRect(128, 358, 92, 92));// Dead Emoji 2 
	this->EmojiVector.push_back(this->Sprite_Emoji);
	this->Sprite_Emoji.setTextureRect(sf::IntRect(128, 478, 92, 92));// // Shock Emoji 3
	this->EmojiVector.push_back(this->Sprite_Emoji);

	this->Sprite_Emoji.setTextureRect(sf::IntRect(128, 598, 92, 82));// // Background for Emoji
	this->Sprite_Emoji.setScale(1.304347826, 1.463414634); //
	for (uint16_t i = 0; i < Columns; i++)
	{
		this->Sprite_Emoji.setPosition( (i * 120), 1200);
		this->Emoji_Background.push_back(this->Sprite_Emoji);
	}
	//std::cout << "Width: " << this->EmojiVector[1].getGlobalBounds().width << ", Height: " << this->EmojiVector[1].getGlobalBounds().height << "\n";
	////////////////////////////////////////	


	//////////////////////////////////////////////////// Game Over Picture //////////////////////////////////
	this->Texture_GO.loadFromFile("MinesweeperSprite/GameOver.png");
	this->Sprite_GO.setTexture(this->Texture_GO);
	this->Sprite_GO.setTextureRect(sf::IntRect(158, 98, 400 - 158, 270 - 98)); // left, top, width, height..
	//242,172
	this->Sprite_GO.setScale(2, 2);
	this->Sprite_GO.setPosition(sf::Vector2f( 358, 528)); // center the Game Over
	// (1200 - (this->Sprite_GO.getScale().x * this->Sprite_GO.getTextureRect().width)) / 2
	// (1400 - (this->Sprite_GO.getScale().y * this->Sprite_GO.getTextureRect().height)) / 2)
	/////////////////////////////////////////////////////////////////// //////////////////////////////////////////
	this->count = 0; // experiment to for 1 - 9 number cells
	this->isLeftMouseClicked = false; // for opening cells
	this->isLeftMouseClicked_Restart = false;
	this->isRightMouseClicked = false; // for flagging
	this->isGameOver = false;

	///////////////////////////////////////////////////////////////////////////
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
	for (uint16_t i = 0; i < Rows; i++) // set it to unknown cells initialize
	{
		for (uint16_t k = 0; k < Columns; k++)
		{
			this->UnknownCellSprite.setPosition(sf::Vector2(k * this->UnknownCellSprite.getGlobalBounds().width
				, i * this->UnknownCellSprite.getGlobalBounds().height)); // width and height
			this->CellsVector[i][k] = this->UnknownCellSprite;
		}
	}
	/////////////////////////////////////////////////////////////////////
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
	this->NumberSprite.setScale(SetScale_Width, SetScale_Height); // Numbers
	for (uint16_t i = 0; i < 8; i++) // for numbers
	{
		this->NumberSprite.setTextureRect(sf::IntRect((76 + ((i) * 33)), 30, Width, Height));
		this->SpriteVector[i + 1] = this->NumberSprite; // 1 - 8
	}
	this->SpriteVector[9] = this->FlaggedSprite; // 9 
	this->SpriteVector[10] = this->BombCellSprite; // 10

}
void Cells::ifMouseInClicked(sf::RenderWindow& window) {
	// Get the mouse position relative to the window
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);


	// Check if the mouse is within the bounds of any cell
	if (!isGameOver)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //left clicked mouse
		{
			if (!this->isLeftMouseClicked)
			{
				//std::cout << "Clicked!\n"; 
				this->isLeftMouseClicked = true;
				for (uint16_t row = 0; row < Rows; row++)
				{
					for (uint16_t column = 0; column < Columns; column++)
					{
						sf::FloatRect cellBounds = this->CellsVector[row][column].getGlobalBounds();
						if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
						{
							if (this->CellsVector[row][column].getTextureRect() == this->FlaggedSprite.getTextureRect())
								return; // if flagged then it cannot be open
							std::cout << "Clicked: " << row << ":" << column << "\n";
							std::cout << "Map: " << this->tp.TileMapVector_Init[row][column] << "\n";

							if (this->tp.TileMapVector_Init[row][column] == 0)
							{
								//isCheckedEmpty.insert({ row, column });
								expandEmptyCells(row, column);
							}
							this->SpriteVector[this->tp.TileMapVector_Init[row][column]].setPosition(this->CellsVector[row][column].getPosition());
							this->CellsVector[row][column] = this->SpriteVector[tp.TileMapVector_Init[row][column]];
							if (this->tp.TileMapVector_Init[row][column] == 10)
							{
								this->isGameOver = true;
								//this->restart();

							}
							return;
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
				this->isRightMouseClicked = true;
				for (uint16_t row = 0; row < Rows; row++)
				{
					for (uint16_t column = 0; column < Columns; column++)
					{
						sf::FloatRect cellBounds = this->CellsVector[row][column].getGlobalBounds();
						if (cellBounds.contains(static_cast<sf::Vector2f>(mousePos)))
						{
							if (this->CellsVector[row][column].getTextureRect() != this->UnknownCellSprite.getTextureRect())
								return; // if not unkown cell then it cannot be flagged
							std::cout << "Clicked: " << row << ":" << column << "\n";

							this->FlaggedSprite.setPosition(this->CellsVector[row][column].getPosition());
							this->CellsVector[row][column] = this->FlaggedSprite;

							return;
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
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // right click mouse for flagging cells
		{
			if (!this->isLeftMouseClicked_Restart)
			{
				//std::cout << "Clicked!\n"; 
				this->isLeftMouseClicked_Restart = true;
				for (const auto& i : this->EmojiVector)
				{
					if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
					{
						this->restart();
						return;
					}
				}
			}
		}
		else
		{
			this->isLeftMouseClicked_Restart = false;
		}
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
	for (const auto& i : this->Emoji_Background) // draw emoji  background
	{
		window.draw(i);
	}
	//this->UnknownCellSprite.setPosition(0, 1200);
	//window.draw(this->UnknownCellSprite);
	if (isGameOver) // display Game Over 
	{
		window.draw(this->Sprite_GO);
		window.draw(this->EmojiVector[2]); // display dead emoji
	}
	else
	{
		window.draw(this->EmojiVector[1]);
	}
}