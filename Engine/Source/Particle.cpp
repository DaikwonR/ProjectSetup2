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

    uint8_t r = rand() % 255 + 1;
    uint8_t g = rand() % 255 + 1;
    uint8_t b = rand() % 255 + 1;
    uint8_t a = rand() % 255 + 1;
    renderer.SetColor(r, g, b, a);
}