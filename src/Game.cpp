#include "Game.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "glm/gtx/string_cast.hpp"
#include "Renderer.h"
#include "EventManager.h"


Game* Game::s_pInstance = nullptr;

// Game functions - DO NOT REMOVE ***********************************************

Game::Game() :
	m_pWindow(nullptr), m_bRunning(true), m_frames(0), m_currentScene(nullptr), m_currentSceneState(NO_SCENE)
{
	srand(unsigned(time(nullptr)));  // random seed
}

Game::~Game()
= default;


void Game::init()
{
	m_bRunning = true;
}

bool Game::init(const char* title, const int x, const int y, const int width, const int height, const bool fullscreen)
{
	auto flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = (Config::make_resource(SDL_CreateWindow(title, x, y, width, height, flags)));
		
		// if window creation successful create our renderer
		if (m_pWindow != nullptr)
		{
			std::cout << "window creation success" << std::endl;

			// create a new SDL Renderer and store it in the Singleton
			const auto renderer = (Config::make_resource(SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));
			Renderer::Instance()->setRenderer(renderer);
			
			if (Renderer::Instance()->getRenderer() != nullptr) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			// Initialize Font Support
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}

			start();

		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::start()
{
	m_currentSceneState = NO_SCENE;

	changeSceneState(START_SCENE);
}

bool Game::isRunning() const
{
	return m_bRunning;
}


glm::vec2 Game::getMousePosition() const
{
	return m_mousePosition;
}

void Game::setFrames(const Uint32 frames)
{
	m_frames = frames;
}

Uint32 Game::getFrames() const
{
	return m_frames;
}

void Game::changeSceneState(const SceneState new_state)
{
	if (new_state != m_currentSceneState) {

		// scene clean up
		if (m_currentSceneState != NO_SCENE) 
		{
			m_currentScene->clean();
			std::cout << "cleaning previous scene" << std::endl;
			FontManager::Instance()->clean();
			std::cout << "cleaning FontManager" << std::endl;
			TextureManager::Instance()->clean();
			std::cout << "cleaning TextureManager" << std::endl;
		}

		m_currentScene = nullptr;

		m_currentSceneState = new_state;

		EventManager::Instance().reset();

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
	
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::render() const
{
	SDL_RenderClear(Renderer::Instance()->getRenderer()); // clear the renderer to the draw colour

	m_currentScene->draw();

	SDL_RenderPresent(Renderer::Instance()->getRenderer()); // draw to the screen
}

void Game::update() const
{
	m_currentScene->update();
}

void Game::clean() const
{
	std::cout << "cleaning game" << std::endl;

	TTF_Quit();

	SDL_Quit();
}

void Game::handleEvents()
{
	m_currentScene->handleEvents();
}