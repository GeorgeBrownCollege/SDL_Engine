#pragma once
#ifndef __GAME_CONTROLLER__
#define __GAME_CONTROLLER__

#include <SDL.h>

struct GameController
{
	GameController(SDL_GameController* controller);
	~GameController();

	void update();

	SDL_GameController* handle;

	// DPAD Buttons
	bool DPAD_UP;
	bool DPAD_DOWN;
	bool DPAD_LEFT;
	bool DPAD_RIGHT;

	// control buttons
	bool START_BUTTON;
	bool BACK_BUTTON;
	bool GUIDE_BUTTON;

	// shoulder buttons
	bool LEFT_SHOULDER;
	bool RIGHT_SHOULDER;

	// face buttons
	bool A_BUTTON;
	bool B_BUTTON;
	bool X_BUTTON;
	bool Y_BUTTON;

	// left stick
	Sint16 LEFT_STICK_X;
	Sint16 LEFT_STICK_Y;
	bool LEFT_STICK_BUTTON;

	// right stick
	Sint16 RIGHT_STICK_X;
	Sint16 RIGHT_STICK_Y;
	bool RIGHT_STICK_BUTTON;
};

#endif /* defined (__GAME_CONTROLLER__) */