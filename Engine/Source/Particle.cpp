#include "Particle.h"
#include "Renderer.h"

using namespace std;

void Particle::Update(float dt)
{
    position = position + (velocity * dt);
}

void Particle::Draw(Renderer renderer)
{
    renderer.DrawPoint(position.x, position.y);
}