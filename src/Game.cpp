#include "Game.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "glm/gtx/string_cast.hpp"
#include "Renderer.h"
#include "EventManager.h"


// Game functions - DO NOT REMOVE ***********************************************

Game::Game() :
	m_bRunning(true), m_frames(0), m_pCurrentScene(nullptr), m_currentSceneState(SceneState::NO_SCENE), m_pWindow(nullptr)
{
	srand(static_cast<unsigned>(time(nullptr)));  // random seed
}

Game::~Game()
= default;


void Game::Init()
{
	m_bRunning = true;
}

bool Game::Init(const char* title, const int x, const int y, const int width, const int height, const bool fullscreen)
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
		m_pWindow = (Config::MakeResource(SDL_CreateWindow(title, x, y, width, height, flags)));

		// if window creation successful create our renderer
		if (m_pWindow != nullptr)
		{
			std::cout << "window creation success" << std::endl;

			// create a new SDL Renderer and store it in the Singleton
			const auto renderer = (Config::MakeResource(SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));
			Renderer::Instance().SetRenderer(renderer);

			if (Renderer::Instance().GetRenderer() != nullptr) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			// IMGUI 
			ImGuiWindowFrame::Instance().Init();

			// Initialize Font Support
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}

			Start();

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
		return false; //SDL could not initialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::Start()
{
	m_currentSceneState = SceneState::NO_SCENE;

	ChangeSceneState(SceneState::START);
}

bool Game::IsRunning() const
{
	return m_bRunning;
}


glm::vec2 Game::GetMousePosition() const
{
	return m_mousePosition;
}

void Game::SetFrames(const Uint32 frames)
{
	m_frames = frames;
}

Uint32 Game::GetFrames() const
{
	return m_frames;
}

float Game::GetDeltaTime() const
{
	return m_deltaTime;
}

void Game::SetDeltaTime(const float time)
{
	m_deltaTime = time;
}

void Game::ChangeSceneState(const SceneState new_state)
{
	if (new_state != m_currentSceneState) {

		// scene clean up
		if (m_currentSceneState != SceneState::NO_SCENE)
		{
			m_pCurrentScene->Clean();
			std::cout << "cleaning previous scene" << std::endl;
			FontManager::Instance().Clean();
			std::cout << "cleaning FontManager" << std::endl;
			TextureManager::Instance().Clean();
			std::cout << "cleaning TextureManager" << std::endl;
			ImGuiWindowFrame::Instance().ClearWindow();
			std::cout << "clearing ImGui Window" << std::endl;
		}

		m_pCurrentScene = nullptr;

		m_currentSceneState = new_state;

		EventManager::Instance().Reset();

		switch (m_currentSceneState)
		{
		case SceneState::START:
			m_pCurrentScene = new StartScene();
			std::cout << "start scene activated" << std::endl;
			break;
		case SceneState::PLAY:
			m_pCurrentScene = new PlayScene();
			std::cout << "play scene activated" << std::endl;
			break;
		case SceneState::END:
			m_pCurrentScene = new EndScene();
			std::cout << "end scene activated" << std::endl;
			break;

		default:
			std::cout << "default case activated" << std::endl;
			break;
		
		}
	}

}

SDL_Window* Game::GetWindow() const
{
	return m_pWindow.get();
}

void Game::Quit()
{
	m_bRunning = false;
}

void Game::Render() const
{
	SDL_RenderClear(Renderer::Instance().GetRenderer()); // clear the renderer to the draw colour

	m_pCurrentScene->Draw();

	SDL_RenderPresent(Renderer::Instance().GetRenderer()); // draw to the screen

	ImGuiWindowFrame::Instance().Render();
}

void Game::Update() const
{
	m_pCurrentScene->Update();
}

void Game::Clean() const
{
	std::cout << "cleaning game" << std::endl;

	// Clean Up for IMGUI
	//ImGui::DestroyContext();
	ImGuiWindowFrame::Instance().Clean();

	//TTF_Quit();

	SDL_Quit();
}

void Game::HandleEvents() const
{
	m_pCurrentScene->HandleEvents();
}
