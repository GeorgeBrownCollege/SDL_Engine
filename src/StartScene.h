#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "Enemy.h"
#include "PressurePlate.h"
#include "Player.h"


class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Player *m_pPlayer;
	PressurePlate *m_pPressurePlate;
	Enemy* m_pEnemy;
	Button* m_pStartButton;
	Button* m_settingButton;
};

#endif /* defined (__START_SCENE__) */