#include "Cells.h"
void Cells::CalculationsBombNumbers()
{
	// o o o
	// o B o
	// o o o
	// Blocks anatomy up

	// experimentation for knowing how many bombs
	this->count = 1;
	for (uint16_t i = 0; i < Rows; i++)
	{

		for (uint16_t k = 0; k < Columns; k++)
		{
			if (this->tp.TileMapVector_Init[i][k] != 10) // empty or if it is 0 - 7 which are not bombs
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
				else if ((i == Rows - 1) && ((k != 0 && k != Columns - 1))) // very bottom 
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
	this->count = 0;
	printTileMap_of_Bomb();
}
void Cells::printTileMap_of_Bomb()
{
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
			//std::cout << this->count << ".Check i : " << Check_i << ", Check K: " << Check_k << "\n";
			tp.TileMapVector_Init[Check_i][Check_k]++;
			this->count++;
		}
	}
}

void Cells::RandomizeBombs()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::set<std::pair<int, int>> StoreIndexes;
	// Define a distribution
	std::uniform_int_distribution<> ColumnRandom(0, Columns - 1); // index, from 0 to ColumnsNumber - 1
	std::uniform_int_distribution<> RowRandom(0, Rows - 1); // index, from 0 to RowsNumbers - 1
	while (StoreIndexes.size() < NumberOfBombs) 
	{
		uint16_t RowIndex = RowRandom(gen); 
		uint16_t ColumnIndex = ColumnRandom(gen);
		//std::cout << "Not True Row: " << RowIndex << ", Column: " << ColumnIndex << "\n";
		StoreIndexes.insert({ RowIndex, ColumnIndex });  // set does not allow duplication
		//std::cout << "Size of Set: " << StoreIndexes.size() << "\n";
	}
	// StoreIndexes.insert({ 1,1 });
	// StoreIndexes.insert({ 1,1 });
	//this->count = 1;
	for (const auto& [Row, Column] : StoreIndexes)
	{
		tp.TileMapVector_Init[Row][Column] = 10;
		//std::cout << this->count << ". True set: " << Row << ", " << Column << "\n";
		//this->count++;
	}
	//this->count = 0;
}
// not done yet, still experimenting
/// i think i should use , map<pair<int,int>, bool> , because set is not that efficient i guess
// need to further enhanced or optimized
void Cells::expandEmptyCells(const uint16_t& i,const uint16_t& k, std::set<std::pair<int,int>>& isCheckedEmpty)
{
	// Check if the cell has already been visited
	if (isCheckedEmpty.find({ i, k }) != isCheckedEmpty.end()) 
	{
		return;
	}
	isCheckedEmpty.insert({ i, k }); // if not yet visited then mark it as visited as of now 
	this->SpriteVector[this->tp.TileMapVector_Init[i][k]].setPosition(this->CellsVector[i][k].getPosition());
	this->CellsVector[i][k] = this->SpriteVector[tp.TileMapVector_Init[i][k]];
	if (this->tp.TileMapVector_Init[i][k] != 0 ) // if not empty
	{
		return;
	}
		if ((i != 0 && i != Rows - 1) && (k != 0 && k != Columns - 1)) // if it is in 8 blocks check , not in beginning
			// not in the very right or very left and not in last
		{
			for (uint16_t l = 0; l < 3; l++)
			{
				uint16_t Check_i = i - 1 + l;
				for (uint16_t p = 0; p < 3; p++)
				{
					uint16_t Check_k = k - 1 + p;
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue; // check if this Check_i and Check_k is already exists in the set
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
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
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
				}
			}
		}
		else if ((i == Rows - 1) && ((k != 0 && k != Columns - 1))) // very bottom 
		{
			for (uint16_t l = 0; l < 2; l++)
			{
				uint16_t Check_i = i - 1 + l;
				for (uint16_t p = 0; p < 3; p++)
				{
					uint16_t Check_k = k - 1 + p;
					/*if ((k == Check_k && i == Check_i) && isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;*/
					if ((k == Check_k && i == Check_i))
						continue;
					if (isCheckedEmpty.find({ Check_i, Check_k }) != isCheckedEmpty.end())
						continue;
					expandEmptyCells(Check_i, Check_k, isCheckedEmpty);
				}
			}
		}
	
}