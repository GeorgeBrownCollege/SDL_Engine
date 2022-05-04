#pragma once
#ifndef __GAME_CONTROLLER__
#define __GAME_CONTROLLER__

#include <SDL.h>

struct GameController
{
	explicit GameController(SDL_GameController* controller);
	~GameController();

	void Update();

	SDL_GameController* handle;

	// DPAD Buttons
	bool DPAD_UP;
	bool DPAD_DOWN;
	bool DPAD_LEFT;
	bool DPAD_RIGHT;

	// control buttons
	bool BUTTON_START;
	bool BUTTON_BACK;
	bool BUTTON_GUIDE;

	// shoulder buttons
	bool BUTTON_SHOULDER_LEFT;
	bool BUTTON_SHOULDER_RIGHT;

	// face buttons
	bool BUTTON_A;
	bool BUTTON_B;
	bool BUTTON_X;
	bool BUTTON_Y;

	// left stick
	Sint16 STICK_LEFT_HORIZONTAL;
	Sint16 STICK_LEFT_VERTICAL;
	bool STICK_LEFT_BUTTON;

	// right stick
	Sint16 STICK_RIGHT_HORIZONTAL;
	Sint16 STICK_RIGHT_VERTICAL;
	bool STICK_RIGHT_BUTTON;
};

#endif /* defined (__GAME_CONTROLLER__) */