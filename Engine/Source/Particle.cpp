#include "Particle.h"
#include "Renderer.h"

using namespace std;

void Particle::Update(float dt)
{
    if (lifespan != 0.0f) lifespan -= dt;
    position = position + (velocity * dt);
}

void Particle::Draw(Renderer renderer)
{
    if (lifespan >= 0)
    {
        uint8_t r = rand() % 255 + 1;
        uint8_t g = rand() % 255 + 1;
        uint8_t b = rand() % 255 + 1;
        uint8_t a = rand() % 255 + 1;
        renderer.SetColor(r, g, b, a);
        renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
    }
}