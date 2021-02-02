#pragma once
#include "EnemyAnimationState.h"
#include "Sprite.h"

class Enemy final : public Sprite {
public:
	Enemy();
	~Enemy();

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// setters
	void setAnimationState(EnemyAnimationState new_state);

private:
	void m_buildAnimations();

	EnemyAnimationState m_currentAnimationState;
};