#include "GameData.h"

namespace GameData
{
	const std::vector<Vector2> shipPoints
	{
		{ 25, 0 },
		{ -5, -25 },
		{ 0, 5 },
		{ 0, -5 },
		{ -5, 25 },
		{ 25, 0 }
	};
	const std::vector<Vector2> bulletPoints
	{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 }
	};
}