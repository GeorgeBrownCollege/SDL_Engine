#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	drawDisplayList();
}

void EndScene::update()
{
	updateDisplayList();
}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void EndScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("END SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pRestartButton->setActive(false);
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->setAlpha(128);
	});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->setAlpha(255);
	});

	addChild(m_pRestartButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}
