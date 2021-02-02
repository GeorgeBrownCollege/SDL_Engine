#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite {
	public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void Draw() override;
	void HandleEvents();
	virtual void Update() override;
	virtual void Clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);

	private:
	void m_buildAnimations();

	bool m_barking, m_canBark;
	
	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */