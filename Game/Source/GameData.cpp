#include "GameData.h"

namespace GameData
{
	const std::vector<Vector2> shipPoints
	{
		{ 25, 0 },
		{ -20, -25 },
		{ 0, 5 },
		{ 0, -5 },
		{ -20, 25 },
		{ 25, 0 }
	};
	const std::vector<Vector2> bulletPoints
	{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 }
	};
	const std::vector<Vector2> blockPoints
	{
		{ -30, -30 },
		{ -30, 30 },
		{ 30, 30 },
		{ 30, -30 },
		{ -30, -30 }
	};
	const std::vector<Vector2> superPoints
	{
		{ -50, 0 },
		{ -15, 14 },
		{ -15, 47 },
		{ 7, 23 },
		{ 40, 29 },
		{ 25, 0 },
		{ 40, -29 },
		{ 7, -23 },
		{ -15, -47 },
		{ -15, -14 },
		{ -50, 0 }
	};
	const std::vector<Vector2> superDuperPoints
	{
		{ -25, 0 },
		{ -7, 14 },
		{ -7, 23 },
		{ 3, 12 },
		{ 20, 15 },
		{ 13, 0 },
		{ 20, -15 },
		{ 3, -12 },
		{ -7, -23 },
		{ -7, -14 },
		{ -25, 0 }
	};
	/*const std::vector<Vector2> bananaPoints
	{
		{ 10, 0 },
		{ 10, 10 },
		{ 6, 10 },
		{ 6, 8 },
		{ 6, 8 },
		{ 8, 2 },
		{ 6, 2 },
		{ 6, 0 }
	};*/
}