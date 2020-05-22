#include "CollisionManager.h"

#include <algorithm> // for FLT_EPSILON, min/max

#include "Util.h"
#include "Transform.h"
#include "ColliderCircle.h"
#include "ColliderAABB.h"

//Todo: make this work with non-uniform scaling
bool CollisionManager::isColliding(ColliderCircle* object1, ColliderCircle* object2)
{
	float radii = object1->m_radius * object1->getScale().x + object2->m_radius * object2->getScale().x;
	float radiiSquared = radii * radii;

	if (CollisionManager::squaredDistance(object1->getPosition(), object2->getPosition()) < (radiiSquared))
	{
		return true;
	}
	else return false;
}

bool CollisionManager::isColliding(ColliderCircle* circle, ColliderAABB* aabb)
{
	//First, we express the position of the circle relative to the

	// circle
	const glm::vec2 circlePos = circle->getPosition();
	const float radiusSq = circle->m_radius * circle->m_radius;

	// get corners of aabb
	const float boxWidth = aabb->m_size.x * aabb->getScale().x;
	const float boxHeight = aabb->m_size.y * aabb->getScale().y;
	const glm::vec2 topLeft = aabb->getPosition();
	const glm::vec2 botLeft = glm::vec2(topLeft.x, topLeft.y + boxHeight);
	const glm::vec2 topRight = glm::vec2(topLeft.x + boxWidth, topLeft.y);
	const glm::vec2 botRight = glm::vec2(topLeft.x + boxWidth, topLeft.y + boxHeight);

	//To detect collision between any rectangle (not just an AABB) and a circle, we do 2 checks:

	//1. is the Circle's origin contained within the rectangle?
	if (isContained(circlePos, aabb)) return true;

	//2. find the minimum distance from each edge of the rectangle to the circle. If at any point this distance is less than the radius of the circle, it is colliding

	//The condition we usually use for circle checks is "length(separationVector) < radius ==> colliding" 
	//But we want to allow scaling so we have something like "length(separationVector) < x*radius ==> colliding" where x is some scale, and these are all scalar quantities
	//But if we scale the circle in a non-uniform way we now have to think about distance on x and y, and the radius is different in different directions!
	//But we can't scale a radius on x and y separately... so we move the scale to the other side instead "length(scale * separationVector) < radius ==> colliding" where scale and displacement are both vectorsm but length() converts to scalar to compare with the radius

	//// left side
	glm::vec2 toLeft = separationVector(circlePos, topLeft, topLeft);
	//We divide the separation vector by the scale to apply the non-uniform scaling of the circle. This way, if the circle is 2x taller, the separation vector is halved before being compared to the radius of the circle
	toLeft /= circle->getScale();

	// do the same for the other sides...

	//// top
	glm::vec2 toTop = separationVector(circlePos, topLeft, topRight);
	toTop /= circle->getScale();

	//// right
	glm::vec2 toRight = separationVector(circlePos, topRight, botRight);
	toRight /= circle->getScale();

	//// bottom
	glm::vec2 toBottom = separationVector(circlePos, botLeft, botRight);
	toBottom /= circle->getScale();

	//Then we can perform the same distance check we would do with a normal unscaled circle-AABB

	if (Util::squaredMagnitude(toTop) < radiusSq ||
		Util::squaredMagnitude(toRight) < radiusSq ||
		Util::squaredMagnitude(toBottom) < radiusSq ||
		Util::squaredMagnitude(toLeft) < radiusSq)
	{
		return true;
	}

	// If we passed all those checks, they are not colliding
	return false;
}

bool CollisionManager::isColliding(ColliderAABB* object1, ColliderCircle* object2)
{
	return isColliding(object2, object1); //AABB-Circle is the same thing as Circle-AABB but reversed
}

bool CollisionManager::isColliding(ColliderAABB* object1, ColliderAABB* object2)
{
	const auto p1 = object1->getPosition();
	const auto p2 = object2->getPosition();

	const float p1Width = object1->m_size.x * object1->getScale().x;
	const float p1Height = object1->m_size.y * object1->getScale().y;
	const float p2Width = object2->m_size.x * object1->getScale().x;
	const float p2Height = object2->m_size.y * object1->getScale().y;

	if (
		p1.x < p2.x + p2Width &&
		p1.x + p1Width > p2.x&&
		p1.y < p2.y + p2Height &&
		p1.y + p1Height > p2.y
		)
	{
		return true;
	}
	else return false;
}

bool CollisionManager::isContained(glm::vec2 point, ColliderAABB* collider)
{
	return pointAABBCheck(point, collider->getPosition(), collider->m_size.x * collider->getScale().x, collider->m_size.y * collider->getScale().y);
}

bool CollisionManager::isContained(glm::vec2 point, ColliderCircle* collider)
{
	glm::vec2 circleToPoint = point - collider->getPosition();
	circleToPoint /= collider->getScale(); // transform/distort into a common space so that we can do the usual circle check on this scaled circle (which may be an oval due to scaling)

	if (isnan(circleToPoint)) // check if divide by zero
	{
		return false; // cannot collide with a zero-scale collider
	}

	return Util::squaredMagnitude(circleToPoint) < collider->m_radius * collider->m_radius;
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

	if (point.x > rect_start.x&&
		point.x < rect_start.x + width &&
		point.y > rect_start.y&&
		point.y < rect_start.y + height)
	{
		return true;
	}
	return false;
}


bool CollisionManager::pointAABBCheckCentered(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const auto width = rect_width / 2;
	const auto height = rect_height / 2;

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
