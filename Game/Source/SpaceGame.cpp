#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"
#include "Pickup.h"
#include "Roadblock.h"
#include "SuperPickup.h"

#include <cstdlib>

bool SpaceGame::Initialize()
{
	m_scene = new Scene(this);


	m_font = new Font();
	m_font->Load("youmurdererbb_reg.ttf", 20);

	m_fontLarge = new Font();
	m_fontLarge->Load("youmurdererbb_reg.ttf", 70);

	m_textScore = new Text(m_font);
	m_textLives = new Text(m_font);
	m_textTitle = new Text(m_fontLarge);

	AUDIO.AddSound("monkey.wav");
	AUDIO.AddSound("jazz.wav");
	// AUDIO.AddSound("scream.wav");

	return true;
}

bool SpaceGame::Shutdown()
{
	return false;
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case State::TITLE:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = State::START_GAME;
			AUDIO.PlaySound("jazz.wav");
		}
		
		break;
	case State::START_GAME:
		m_score = 0;
		m_lives = 3;

		m_state = State::START_LEVEL;
		
		break;
	case State::START_LEVEL:
		

		m_scene->RemoveAll();
		{
			Transform transform{ Vector2{ randomf(0, 800), randomf(0, 600)}, 0, randomf(1, 5) };
			Model* model = new Model{ GameData::shipPoints, Color{ 100, 0, 0 } };
			auto player = std::make_unique<Player>(randomf(1000, 1000), transform, model);
			player->SetDamping(2.3f);
			player->SetTag("Player");
			m_scene->AddActor(std::move(player));
			m_roadBlockCount = 0;
		}

		m_spawnTime = 3;
		m_spawnTimer = m_spawnTime;
		// roadBlockSpawner();

		m_state = State::GAME;

		break;
	case State::GAME:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTime -= 0.2f;
			m_spawnTimer = m_spawnTime;

			// create enemy
			auto* enemyModel = new Model{ GameData::shipPoints, Color{100, 230, 50  } };
			auto enemy = std::make_unique<Enemy>(110.0f, Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetWidth())}, 0, 2 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));
			AUDIO.PlaySound("monkey.wav");

			// create pickup
			auto* pickupModel = new Model{ GameData::superPoints, Color{ rand() % 255, rand() % 255, rand() % 255} };
			auto pickup = std::make_unique<Pickup>(Transform{ {random(g_engine.GetRenderer().GetWidth()),random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, pickupModel);
			pickup->SetTag("Pickup");
			m_scene->AddActor(std::move(pickup));

			// create roadblock
			roadBlockSpawner();
			// OnPlayerLastLife();
		}
		break;
	case State::DEAD:
		// AUDIO.PlaySound("scream.wav");
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) { m_state = State::START_LEVEL; }

		break;
	case State::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) { m_state = State::TITLE; }

		break;
	default:
		break;
	}


	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case SpaceGame::State::TITLE:
		// draw text "Game Title"
		m_textTitle->Create(renderer, "Monkey Business! :) ", Color{ 1, 0, 0, 1 });
		m_textTitle->Draw(renderer, 260, 300);
		break;
	case SpaceGame::State::GAME_OVER:
		// draw text "Game Over"
		m_textTitle->Create(renderer, "Monkey Business? :( ", Color{ 1, 0, 0, 1 });
		m_textTitle->Draw(renderer, 260, 300);
		break;
	default:
		break;
	}

	// draw score
	std::string text = "Score " + std::to_string(m_score);
	m_textScore->Create(renderer, text, { 1, 0, 0, 1 });
	m_textScore->Draw(renderer, 20, 20);
	// draw lives
	text = "Lives " + std::to_string(m_lives);
	m_textLives->Create(renderer, text, { 1, 0, 0, 1 });
	m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);
	m_scene->Draw(renderer);
}

void SpaceGame::roadBlockSpawner()
{
	m_roadBlockCount++;
	if (m_roadBlockCount <= 3)
	{
		auto* roadblockModel = new Model{ GameData::blockPoints, Color{  rand() % 255, 230, 10, 255} };
		auto roadblock = std::make_unique<Roadblock>(Transform{ {random(g_engine.GetRenderer().GetWidth()),random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, roadblockModel);
		roadblock->SetTag("Roadblock");
		m_scene->AddActor(std::move(roadblock));

	}
	else
	{
		// m_scene->RemoveActor(std::move(roadblock));

		return;
	}
}
void SpaceGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0) ? State::GAME_OVER : State::DEAD;
	m_stateTimer = 3;
}

void SpaceGame::OnPlayerLastLife()
{
	Roadblock roadblock;
	m_scene->RemoveAll();
	
	if (m_lives == 1)
	{
		
		roadblock.Update(1.0f);
		
		auto* enemyModel = new Model{ GameData::superDuperPoints, Color{100, 230, 50  } };
		auto enemy = std::make_unique<Enemy>(110.0f, Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetWidth())}, 0, 2 }, enemyModel);
		enemy->SetDamping(1.0f);
		enemy->SetTag("Enemy");
		m_scene->AddActor(std::move(enemy));
		AUDIO.PlaySound("monkey.wav");
	}
}

