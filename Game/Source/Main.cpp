#include "Engine.h"
#include "Player.h"
#include "Actor.h"
#include "Enemy.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>




using namespace std;

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	Font* font = new Font();
	font->Load("youmurdererbb_reg.ttf", 20);

	Text* text = new Text(font);
	text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		text->Draw(g_engine.GetRenderer(), 40, 40);

		g_engine.GetRenderer().EndFrame();

		
	}

	return 0;
}
/*

	// create audio system

	std::vector<FMOD::Sound*> sounds;

	AUDIO.AddSound("bass.wav");
	AUDIO.AddSound("snare.wav");
	AUDIO.AddSound("close-hat.wav");
	AUDIO.AddSound("open-hat.wav");
	AUDIO.AddSound("clap.wav");
	AUDIO.AddSound("cowbell.wav");


	std::vector<Particle> particles;
	float offset = 0;
	

	// make player 
	Model* model = new Model{ GameData::shipPoints, Color{ 100, 0, 0 } };
	Scene* scene = new Scene();

	Transform transform{ Vector2{ randomf(0, 800), randomf(0, 600)}, 0, randomf(1, 5) };
	Player* player = new Player(randomf(100, 100), transform, model);
	player->SetDamping(2.3f);
	player->SetTag("Player");
	scene->AddActor(player);

	auto* enemyModel = new Model{ GameData::shipPoints, Color{ 100, 230, 50 } };
	auto* enemy = new Enemy(110, Transform{ {g_engine.GetRenderer().GetWidth(), 10}, 0, 2}, enemyModel);
	enemy->SetDamping(1.0f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);

	float spawnTimer = 2;

	// main loop
	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		/*spawnTimer -= dt;
		if ()
		{
			scene->AddActor(enemy);
		}

		//transform.rotation = velocity.Angle();//rotation + time.GetDeltaTime();


		// UPDATE
		scene->Update(g_engine.GetTime().GetDeltaTime());
		//scene->Draw();
		Vector2 mousePosition = INPUT.GetMousePos();
		if (INPUT.GetMouseButDown(0) && !INPUT.GetPrevMouseButDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3) });// , (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(g_engine.GetTime().GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		// DRUM MACHINE
		if (INPUT.GetKeyDown(SDL_SCANCODE_E) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_E)) AUDIO.PlaySound("bass.wav");
		if (INPUT.GetKeyDown(SDL_SCANCODE_R) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_R)) AUDIO.PlaySound("snare.wav");
		if (INPUT.GetKeyDown(SDL_SCANCODE_T) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_T)) AUDIO.PlaySound("close-hat.wav");
		if (INPUT.GetKeyDown(SDL_SCANCODE_Y) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_Y)) AUDIO.PlaySound("open-hat.wav");
		if (INPUT.GetKeyDown(SDL_SCANCODE_Q) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_Q)) AUDIO.PlaySound("clap.wav");
		if (INPUT.GetKeyDown(SDL_SCANCODE_W) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_W)) AUDIO.PlaySound("cowbell.wav");

		// DRAW
		// clear screen
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		RENDERER.SetColor(255, 255, 255, 0);
		float radius = 5;
		offset += (90 * g_engine.GetTime().GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 60)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			//float x = Math::Cos(Math::DegToRad(angle + offset)) * (radius + angle);
			//float y = Math::Sin(Math::DegToRad(angle + offset)) * (radius + angle);

			RENDERER.SetColor(random(256), random(20), random(25), 0);
			//renderer.DrawRect(400 + x, 300 + y, 10.0f, 10.0f);
		}

		// draw particles
		RENDERER.SetColor(255, 20, 25, 0);
		for (Particle particle : particles)
		{
			particle.Draw(g_engine.GetRenderer());
		}

		RENDERER.SetColor(255, 20, 25, 0);
		scene->Draw(g_engine.GetRenderer());


		// show screen
		RENDERER.EndFrame();
	}

	return 0;
}
*/