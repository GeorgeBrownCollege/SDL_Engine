#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

struct RigidBody {

	glm::vec2 velocity;
	glm::vec2 acceleration;

	float mass;
	bool isColliding;
	bool hasGravity;
};
#endif /* defined (__RIGID_BODY__) */