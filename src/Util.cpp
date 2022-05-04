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
glm::vec2 Util::Clamp(const glm::vec2 vec, const float max_length)
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
float Util::Distance(const glm::vec2 vec_a, const glm::vec2 vec_b)
{
	const auto x = vec_b.x - vec_a.x;
	const auto y = vec_b.y - vec_a.y;
	return sqrt((x * x) + (y * y));
}

/**
* Returns the Squared Euclidean distance of vecA and vecB
* No Square Root
*/
float Util::SquaredDistance(const glm::vec2 vec_a, const glm::vec2 vec_b)
{
	const auto x = vec_b.x - vec_a.x;
	const auto y = vec_b.y - vec_a.y;
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
float Util::SquaredMagnitude(const glm::vec2 vec)
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
glm::vec2 Util::Min(const glm::vec2 vec_a, const glm::vec2 vec_b)
{
	return { glm::min(vec_a.x, vec_b.x) , glm::min(vec_a.y, vec_b.y) };
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
glm::vec2 Util::Max(const glm::vec2 vec_a, const glm::vec2 vec_b)
{
	return { glm::max(vec_a.x, vec_b.x), glm::max(vec_a.y, vec_b.y)};
}

float Util::Max(const float a, const float b)
{
	return a > b ? a : b;
}

/**
* Negates the x and y components of a vec2 and returns them in a new vec2 object
*
*/
glm::vec2 Util::Negate(const glm::vec2 vec)
{
	return { -vec.x, -vec.y };
}

/**
* Returns the inverse x and y components of src vec2 and returns them in a new vec2 object
*
*/
glm::vec2 Util::Inverse(const glm::vec2 vec)
{
	return {1.0f / vec.x, 1.0f / vec.y};
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
	if (auto length = (x * x) + (y * y); length > 0) 
	{
		length = 1.0f / sqrt(length);
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
	return acos(Clamp(Dot(Normalize(from), Normalize(to)), -1.0f, 1.0f)) * 57.29578f;
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
	const auto [r, g, b, a] = ToSDLColour(colour);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawRect(const glm::vec2 position, const int width, const int height, const glm::vec4 colour, SDL_Renderer* renderer)
{
	const auto [r, g, b, a] = ToSDLColour(colour);

	SDL_FRect rectangle{};
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = static_cast<float>(width);
	rectangle.h = static_cast<float>(height);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRectF(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawFilledRect(const glm::vec2 position, const int width, const int height, const glm::vec4 fill_colour, SDL_Renderer* renderer)
{
	const auto [r, g, b, a] = ToSDLColour(fill_colour);

	SDL_FRect rectangle{};
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = static_cast<float>(width);
	rectangle.h = static_cast<float>(height);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRectF(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCircle(const glm::vec2 centre, const float radius, const glm::vec4 colour, const ShapeType type, SDL_Renderer* renderer)
{
	const auto [r, g, b, a] = ToSDLColour(colour);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	const float diameter = floor(radius * 2.0f);

	float x = (radius - 1);
	float y = 0.0f;
	float tx = 1;
	float ty = 1;
	float error = (tx - diameter);

	while (x >= y)
	{
		switch (type)
		{
		case ShapeType::SEMI_CIRCLE_TOP:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y - x);
			break;
		case ShapeType::SEMI_CIRCLE_BOTTOM:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y + y); // bottom right
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y + y); // bottom left
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y + x); // bottom right
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y + x); // bottom left
			break;
		case ShapeType::SEMI_CIRCLE_LEFT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y + x);
			break;
		case ShapeType::SEMI_CIRCLE_RIGHT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y + x);
			break;
		case ShapeType::SYMMETRICAL:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPointF(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPointF(renderer, centre.x + y, centre.y + x);
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPointF(renderer, centre.x - y, centre.y + x);
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
	float radius;
	const float half_width = floor(static_cast<float>(width) * 0.5f);
	const float half_height = floor(static_cast<float>(height) * 0.5f);
	if (width > height)
	{
		// Horizontal Capsule
		DrawCircle(glm::vec2(position.x - half_width + half_height, position.y), half_height, colour, ShapeType::SEMI_CIRCLE_LEFT, renderer);
		DrawCircle(glm::vec2(position.x + half_width - half_height, position.y), half_height, colour, ShapeType::SEMI_CIRCLE_RIGHT, renderer);
		DrawLine(glm::vec2(position.x - half_width + half_height, position.y - half_height), glm::vec2(position.x + half_width - half_height, position.y - half_height), colour, renderer);
		DrawLine(glm::vec2(position.x - half_width + half_height, position.y + half_height), glm::vec2(position.x + half_width - half_height, position.y + half_height), colour, renderer);
	}
	else if (width < height)
	{
		// Vertical Capsule
		radius = half_width * 0.5f;
		DrawCircle(glm::vec2(position.x, position.y - half_height + radius), radius, colour, ShapeType::SEMI_CIRCLE_TOP, renderer);
		DrawCircle(glm::vec2(position.x, position.y + half_height - radius), radius, colour, ShapeType::SEMI_CIRCLE_BOTTOM, renderer);
		DrawLine(glm::vec2(position.x - radius, position.y - half_height + radius), glm::vec2(position.x - half_width * 0.5f, position.y + half_height * 0.5f), colour, renderer);
		DrawLine(glm::vec2(position.x + radius, position.y - half_height + radius), glm::vec2(position.x + half_width * 0.5f, position.y + half_height * 0.5f), colour, renderer);
	}
	else
	{
		// Circle
		DrawCircle(position, radius = half_width, colour, ShapeType::SYMMETRICAL, renderer);
	}
}

float Util::GetClosestEdge(const glm::vec2 vec_a, GameObject* object)
{
	const auto width = static_cast<float>(object->GetWidth());
	const auto height = static_cast<float>(object->GetHeight());

	const auto target_offset = glm::vec2(width * 0.5f, height * 0.5f);
	const auto target_top_left = object->GetTransform()->position - target_offset;
	SDL_Rect rect = { static_cast<int>(target_top_left.x), static_cast<int>(target_top_left.y), object->GetWidth(), object->GetHeight() };

	const glm::vec2 sides[4] = { { rect.x + rect.w / 2, rect.y }, // top
						   { rect.x + rect.w / 2, rect.y + rect.h }, // bottom
						   { rect.x, rect.y + rect.h / 2 }, // left
						   { rect.x + rect.w, rect.y + rect.h / 2 } }; // right
	float dist = Distance(vec_a, sides[0]);
	for (int i = 1; i < 4; i++)
	{
		dist = Min(Distance(vec_a, sides[i]), dist);
	}
	return dist;
}

SDL_Color Util::ToSDLColour(const glm::vec4 colour)
{
	SDL_Color color{};
	color.r = static_cast<Uint8>(floor(colour.r * 255.0f));
	color.g = static_cast<Uint8>(floor(colour.g * 255.0f));
	color.b = static_cast<Uint8>(floor(colour.b * 255.0f));
	color.a = static_cast<Uint8>(floor(colour.a * 255.0f));
	return color;
}