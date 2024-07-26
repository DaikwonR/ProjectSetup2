#include "Particle.h"
#include "Renderer.h"

using namespace std;

void Particle::Initialize(const Data& data)
{
    isActive = true;
    position = data.position;
    velocity = data.velocity;
    lifespan = data.lifespan;
    r = data.r;
    g = data.g;
    b = data.b;
    a = data.a;
}

void Particle::Update(float dt)
{
    if (lifespan != 0.0f) lifespan -= dt;
    if (lifespan <= 0)
    {
        isActive = false;
    }

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
        renderer.DrawRect(position.x, position.y, 2.0f, 2.0f);
    }
}