#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "Vector2.h"
#include "Renderer.h"
#include "Input.h"
#include "Particle.h"
#include "E_Time.h"

using namespace std;

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.ShutDown();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	vector<Vector2> points;
	vector<Particle> particles;
	/*for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}*/
	bool quit = false;

	while (true)
	{
		time.Tick();
		// input
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// update
		// draw

		// UPDATE
		Vector2 mouse = input.GetMousePos();
		cout << mouse.x << "" << mouse.y << endl;


		if (input.GetMouseButDown(0) && !input.GetPrevMouseButDown(0))
		{
			cout << "Mouse Pressed\n";
			points.push_back(mouse);
		}

		if (input.GetMouseButDown(0) && input.GetPrevMouseButDown(0))
		{
			float distance = (points.back() - mouse).length();
			if (distance > 5)
			{
				points.push_back(mouse);
			}
		}

		if (input.GetMouseButDown(0))
		{
			particles.push_back(Particle{ mouse, {rand() % (-100, 100), rand() % (-100,100)} });
		}

		for (Particle& particle : particles)
		{

			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;

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

		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		/*for (int i = 0; i < rand() % 10'000 + 1; i++)
		{
			renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
			int x1 = rand() % 1000 + 1;
			int y1 = rand() % 1000 + 1;
			int x2 = rand() % 1000 + 1;
			int y2 = rand() % 1000 + 1;

			renderer.DrawLine(x1, y1, x2, y2);
		}*/

		// show screen
		renderer.EndFrame();

		SDL_Delay(10);
	}

	return 0;
}