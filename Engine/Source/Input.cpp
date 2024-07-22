#include "Input.h"
#include <SDL.h>

using namespace std;

bool Input::Initialize()
{
    int numbKeys;
    const uint8_t* keyboardState = SDL_GetKeyboardState(&numbKeys);
    m_keyState.resize(numbKeys);
    //copy current keyboard state into out keyboard state
    copy(keyboardState, keyboardState + numbKeys, m_keyState.begin());

    m_prevKeyState = m_keyState;

    return true;
}

void Input::ShutDown()
{

}

void Input::Update()
{

    //key input
    m_prevKeyState = m_keyState;
    const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
    copy(keyboardState, keyboardState + m_keyState.size(), m_keyState.begin());


    //mouse input
    int x, y;
    uint32_t buttonState = SDL_GetMouseState(&x, &y);
    m_mousePos.x = (float)x;
    m_mousePos.y = (float)y;

    m_prevMouseButtonState = m_mouseButtonState;

    //000 <- Button State
    //001 <- button mask
    //000 - if there is a 0, it is false
    m_mouseButtonState[0] = buttonState & SDL_BUTTON_LMASK;
    m_mouseButtonState[1] = buttonState & SDL_BUTTON_MMASK;

    m_mouseButtonState[2] = buttonState & SDL_BUTTON_RMASK;
}