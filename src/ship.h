#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "TextureManager.h"
#include <glm/vec4.hpp>

#include "Agent.h"

class Ship final : public Agent
{
public:
	Ship();
	~Ship() override;

	// Inherited via GameObject
	void Draw() override;
	void Update() override;
	void Clean() override;

	void TurnRight();
	void TurnLeft();
	void MoveForward();
	void MoveBack();

	void Move();

	// getters
	[[nodiscard]] float GetMaxSpeed() const;

	// setters
	void SetMaxSpeed(float new_speed);

private:
	void CheckBounds();
	void Reset();

	float m_maxSpeed;
	float m_turnRate;

};


#endif /* defined (__SHIP__) */

