#pragma once
#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include "SDL.h"
#include <vector>
#include "glm/vec2.hpp"
#include "MouseButtons.h"

/* singleton with magic static */
class EventManager
{
public:
	static EventManager& Instance()
	{
		static EventManager instance;
		return instance;
	}

	void reset();

	// update and clean the input handler
	void update();
	void clean();

	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;
	bool isKeyUp(SDL_Scancode key) const;

	// mouse events
	bool getMouseButton(int button_number) const;
	glm::vec2 getMousePosition() const;
	int getMouseWheel() const;
	
private:
	// Hide Constructor and Destructor 
	EventManager();
	~EventManager();
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	/*------- PRIVATE MEMBER FUNCTIONS -------*/
	
	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onMouseWheel(SDL_Event& event);

	/*------- PRIVATE MEMBER VARIABLES -------*/
	
	// keyboard states array
	const Uint8* m_keyStates;

	// mouse specific
	bool m_mouseButtons[3];
	glm::vec2 m_mousePosition;
	int m_mouseWheel;


	bool m_isActive;

};


#endif /* defined (__EVENT_MANAGER__) */
