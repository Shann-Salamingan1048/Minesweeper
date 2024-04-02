#pragma once
#include <vector>
constexpr unsigned char Columns = 10;
constexpr unsigned char Rows = 10;
constexpr unsigned char Height = 30; //for the image texture
constexpr unsigned char Width = 30; // for the image texture
constexpr unsigned char Number_ofNumberCellsSprite = 8;
constexpr unsigned char NumberOfBombs = 20;
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