#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite {
	private:
	const int M_MAX_SPEED = 4.75f;
	float m_xAcceleration; // This will hold the acceleration for the player in the x direction 
	
	public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void SetMaxSpeed(int _speed);

	private:	
	void m_buildAnimations();
	void Move(int _direction); // This will move the player
	void Decelerate(); // This will bring the player to a stop when the function is called

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */