#pragma once
#ifndef __GAME__
#define __GAME__

// Core Libraries
#include <iostream>
#include <string>
#include <vector>
#include "SceneState.h"

#include <SDL.h>

// Game Managers
#include "CollisionManager.h"

// Scenes
#include "StartScene.h"
#include "PlayScene.h"
#include "EndScene.h"

#include "Config.h"

class Game
{
public:
	
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}

	// simply set the isRunning variable to true
	void init();
	bool init(const char* title, int x, int y, int width, int height, bool fullscreen);

	// public life cycle functions
	void render() const;
	void update() const;
	void handleEvents();
	void clean() const;
	void start();
	void quit();

	// getter and setter functions
	glm::vec2 getMousePosition() const;
	void setFrames(Uint32 frames);
	Uint32 getFrames() const;
	bool isRunning() const;
	void changeSceneState(SceneState new_state);
	
private:
	Game();
	~Game();

	// game properties
	bool m_bRunning;
	Uint32 m_frames;
	glm::vec2 m_mousePosition;

	// scene variables
	Scene* m_currentScene;
	SceneState m_currentSceneState;

	// storage structures
	std::shared_ptr<SDL_Window> m_pWindow;
	static Game* s_pInstance;
};

typedef Game TheGame;

#endif /* defined (__GAME__) */

