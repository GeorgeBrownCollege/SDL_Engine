#include "GameController.h"

GameController::GameController(SDL_GameController* controller):
	handle(controller), DPAD_UP(false), DPAD_DOWN(false), DPAD_LEFT(false), DPAD_RIGHT(false),
	BUTTON_START(false), BUTTON_BACK(false), BUTTON_SHOULDER_LEFT(false), BUTTON_SHOULDER_RIGHT(false),
	BUTTON_A(false), BUTTON_B(false), BUTTON_X(false), BUTTON_Y(false),
	STICK_LEFT_HORIZONTAL(false), STICK_LEFT_VERTICAL(false), STICK_RIGHT_HORIZONTAL(false), STICK_RIGHT_VERTICAL(false)
{}

GameController::~GameController()
= default;

void GameController::Update()
{
    // DPAD Buttons
    DPAD_UP = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_UP);
    DPAD_DOWN = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    DPAD_LEFT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    DPAD_RIGHT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    // control buttons
    BUTTON_START = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_START);
    BUTTON_BACK = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_BACK);
    BUTTON_GUIDE = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_GUIDE);

    // shoulders
    BUTTON_SHOULDER_LEFT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    BUTTON_SHOULDER_RIGHT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    // face buttons
    BUTTON_A = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_A);
    BUTTON_B = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_B);
    BUTTON_X = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_X);
    BUTTON_Y = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_Y);

    // sticks
    STICK_LEFT_HORIZONTAL = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_LEFTX);
    STICK_LEFT_VERTICAL = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_LEFTY);
    STICK_LEFT_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_LEFTSTICK);

    STICK_RIGHT_HORIZONTAL = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_RIGHTX);
    STICK_RIGHT_VERTICAL = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_RIGHTY);
    STICK_RIGHT_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
}
