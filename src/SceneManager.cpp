#include "SceneManager.h"
#include <iostream>
#include "Game.h"

void SceneManager::init()
{
	m_currentScene = nullptr;
	m_currentSceneState = SceneState::NO_SCENE;
}

void SceneManager::clean()
{
	m_currentScene->clean();
}

void SceneManager::draw()
{
	m_currentScene->draw();
}

void SceneManager::update()
{
	m_currentScene->update();
}

void SceneManager::handleEvents()
{
	m_currentScene->handleEvents();
}

Scene& SceneManager::getCurrentScene()
{
	return *m_currentScene;
}

SceneState SceneManager::getCurrentSceneState()
{
	return m_currentSceneState;
}

void SceneManager::loadScene(SceneState new_state)
{
	m_currentScene = nullptr;
	m_currentSceneState = new_state;

	switch (m_currentSceneState)
	{
	case START_SCENE:
		m_currentScene = new StartScene();
		std::cout << "start scene activated" << std::endl;
		break;
	case PLAY_SCENE:
		m_currentScene = new PlayScene();
		std::cout << "play scene activated" << std::endl;
		break;
	case END_SCENE:
		m_currentScene = new EndScene();
		std::cout << "end scene activated" << std::endl;
		break;
	default:
		std::cout << "default case activated" << std::endl;
		break;
	}
}
