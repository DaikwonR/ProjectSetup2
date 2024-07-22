#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"

#include <iostream>

using namespace std;

void Player::Update(float dt)
{
	// movement
	Vector2 direction{ 0, 0 };
	if (INPUT.GetKeyDown(SDL_SCANCODE_W))		direction.x = 1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_S))	direction.x = -1;
	
	if (INPUT.GetKeyDown(SDL_SCANCODE_Q))		direction.y = -1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_E))	direction.y = 1;

	if (INPUT.GetKeyDown(SDL_SCANCODE_A))	m_transform.rotation -= Math::DegToRad(100) * dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_D))	m_transform.rotation += Math::DegToRad(100) * dt;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)RENDERER.GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)RENDERER.GetHeight());


	// fire
	m_firetimer -= dt;
	if (INPUT.GetMouseButDown(0) && m_firetimer <= 0) // && !INPUT.GetKeyDown(SDL_SCANCODE_SPACE))
	{
		m_firetimer = 0.2f * m_fireModifier;

		// shoot at mouse position
		Vector2 direction = g_engine.GetInput().GetMousePos() - m_transform.position;
		float angle = direction.Angle();


		std::vector<Vector2> points;

		// actor
		Model* model = new Model{ GameData::shipPoints, Color{ 1, 1, 1 } };
		Transform transform{ m_transform.position, angle, 1.0f };

		Bullet* bullet = new Bullet(400.0f, transform, model);
		bullet->SetLifeSpan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(bullet);
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
}
