#pragma once
#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include <SDL.h>

#include "Scene.h"
#include "SceneState.h"

// Scenes
#include "StartScene.h"
#include "PlayScene.h"
#include "EndScene.h"

class SceneManager
{
public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

	void init();

	// current scene functions
	void clean();
	void draw();
	void update();
	void handleEvents();

	// change scene
	void loadScene(const SceneState new_scene_state);

	Scene& getCurrentScene();
	SceneState getCurrentSceneState();

private:
	Scene* m_currentScene;
	SceneState m_currentSceneState;
};

#endif /* defined(__SCENE_MANAGER__) */