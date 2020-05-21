#pragma once
#ifndef __ColliderCircle__
#define __ColliderCircle__

#include "Collider.h"

class ColliderCircle :
	public Collider
{
public:
	ColliderCircle(Transform* const owner, glm::vec2 anchor, float radius) : Collider(owner, anchor), m_radius(radius) {};
	~ColliderCircle() override {};

	float m_radius;
};

#endif