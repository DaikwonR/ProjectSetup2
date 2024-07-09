#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fmod.hpp>

#include "Vector2.h"
#include "Renderer.h"
#include "Input.h"
#include "Particle.h"
#include "E_Time.h"
#include "MathUtils.h"
#include "Random.h"

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
	vector<FMOD::Sound*> sounds;
	float offset = 0;
	bool quit = false;

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
	audio->playSound(sound, 0, false, nullptr);

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);


	while (true)
	{
		
		time.Tick();
		// input
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// play sounds
		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPrevKeyDown(SDL_SCANCODE_Q))
		{
			audio->playSound(sounds[0], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPrevKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[1], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPrevKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[2], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPrevKeyDown(SDL_SCANCODE_R))
		{
			audio->playSound(sounds[3], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPrevKeyDown(SDL_SCANCODE_T))
		{
			audio->playSound(sounds[4], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPrevKeyDown(SDL_SCANCODE_Y))
		{
			audio->playSound(sounds[5], 0, false, nullptr);
		}



		// UPDATE
		Vector2 mouse = input.GetMousePos();
		cout << mouse.x << " " << mouse.y << endl;


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

		//Vector2 mousePosition = input.GetMousePos();
		if (input.GetMouseButDown(0) && !input.GetPrevMouseButDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mouse, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3) });// , (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0 });
			}
		}

		for (Particle& particle : particles)
		{

			particle.Update(time.GetDeltaTime());

			//if (particle.position.x > 800) particle.position.x = 0;
			//if (particle.position.x < 0) particle.position.x = 800;

		}



		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		float radius = 200;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * .05f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * .05f) * radius;

			renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}

		//// draw line
		//renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		//renderer.DrawLine(100, 500, 300, 300);
		//renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		//renderer.DrawLine(100, 500, 500, 500);
		//renderer.SetColor(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 10 + 1);
		//renderer.DrawLine(300, 300, 500, 500);

		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		/*for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}*/

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

		
		audio->update();
		// show screen
		renderer.EndFrame();

		SDL_Delay(10);
	}

	return 0;
}