#pragma once
#include <vector>
#include <array>
#include "Vector2.h"

using namespace std;

class Input {
public:
    Input() = default;
    ~Input() = default;

    bool Initialize();
    void ShutDown();

    void Update();

    bool GetKeyDown(uint8_t key) { return m_keyState[key]; }
    bool GetPrevKeyDown(uint8_t key) { return m_prevKeyState[key]; }


    Vector2 GetMousePos() { return m_mousePos; }
    bool GetMouseButDown(uint8_t button) { return m_mouseButtonState[button]; }
    bool GetPrevMouseButDown(uint8_t button) { return m_prevMouseButtonState[button]; }

private:
    vector<uint8_t> m_keyState;
    vector<uint8_t> m_prevKeyState;

    Vector2 m_mousePos{ 0,0 };
    array<uint8_t, 3> m_mouseButtonState{ 0, 0, 0 };
    array<uint8_t, 3> m_prevMouseButtonState{ 0, 0, 0 };
};