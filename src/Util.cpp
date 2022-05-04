#include "Util.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>
#include <SDL.h>
#include "Renderer.h"

constexpr float Util::EPSILON = glm::epsilon<float>();
constexpr float Util::Deg2Rad = glm::pi<float>() / 180.0f;
constexpr float Util::Rad2Deg = 180.0f / glm::pi<float>();

Util::Util()
= default;


Util::~Util()
= default;

/**
* Returns -1.0 if the value is less than 0 and 1.0 if the value is greater than 0
*/
float Util::Sign(const float value)
{
	return (value < 0.0f) ? -1.0f : 1.0f;
}

/**
* This method confines the value provided between min and max and returns the result
*
*/
float Util::Clamp(float value, const float min, const float max)
{
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
	return value;
}

/** This method confines a vector magnitude to the max_length parameter */
glm::vec2 Util::Clamp(glm::vec2 vec, const float max_length)
{
	if (const auto sqr_magnitude = Util::SquaredMagnitude(vec); sqr_magnitude > max_length * max_length)
	{
		const auto mag = sqrt(sqr_magnitude);
		const auto normalized_x = vec.x / mag;
		const auto normalized_y = vec.y / mag;
		return {normalized_x * max_length, normalized_y * max_length};
	}
	return vec;
}

/**
* Clamps a value between 0 and 1 and returns the result
*
*/
float Util::Clamp01(const float value)
{
	auto result = 0.0f;
	if (value < 0.0f) {
		result = 0.0f;
	}
	else if (value > 1.0f) {
		result = 1.0f;
	}
	else {
		result = value;
	}
	return result;
}

/**
* Returns the Euclidean distance of vecA and vecB
*/
float Util::Distance(const glm::vec2 vecA, const glm::vec2 vecB)
{
	const auto x = vecB.x - vecA.x;
	const auto y = vecB.y - vecA.y;
	return sqrt((x * x) + (y * y));
}

/**
* Returns the Squared Euclidean distance of vecA and vecB
* No Square Root
*/
float Util::SquaredDistance(const glm::vec2 vecA, const glm::vec2 vecB)
{
	const auto x = vecB.x - vecA.x;
	const auto y = vecB.y - vecA.y;
	return (x * x) + (y * y);
}

/**
* Returns the magnitude of a vec2
*
*/
float Util::Magnitude(const glm::vec2 vec)
{
	const auto x = vec.x;
	const auto y = vec.y;
	return sqrt((x * x) + (y * y));
}

/**
* Returns the squared Magnitude of a vec2
* No Square Root
*/
float Util::SquaredMagnitude(glm::vec2 vec)
{
	const auto x = vec.x;
	const auto y = vec.y;
	return (x * x) + (y * y);
}


glm::vec2 Util::LimitMagnitude(glm::vec2 vector, const float magnitude)
{
	if (const auto length = Magnitude(vector); length > magnitude) {
		const auto limiter = magnitude / length;
		vector.x *= limiter;
		vector.y *= limiter;
		return vector;
	}
	return vector;
}

/**
* Performs Linear Interpolation between and b
* at some t value between 0 and 1
*
*/
float Util::Lerp(const float a, const float b, const float t)
{
	return a + (b - a) * Util::Clamp01(t);
}

glm::vec2 Util::Lerp(const glm::vec2 p0, const glm::vec2 p1, const float t)
{
	const auto lerp_xs = Lerp(p0.x, p1.x, t);
	const auto lerp_ys = Lerp(p0.y, p1.y, t);
	return {lerp_xs, lerp_ys};
}

/**
	 * Lerps between a and b at some t value - unclamped.
*
*/
float Util::LerpUnclamped(const float a, const float b, const float t)
{
	return a + (b - a) * t;
}

/**
* Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.
*
*/
float Util::LerpAngle(const float a, const float b, const float t)
{
	auto num = Util::Repeat(b - a, 360.0);
	if (num > 180.0f) 
	{
		num -= 360.0f;
	}
	return a + num * Util::Clamp01(t);
}

/**
* Loops the value t, so that it is never larger than length and never smaller than 0.
*
*/
float Util::Repeat(const float t, const float length)
{
	return Clamp(t - glm::floor(t / length) * length, 0.0f, length);
}

