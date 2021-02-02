#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "PlayScene.h"

StartScene::StartScene() {
	StartScene::Start();
}

StartScene::~StartScene()
= default;

void StartScene::Draw() {
	DrawDisplayList();
}

void StartScene::Update() {
	UpdateDisplayList();
}

void StartScene::Clean() {
	RemoveAllChildren();
}

void StartScene::HandleEvents() {
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->quit();
	}
}

void StartScene::Start() {
	//Background
	DisplayObject *m_pBackground = new Background();
	AddChild(m_pBackground);

	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color white = { 255, 255, 255, 0 };
	m_pStartLabel = new Label("Dog: Far From Home", "Consolas", 50, white, glm::vec2(550.0f, 150.0f));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	//Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->GetTransform()->position = glm::vec2(350.0f, 475.0f);
	m_pPlayer->SetMovementEnabled(false);
	AddChild(m_pPlayer);

	//Pressure plate Sprite
	m_pPressurePlate = new PressurePlate();
	m_pPressurePlate->GetTransform()->position = glm::vec2(625, 470.0f);
	AddChild(m_pPressurePlate);

	//Enemy Sprite
	m_pEnemy = new Enemy();
	m_pEnemy->GetTransform()->position = glm::vec2(742.0f, 445.0f);
	AddChild(m_pEnemy);

	// StartButton
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(550.0f, 350.0f);

	m_pStartButton->AddEventListener(CLICK, [&]()-> void {
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pStartButton->AddEventListener(MOUSE_OVER, [&]()->void {
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->AddEventListener(MOUSE_OUT, [&]()->void {
		m_pStartButton->setAlpha(255);
	});
	AddChild(m_pStartButton);
}