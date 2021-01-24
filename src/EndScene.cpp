#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

EndScene::EndScene()
{
	EndScene::Start();
}

EndScene::~EndScene()
= default;

void EndScene::Draw()
{
	DrawDisplayList();
}

void EndScene::Update()
{
	UpdateDisplayList();
}

void EndScene::Clean()
{
	RemoveAllChildren();
}

void EndScene::HandleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->Update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void EndScene::Start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("END SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_label->SetParent(this);
	AddChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->GetTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->AddEventListener(CLICK, [&]()-> void
	{
		m_pRestartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pRestartButton->AddEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->setAlpha(128);
	});

	m_pRestartButton->AddEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->setAlpha(255);
	});

	AddChild(m_pRestartButton);
}
