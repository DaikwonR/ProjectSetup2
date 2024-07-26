#pragma once
#include "Actor.h"

class Audio;

class Player : public Actor
{
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}
	Player(Audio* audio) : m_audio(audio) {}

	void Update(float dt);
	virtual void OnCollision(Actor* actor);

	void SetFireModifier(float modifier) { m_fireModifier = modifier; }
	// void SetSuperModifier(Actor* actor);

	
	

private:
	float m_speed = 0;
	float m_firetimer = 0;
	float m_fireModifier = 1;

	Audio* m_audio{ nullptr };
};