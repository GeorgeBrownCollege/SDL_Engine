#include "CollisionManager.h"

#include <algorithm> // for FLT_EPSILON, min/max

#include "Util.h"
#include "Transform.h"
#include "ColliderCircle.h"
#include "ColliderAABB.h"

bool CollisionManager::isColliding(ColliderCircle* object1, ColliderCircle* object2)
{
	float radii = object1->m_radius + object2->m_radius;
	float radiiSquared = radii * radii;

	if (CollisionManager::squaredDistance(object1->getPosition(), object2->getPosition()) < (radiiSquared))
	{
		return true;
	} 
	else return false;
}

bool CollisionManager::isColliding(ColliderCircle* object1, ColliderAABB* object2)
{
	// circle
	const glm::vec2 circleCentre = object1->getPosition();
	const int circleRadius = object1->m_radius;

	// aabb
	const float boxWidth = object2->m_size.x;
	const float boxHeight = object2->m_size.y;
	const glm::vec2 boxStart = object2->getPosition();

	if (circleAABBsquaredDistance(circleCentre, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius * circleRadius))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionManager::isColliding(ColliderAABB* object1, ColliderCircle* object2)
{
	return isColliding(object2, object1); //AABB-Circle is the same thing as Circle-AABB but reversed
}

bool CollisionManager::isColliding(ColliderAABB* object1, ColliderAABB* object2)
{
	const auto p1 = object1->getPosition();
	const auto p2 = object2->getPosition();

	const float p1Width = object1->m_size.x;
	const float p1Height = object1->m_size.y;
	const float p2Width = object2->m_size.x;
	const float p2Height = object2->m_size.y;

	if (
		p1.x < p2.x + p2Width &&
		p1.x + p1Width > p2.x &&
		p1.y < p2.y + p2Height &&
		p1.y + p1Height > p2.y
		)
	{
		return true;
	} else return false;
}

bool CollisionManager::lineLineCheck(const glm::vec2 line1_start, const glm::vec2 line1_end, const glm::vec2 line2_start, const glm::vec2 line2_end)
{
	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto x3 = line2_start.x;
	const auto x4 = line2_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto y3 = line2_start.y;
	const auto y4 = line2_end.y;

	// calculate the distance to intersection point
	const auto uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	const auto uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}

	return false;
}

inline bool CollisionManager::lineCircleCheck(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 circle_center, float circle_radius)
{
	return distanceToLineSq(circle_center, line_start, line_end) < circle_radius * circle_radius;
}

bool CollisionManager::lineAABBCheck(const glm::vec2 line1_start, const glm::vec2 line1_end, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	// If either point is inside the AABB it is guaranteed to be colliding already
	if (pointAABBCheck(line1_start, rect_start, rect_width, rect_height) || pointAABBCheck(line1_end, rect_start, rect_width, rect_height))
	{
		return true;
	}

	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto rx = rect_start.x;
	const auto ry = rect_start.y;
	const auto rw = rect_width;
	const auto rh = rect_height;

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	const auto left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	const auto right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	const auto top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	const auto bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));
	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}

	return false;
}

inline bool CollisionManager::pointLineCheck(glm::vec2 point, glm::vec2 line_start, glm::vec2 line_end)
{
	//If the distance between the point and the two ends sums to the distance between the two ends, it is on the line segment
	return(abs(Util::distance(point, line_start) + Util::distance(point, line_end) - Util::distance(line_start, line_end))) < FLT_EPSILON;
}

inline bool CollisionManager::pointCircleCheck(glm::vec2 point, glm::vec2 circle_center, float circle_radius)
{
	//if the point is closer than the radius, it is contained
	return squaredDistance(point, circle_center) < circle_radius * circle_radius;
}

bool CollisionManager::pointAABBCheck(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const auto width = rect_width;
	const auto height = rect_height;

	if (point.x > rect_start.x &&
		point.x < rect_start.x + width &&
		point.y > rect_start.y &&
		point.y < rect_start.y + height)
	{
		return true;
	}
	return false;
}


bool CollisionManager::pointAABBCheckCentered(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const auto width = rect_width/2;
	const auto height = rect_height/2;

	if (point.x > rect_start.x - width &&
		point.x < rect_start.x + width &&
		point.y > rect_start.y - height &&
		point.y < rect_start.y + height)
	{
		return true;
	}
	return false;
}


inline float CollisionManager::squaredDistance(const glm::vec2 p1, const glm::vec2 p2)
{
	const float diffOfXs = p2.x - p1.x;
	const float diffOfYs = p2.y - p1.y;
	const auto result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

int CollisionManager::minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end)
{
	auto u = line1_end - line1_start;
	auto v = line2_end - line2_start;
	auto w = line1_start - line2_start;
	auto a = Util::dot(u, u);         // always >= 0
	auto b = Util::dot(u, v);
	auto c = Util::dot(v, v);         // always >= 0
	auto d = Util::dot(u, w);
	auto e = Util::dot(v, w);
	auto D = a * c - b * b;					// always >= 0
	float sc, tc;

	// compute the line parameters of the two closest points
	if (D < FLT_EPSILON) {					// the lines are almost parallel
		sc = 0.0;
		tc = (b > c ? d / b : e / c);			// use the largest denominator
	}
	else {
		sc = (b * e - c * d) / D;
		tc = (a * e - b * d) / D;
	}

	// get the difference of the two closest points
	auto dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

	auto norm = Util::dot(dP, dP);
	return norm;
}

int CollisionManager::circleAABBsquaredDistance(const glm::vec2 circle_centre, float circle_radius, const glm::vec2 box_start, const float box_width, const float box_height)
{
	auto dx = std::max(box_start.x - circle_centre.x, 0.0f);
	dx = std::max(dx, circle_centre.x - (box_start.x + box_width));
	auto dy = std::max(box_start.y - circle_centre.y, 0.0f);
	dy = std::max(dy, circle_centre.y - (box_start.y + box_height));

	return (dx * dx) + (dy * dy);
}


glm::vec2 CollisionManager::separationVector(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end)
{
	glm::vec2 segment = line_end - line_start;

	// project point onto line segment
	float proj = Util::dot(point - line_start, segment);
	// keep it within the line segment
	proj = Util::clamp(proj, 0.f, 1.0f);

	//produce a point from the projection and see how far it is away from the actual point
	glm::vec2 separation = (segment * proj) - point;
	
	return separation;
}

float CollisionManager::distanceToLine(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end)
{
	return separationVector(point, line_start, line_end).length();
}

float CollisionManager::distanceToLineSq(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end)
{
	return Util::squaredMagnitude(separationVector(point, line_start, line_end));
}

CollisionManager::CollisionManager()
= default;


CollisionManager::~CollisionManager()
= default;
