#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

class GameObject;

struct RigidBody
{
	float mass;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	GameObject* collider = nullptr;
};
#endif /* defined (__RIGID_BODY__) */