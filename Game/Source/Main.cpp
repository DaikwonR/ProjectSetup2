#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Vector2.h"
#include "Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Enging", 800, 600);

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	vector<Vector2> points;
	for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}

	while (true)
	{

		// input
		// update
		//draw

		// UPDATE
		Vector2 speed = { 0.1f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.002f;
		}



		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//// draw line
		renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		renderer.DrawLine(100, 500, 300, 300);
		renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		renderer.DrawLine(100, 500, 500, 500);
		renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		renderer.DrawLine(300, 300, 500, 500);

		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		for (int i = 0; i < rand() % 10'000 + 1; i++)
		{
			renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
			int x1 = rand() % 1000 + 1;
			int y1 = rand() % 1000 + 1;
			int x2 = rand() % 1000 + 1;
			int y2 = rand() % 1000 + 1;

			renderer.DrawLine(x1, y1, x2, y2);
		}

		// show screen
		renderer.EndFrame();

		SDL_Delay(10);
	}

	return 0;
}