float Util::RandomRange(const float min, const float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

glm::vec2 Util::RandomRange(const glm::vec2 p0, const glm::vec2 p1)
{
	const auto random_x = RandomRange(p0.x, p1.x);
	const auto random_y = RandomRange(p0.y, p1.y);
	return {random_x, random_y};
}

/**
* This Utility function checks to see if a number is very small (close to EPSILON)
* If so, it changes the value to 0.0;
*/
float Util::Sanitize(float value)
{
	if ((value >= -Util::EPSILON) && (value <= Util::EPSILON)) {
		value = 0.0;
	}
	return value;
}

/**
* This method computes the minimum values for x and y from vecA and vecB
* and returns them in dest or returns the result in a new vec2
*
*/
glm::vec2 Util::Min(const glm::vec2 vecA, const glm::vec2 vecB)
{
	glm::vec2 dest;
	dest.x = glm::min(vecA.x, vecB.x);
	dest.y = glm::min(vecA.y, vecB.y);
	return dest;
}

float Util::Min(const float a, const float b)
{
	return a < b ? a : b;
}

/**
* This method computes the maximum values of x and y from vecA and vecB
* and returns the result in dest or returns the result as a new vec2
*
*/
glm::vec2 Util::Max(const glm::vec2 vecA, const glm::vec2 vecB)
{
	glm::vec2  dest;
	dest.x = glm::max(vecA.x, vecB.x);
	dest.y = glm::max(vecA.y, vecB.y);
	return dest;
}

float Util::Max(float a, float b)
{
	return a > b ? a : b;
}

/**
* Negates the x and y components of a vec2 and returns them in a new vec2 object
*
*/
glm::vec2 Util::Negate(const glm::vec2 vec)
{
	glm::vec2 dest;
	dest.x = -vec.x;
	dest.y = -vec.y;
	return dest;
}

/**
* Returns the inverse x and y components of src vec2 and returns them in a new vec2 object
*
*/
glm::vec2 Util::Inverse(const glm::vec2 vec)
{
	glm::vec2 dest;
	dest.x = 1.0 / vec.x;
	dest.y = 1.0 / vec.y;
	return dest;
}


/**
* Normalizes vec2 and stores the result in a new vec2 object
*
*/
glm::vec2 Util::Normalize(const glm::vec2 vec)
{
	glm::vec2 dest;
	const auto x = vec.x;
	const auto y = vec.y;
	if (auto length = (x * x) + (y * y); length > 0) {
		length = 1.0 / sqrt(length);
		dest.x = vec.x * length;
		dest.y = vec.y * length;
	}
	return dest;
}

/**
* Returns the angle in degrees between from and to.
*/
float Util::Angle(const glm::vec2 from, const glm::vec2 to)
{
	return acos(Util::Clamp(Util::Dot(Util::Normalize(from), Util::Normalize(to)), -1.0f, 1.0f)) * 57.29578f;
}

/**
* Dot Product of two vectors.
*/
float Util::Dot(const glm::vec2 lhs, const glm::vec2 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Util::SignedAngle(const glm::vec2 from, const glm::vec2 to)
{
	const auto unsigned_angle = Util::Angle(from, to);
	const auto sign = Util::Sign(from.x * to.y - from.y * to.x);
	return unsigned_angle * sign;
}

void Util::DrawLine(const glm::vec2 start, const glm::vec2 end, const glm::vec4 colour, SDL_Renderer* renderer)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawRect(const glm::vec2 position, const int width, const int height, const glm::vec4 colour, SDL_Renderer* renderer)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_Rect rectangle;
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = width;
	rectangle.h = height;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawFilledRect(const glm::vec2 position, const int width, const int height, const glm::vec4 fill_colour, SDL_Renderer* renderer)
{
	int r = floor(fill_colour.r * 255.0f);
	int g = floor(fill_colour.g * 255.0f);
	int b = floor(fill_colour.b * 255.0f);
	int a = floor(fill_colour.a * 255.0f);

	SDL_Rect rectangle;
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = width;
	rectangle.h = height;

	/* Declaring the surface. */
	SDL_Surface* surface;

	/* Creating the surface. */
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
		
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b));
	SDL_RenderDrawRect(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCircle(const glm::vec2 centre, const int radius, const glm::vec4 colour, const ShapeType type, SDL_Renderer* renderer)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	const int diameter = floor(radius * 2.0f);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		switch (type)
		{
		case SEMI_CIRCLE_TOP:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			break;
		case SEMI_CIRCLE_BOTTOM:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y); // bottom left
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x); // bottom left
			break;
		case SEMI_CIRCLE_LEFT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		case SEMI_CIRCLE_RIGHT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			break;
		case SYMMETRICAL:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		}


		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCapsule(const glm::vec2 position, const int width, const int height, const glm::vec4 colour, SDL_Renderer* renderer)
{
	int radius;
	const int halfWidth = floor(width * 0.5f);
	const int halfHeight = floor(height * 0.5f);
	if (width > height)
	{
		// Horizontal Capsule
		radius = halfHeight * 0.5f;
		DrawCircle(glm::vec2(position.x - halfWidth + halfHeight, position.y), halfHeight, colour, SEMI_CIRCLE_LEFT, renderer);
		DrawCircle(glm::vec2(position.x + halfWidth - halfHeight, position.y), halfHeight, colour, SEMI_CIRCLE_RIGHT, renderer);
		DrawLine(glm::vec2(position.x - halfWidth + halfHeight, position.y - halfHeight), glm::vec2(position.x + halfWidth - halfHeight, position.y - halfHeight), colour, renderer);
		DrawLine(glm::vec2(position.x - halfWidth + halfHeight, position.y + halfHeight), glm::vec2(position.x + halfWidth - halfHeight, position.y + halfHeight), colour, renderer);
	}
	else if (width < height)
	{
		// Vertical Capsule
		radius = halfWidth * 0.5f;
		DrawCircle(glm::vec2(position.x, position.y - halfHeight + radius), radius, colour, SEMI_CIRCLE_TOP, renderer);
		DrawCircle(glm::vec2(position.x, position.y + halfHeight - radius), radius, colour, SEMI_CIRCLE_BOTTOM, renderer);
		DrawLine(glm::vec2(position.x - radius, position.y - halfHeight + radius), glm::vec2(position.x - halfWidth * 0.5f, position.y + halfHeight * 0.5f), colour, renderer);
		DrawLine(glm::vec2(position.x + radius, position.y - halfHeight + radius), glm::vec2(position.x + halfWidth * 0.5f, position.y + halfHeight * 0.5f), colour, renderer);
	}
	else
	{
		// Circle
		radius = width;
		DrawCircle(position, radius = halfWidth, colour, SYMMETRICAL, renderer);
	}
}


