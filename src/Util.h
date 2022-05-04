#pragma once
#ifndef __UTIL__
#define __UTIL__

#include "GLM/vec2.hpp"
#include "GLM/vec4.hpp"
#include "ShapeType.h"
#include <SDL.h>

#include "GameObject.h"
#include "Renderer.h"

class Util
{
public:
	static const float EPSILON;
	static const float Deg2Rad;
	static const float Rad2Deg;

	static float Sign(float value);
	static float Clamp(float value, float min, float max);

	static glm::vec2 Clamp(glm::vec2 vec, float max_length);

	static float Clamp01(float value);
	static float Distance(glm::vec2 vec_a, glm::vec2 vec_b);
	static float SquaredDistance(glm::vec2 vec_a, glm::vec2 vec_b);
	static float Magnitude(glm::vec2 vec);
	static float SquaredMagnitude(glm::vec2 vec);
	static glm::vec2 LimitMagnitude(glm::vec2 vector, float magnitude);

	static float Lerp(float a, float b, float t);
	static glm::vec2 Lerp(glm::vec2 p0, glm::vec2 p1, float t);

	static float LerpUnclamped(float a, float b, float t);
	static float LerpAngle(float a, float b, float t);
	static float Repeat(float t, float length);

	static float RandomRange(float min, float max);
	static glm::vec2 RandomRange(glm::vec2 p0, glm::vec2 p1);

	static float Sanitize(float value);
	static glm::vec2 Min(glm::vec2 vec_a, glm::vec2 vec_b);
	static float Min(float a, float b);
	static glm::vec2 Max(glm::vec2 vec_a, glm::vec2 vec_b);
	static float Max(float a, float b);
	static glm::vec2 Negate(glm::vec2 vec);
	static glm::vec2 Inverse(glm::vec2 vec);
	static glm::vec2 Normalize(glm::vec2 vec);
	static float Angle(glm::vec2 from, glm::vec2 to);
	static float Dot(glm::vec2 lhs, glm::vec2 rhs);
	static float SignedAngle(glm::vec2 from, glm::vec2 to);

	// debugging convenience functions
	static void DrawLine(glm::vec2 start, glm::vec2 end, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawRect(glm::vec2 position, int width, int height, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawFilledRect(glm::vec2 position, int width, int height, glm::vec4 fill_colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawCircle(glm::vec2 centre, float radius, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), ShapeType type = ShapeType::SYMMETRICAL, SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawCapsule(glm::vec2 position, int width, int height, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());

	static float GetClosestEdge(glm::vec2 vec_a, GameObject* object);

	static SDL_Color ToSDLColour(glm::vec4 colour);

private:
	Util();
	~Util();

};




#endif /* defined (__UTIL__) */
