#include "SuperPickup.h"
#include "Player.h"

void SuperPickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		dynamic_cast<Player*>(actor)->SetFireModifier(.001);
		m_destroyed = true;
	}
}
