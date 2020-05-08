#include "PlayScene.h"
#include "Game.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	
}

void PlayScene::update()
{
	updateDisplayList();
	
}

void PlayScene::clean()
{

	removeAllChildren();
}

void PlayScene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
			
			}
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			// movement keys
			{
				if(keyPressed == SDLK_w)
				{
					std::cout << "move forward" << std::endl;

				}

				if (keyPressed == SDLK_a)
				{
					//std::cout << "move left" << std::endl;
					m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				}

				if (keyPressed == SDLK_s)
				{
					std::cout << "move back" << std::endl;
				
				}

				if (keyPressed == SDLK_d)
				{
					//std::cout << "move right" << std::endl;
					m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				}
			}
			
			break;
		case SDL_KEYUP:
			keyReleased = event.key.keysym.sym;

			if (keyReleased == SDLK_a)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}

			if (keyReleased == SDLK_d)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			break;
			
		}
	}
}

void PlayScene::start()
{
	m_pPlaneSprite = new PlaneSprite();
	addChild(m_pPlaneSprite);

	m_pPlayer = new Player();
	addChild(m_pPlayer);
}
