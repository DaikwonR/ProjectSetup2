#pragma once
#include "Actor.h"

class SuperPickup : public Actor
{
public:
	SuperPickup() = default;
	SuperPickup(const Transform& transform) : Actor{ transform } {}
	SuperPickup(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	// Inherited via Actor
	void OnCollision(Actor* actor) override;

protected:

};