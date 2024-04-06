#pragma once
#include <vector>
constexpr unsigned char Columns = 10;
constexpr unsigned char Rows = 10;
constexpr unsigned char Height = 30; //for the image texture
constexpr unsigned char Width = 30; // for the image texture
constexpr unsigned char NumberCellsSprite = 11; // 0 (Empty Cell) , 1, 2, 3, 4, 5, 6, 7, 8, 9(Flagged) , 10(Bomb)
constexpr unsigned char NumberOfBombs = 15;
constexpr unsigned char SetScale_Width = 4;
constexpr unsigned char SetScale_Height = 4;
struct TileMaps
{
	std::vector<std::vector<uint16_t>> TileMapVector_Init // 10 = bomb, 0 = empty
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
};