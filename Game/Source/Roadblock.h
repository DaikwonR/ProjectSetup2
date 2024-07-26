#pragma once
#include "Actor.h"

class Player;

class Roadblock : public Actor
{
public:
	Roadblock() = default;
	Roadblock(const Transform& transform) : Actor{ transform } {}
	Roadblock(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Roadblock(const Vector2& size, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_size{ size }
	{}

	// Inherited via Actor
	void Update(float dt);
	void OnCollision(Actor* actor) override;
	
	
	//const int m_roadBlockCount = 3;
protected:
	float m_speed = 0;
	float m_firetimer = 0;
	float m_fireModifier = 1;

	
	Vector2 m_size{ 0, 0 };
	//Transform* m_roadblock{ nullptr };

};