// Core Libraries
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>

#include "Game.h"

constexpr int FPS = 60;
constexpr int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	Uint32 frames = 0;

	// show console
	AllocConsole();
	freopen("CON", "w", stdout);

	TheGame::Instance().Init("SDL_Engine v0.28", 100, 100, 800, 600, false);

	while (TheGame::Instance().IsRunning())
	{
		const Uint32 frame_start = SDL_GetTicks();

		TheGame::Instance().HandleEvents();
		TheGame::Instance().Update();
		TheGame::Instance().Render();

		const Uint32 frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time
		const auto delta_time = static_cast<float>(SDL_GetTicks() - frame_start) / 1000.0f;
		TheGame::Instance().SetDeltaTime(delta_time);

		frames++;
		TheGame::Instance().SetFrames(frames);

	}

	TheGame::Instance().Clean();
	return 0;
}

