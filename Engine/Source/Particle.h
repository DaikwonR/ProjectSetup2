#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include "Vector2.h"

using namespace std;

struct Particle 
{
    struct Data
    {
        Vector2 position{ 0,0 };
        Vector2 velocity{ 0,0 };
        float lifespan = 0;
        uint8_t r{255}, g{255}, b{255}, a{0};
    };


    Vector2 position{ 0,0 };
    Vector2 velocity{ 0,0 };
    float lifespan = 0;
    uint8_t r{ 255 }, g{ 255 }, b{ 255 }, a{ 0 };

    bool isActive{ false };

    Particle() = default;
    Particle(Vector2 position, Vector2 velocity) :
        position{ position },
        velocity{ velocity }
    {}
    Particle(Vector2 position, Vector2 velocity, float lifespan) :
        position{ position },
        velocity{ velocity },
        lifespan{ lifespan }
    {}

    void Initialize(const Data& data);
    void Update(float dt);
    void Draw(Renderer renderer);
    Vector2 getPosition(){ return position; }
};