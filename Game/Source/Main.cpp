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
#include "Transform.h"
#include "Model.h"
#include "Color.h"

using namespace std;

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
	//audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	std::vector<Particle> particles;
	float offset = 5;


	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -20, -20 });
	points.push_back(Vector2{ -5, 25 });
	points.push_back(Vector2{ 5, 0 });
	
	points.push_back(Vector2{ 0, 5 });
	points.push_back(Vector2{ 25, 5 });
	points.push_back(Vector2{ -20, -20 });
	points.push_back(Vector2{ 0, 5 });

	Model model{ points, Color{ 100, 0, 0 } };
	Transform transform{ { renderer.GetWidth() >> 1, renderer.GetHeight() >> 1 }, 0, 5 };

	// 0001 = 1
	// 0010 = 2
	// 0100 = 4
	// 1000 = 8
	// >> 1

	// main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();

		// INPUT
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_UP))		thrust = -51;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN))	thrust = -51;

		if (input.GetKeyDown(SDL_SCANCODE_LEFT))	transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT))	transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.GetHeight());

		//transform.rotation = velocity.Angle();//rotation + time.GetDeltaTime();


		// UPDATE
		Vector2 mousePosition = input.GetMousePos();
		if (input.GetMouseButDown(0) && !input.GetPrevMouseButDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3) });// , (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		// DRUM MACHINE
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPrevKeyDown(SDL_SCANCODE_E)) audio->playSound(sounds[2], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPrevKeyDown(SDL_SCANCODE_R)) audio->playSound(sounds[3], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPrevKeyDown(SDL_SCANCODE_T)) audio->playSound(sounds[4], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPrevKeyDown(SDL_SCANCODE_Y)) audio->playSound(sounds[5], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPrevKeyDown(SDL_SCANCODE_Q)) audio->playSound(sounds[0], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPrevKeyDown(SDL_SCANCODE_W)) audio->playSound(sounds[1], 0, false, nullptr);

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);
		float radius = 5;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 60)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			//float x = Math::Cos(Math::DegToRad(angle + offset)) * (radius + angle);
			//float y = Math::Sin(Math::DegToRad(angle + offset)) * (radius + angle);

			renderer.SetColor(random(256), random(20), random(25), 0);
			//renderer.DrawRect(400 + x, 300 + y, 10.0f, 10.0f);
		}

		// draw particles
		renderer.SetColor(255, 20, 25, 0);
		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		renderer.SetColor(255, 20, 25, 0);
		model.Draw(renderer, transform);


		// show screen
		renderer.EndFrame();
	}

	return 0;
}
