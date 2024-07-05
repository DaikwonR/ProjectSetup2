#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include "Vector2.h"

using namespace std;

struct Particle {
    Vector2 position{ 0,0 };
    Vector2 velocity{ 0,0 };
    float lifespan = 1'000;

    Particle() = default;
    Particle(Vector2 postion, Vector2 velocity) :
        position{ position },
        velocity{ velocity }
    {}
    void Update(float dt);
    void Draw(Renderer renderer);
    Vector2 getPosition(){ return position; }
};