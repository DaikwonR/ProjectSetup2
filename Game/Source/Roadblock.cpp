#include "Roadblock.h"
#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "Game.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Audio.h"
#include "Enemy.h"

#include <fmod.h>
#include <iostream>
#include <vector>


void Roadblock::Update(float dt)
{
	m_firetimer -= dt;
	if (INPUT.GetMouseButDown(0) && m_firetimer <= 0) // && !INPUT.GetKeyDown(SDL_SCANCODE_SPACE))
	{
		if(m_scene->GetGame()->GetLives() != 1) return;

		m_firetimer = 0.2f * m_fireModifier;

		// shoot at mouse position
		Vector2 direction = g_engine.GetInput().GetMousePos() - m_transform.position;
		float angle = direction.Angle();

		std::vector<Vector2> points;

		// actor
		Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 1 } };
		Transform transform{ m_transform.position, angle, 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifeSpan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(std::move(bullet));


		AUDIO.PlaySound("skadoosh.wav");


		
	}

	Actor::Update(dt);
}

void Roadblock::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		Vector2 direction = actor->GetTransform().position - m_transform.position;
		Vector2 offset = direction.Normalized() * (GetRadius());// +actor->GetRadius());

		actor->GetTransform().position = m_transform.position + offset;
	}

	
	
	//if (actor->GetTag() == "Player" && m_transform.position.x + actor->GetRadius() == m_transform.position.x + this->GetRadius())
	//{
	//	m_transform.position.x - m_roadblock->position.x + this->GetRadius();
	//}
	//if (actor->GetTag() == "Player" && m_transform.position.y + actor->GetRadius() == m_roadblock->position.y + this->GetRadius())
	//{
	//	m_transform.position.y - m_roadblock->position.y + this->GetRadius();
	//}
}
