#pragma once
#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include "SDL.h"
#include <vector>
#include "glm/vec2.hpp"
#include "MouseButtons.h"
#include "GameController.h"
#include "imgui.h"

/* singleton with magic static */
class EventManager
{
public:
	static EventManager& Instance()
	{
		static EventManager instance;
		return instance;
	}

	void Reset();

	// update and clean the input handler
	void Update();
	void Clean();

	// keyboard events
	[[nodiscard]] bool IsKeyDown(SDL_Scancode key) const;
	[[nodiscard]] bool IsKeyUp(SDL_Scancode key) const;

	// one-shot keyboard events
	bool KeyPressed(const SDL_Scancode c) const;
	bool KeyReleased(const SDL_Scancode c) const;

	// mouse events
	[[nodiscard]] bool GetMouseButton(int button_number) const;
	[[nodiscard]] glm::vec2 GetMousePosition() const;
	[[nodiscard]] int GetMouseWheel() const;

	[[nodiscard]] bool MousePressed(const int b) const;
	[[nodiscard]] bool MouseReleased(const int b) const;

	// gamecontroller events
	[[nodiscard]] GameController* GetGameController(int controller_number) const;

	//IMGUI
	[[nodiscard]] bool IsIMGUIActive() const;

	// window focus
	[[nodiscard]] bool IsMainWindowInFocus() const;

private:
	// Hide Constructor and Destructor 
	EventManager();
	~EventManager();
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	/*------- PRIVATE MEMBER FUNCTIONS -------*/

	// handle keyboard events
	void OnKeyDown();
	void OnKeyUp();

	// handle mouse events
	void OnMouseMove(const SDL_Event& event);
	void OnMouseButtonDown(const SDL_Event& event);
	void OnMouseButtonUp(const SDL_Event& event);
	void OnMouseWheel(const SDL_Event& event);

	// game controller functions
	void InitializeControllers();

	// IMGUI IO
	void IMGUIKeymap() const;

	/*------- PRIVATE MEMBER VARIABLES -------*/

	// IMGUI variables
	ImGuiIO& m_io;
	bool m_isIMGUIActive;

	// keyboard states array
	const Uint8* m_keyStates;

	// keyboard state containers
	const Uint8* m_keysCurr;
	Uint8* m_keysLast;
	int m_numKeys{};

	// mouse specific
	bool m_mouseButtons[3]{};
	glm::vec2 m_mousePosition;
	int m_mouseWheel;

	// mouse state containers
	Uint32 m_mouseCurrent;
	Uint32 m_mouseLast;

	// GameControllers
	std::vector<GameController*> m_pGameControllers;

	// is the Event Manager active
	bool m_isActive;

	// does the main window have focus
	bool m_mainWindowHasFocus;
};

#endif /* defined (__EVENT_MANAGER__) */
