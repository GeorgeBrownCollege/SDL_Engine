#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"


#include "PlaneSprite.h"
#include "Player.h"



class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	glm::vec2 m_mousePosition;

	PlaneSprite* m_pPlaneSprite;
	Player* m_pPlayer;

};

#endif /* defined (__LEVEL1_SCENE__) */