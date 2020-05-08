#pragma once
#ifndef __TRANSFORM__
#define __TRANSFORM__
#include <glm/vec2.hpp>

struct Transform
{
	glm::vec2 position;
	glm::vec2 rotation;
	glm::vec2 scale;
};
#endif /* defined (__TRANSFORM__) */