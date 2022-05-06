#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene() override;

	// Inherited via Scene
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Ship* m_pShip{};

	Button* m_pStartButton{};
};

#endif /* defined (__START_SCENE__) */