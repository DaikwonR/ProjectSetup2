#pragma once
#include <chrono>
#ifndef TIME_H
#define TIME_H

using namespace std;

class Time
{
private:
    using clock = chrono::high_resolution_clock;
public:
    Time() :
        m_startTime{ clock::now() },
        m_frameTime{ clock::now() }
    {}

    void Tick();
    void Reset() { m_startTime = clock::now(); }

    float GetTime() { return m_time; }
    float GetDeltaTime() const { return m_deltaTime; }


private:
    float m_time{ 0 };
    float m_deltaTime{ 0 };

    clock::time_point m_startTime;
    clock::time_point m_frameTime;


};

#endif TIME_H