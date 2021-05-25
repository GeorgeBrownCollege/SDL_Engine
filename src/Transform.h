#pragma once
#ifndef __TRANSFORM__
#define __TRANSFORM__
#include <glm/vec2.hpp>

/*
 * The GameObject uses composition to have a Transform which is this struct.
 * It has a few variables you can use to manipulate the GameObject.
 */

struct Transform
{
	glm::vec2 position; // Position with an x and y usually used in relation to a window
						// which starts at 0 x and 0 y at the top left corner of the window 
	glm::vec2 rotation; // used to rotate the GameObject
	glm::vec2 scale; // used to change the size of the gameObject in relation to the original size
};
#endif /* defined (__TRANSFORM__) */