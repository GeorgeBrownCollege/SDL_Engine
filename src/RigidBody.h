#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

/*
 * GameObject class uses composition to have a rigidbody which is this struct.
 * You can use this for physics. It also has the isColliding bool which can be
 * used for collision like in the CollisionManager.
 */
struct RigidBody
{
	//physics
	float mass;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	
	//collision
	bool isColliding;
};
#endif /* defined (__RIGID_BODY__) */