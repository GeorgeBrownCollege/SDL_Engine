#include "SettingScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

SettingScene::SettingScene() // begaining of program constructs everything 
{
	SettingScene::Start();
}

SettingScene::~SettingScene()
= default;

void SettingScene::Draw()  // renders objects
{
	DrawDisplayList();
}

void SettingScene::Update() // updates the image / scenes
{
	UpdateDisplayList();
}

void SettingScene::Clean() // last thing the program does
{
	RemoveAllChildren();
}

void SettingScene::HandleEvents() // handle keyboard inputs 
{
	EventManager::Instance().update();

	// Button Events
	m_backButton->Update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
}

void SettingScene::Start() // main window 
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_settinglabel = new Label("END SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_settinglabel->SetParent(this);
	AddChild(m_settinglabel);

	// Restart Button
	m_backButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_backButton->GetTransform()->local_position = glm::vec2(400.0f, 400.0f);
	m_backButton->AddEventListener(CLICK, [&]()-> void
	{
		m_backButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_backButton->AddEventListener(MOUSE_OVER, [&]()->void
	{
		m_backButton->setAlpha(128);
	});

	m_backButton->AddEventListener(MOUSE_OUT, [&]()->void
	{
		m_backButton->setAlpha(255);
	});

	AddChild(m_backButton);
}
