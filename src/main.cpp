// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"

constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS;

/**
 * \brief Program Entry Point
 */
int main(int argc, char* args[])
{
	Uint32 frames = 0;

	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);

	// Display Main SDL Window
	Game::Instance().Init("SDL_Engine v0.28", 100, 100, 800, 600, false);

	// Main Game Loop
	while (Game::Instance().IsRunning())
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());

		Game::Instance().HandleEvents();
		Game::Instance().Update();
		Game::Instance().Render();

		if (const float frame_time = static_cast<float>(SDL_GetTicks() - frame_start); 
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time
		const auto delta_time = static_cast<float>(SDL_GetTicks() - frame_start) / 1000.0f;
		Game::Instance().SetDeltaTime(delta_time);

		frames++;
		Game::Instance().SetFrames(frames);

	}

	Game::Instance().Clean();
	return 0;
}

