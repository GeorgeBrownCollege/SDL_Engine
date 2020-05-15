#include "EventManager.h"
#include <iostream>
#include "Game.h"

void EventManager::reset()
{
    m_isActive = false;
    SDL_Delay(300);
    m_isActive = true;
}

void EventManager::update()
{
	if(m_isActive)
	{
		SDL_Event event;
	    while (SDL_PollEvent(&event))
	    {
	        switch (event.type)
	        {
	        case SDL_QUIT:
	            TheGame::Instance()->quit();
	            break;

	        //case SDL_JOYAXISMOTION:
	        //    //onJoystickAxisMove(event);
	        //    break;

	        //case SDL_JOYBUTTONDOWN:
	        //    //onJoystickButtonDown(event);
	        //    break;

	        //case SDL_JOYBUTTONUP:
	        //    //onJoystickButtonUp(event);
	        //    break;

	        case SDL_MOUSEMOTION:
	            onMouseMove(event);
	            break;

	        case SDL_MOUSEBUTTONDOWN:
	            onMouseButtonDown(event);
	            break;

	        case SDL_MOUSEBUTTONUP:
	            onMouseButtonUp(event);
	            break;

	        case SDL_MOUSEWHEEL:
	            break;

	        case SDL_KEYDOWN:
	            onKeyDown();
	            break;

	        case SDL_KEYUP:
	            onKeyUp();
	            break;

	        default:
	            break;
	        }
	    }
    }
}

void EventManager::clean()
{
}

bool EventManager::isKeyDown(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool EventManager::isKeyUp(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void EventManager::onKeyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::onKeyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::onMouseMove(SDL_Event& event)
{
    m_mousePosition.x = event.motion.x;
    m_mousePosition.y = event.motion.y;
}

void EventManager::onMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[LEFT] = true;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[MIDDLE] = true;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[RIGHT] = true;
    }
}

void EventManager::onMouseButtonUp(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[LEFT] = false;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[MIDDLE] = false;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[RIGHT] = false;
    }
}

void EventManager::onMouseWheel(SDL_Event& event)
{
    m_mouseWheel = event.wheel.y;
}

bool EventManager::getMouseButton(const int button_number) const
{
    return m_mouseButtons[button_number];
}

glm::vec2 EventManager::getMousePosition() const
{
    return m_mousePosition;
}

int EventManager::getMouseWheel() const
{
    return m_mouseWheel;
}

EventManager::EventManager():
    m_keyStates(nullptr), m_mouseWheel(0), m_isActive(true)
{
	// initialize mouse position
    m_mousePosition = glm::vec2(0.0f, 0.0f);
	
    // initialize button states for the mouse
    for (auto& mouseButtonState : m_mouseButtons)
    {
	    mouseButtonState = false;
    }
}

EventManager::~EventManager()
= default;
