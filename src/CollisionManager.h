#pragma once
#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

#include "glm/vec2.hpp"

class ColliderCircle;
class ColliderAABB;

static class CollisionManager
{
public:


	/////////// --- COLLISION DETECTION FUNCTIONS --- ///////////
	// These functions return whether or not colliders are touching, or if a line or point touches them. These incorporate the transformations of the objects the colliders are on, so if you scale an object, you scale its collision too.
	// They do not provide collision response (i.e. it does not push them apart so they do not collide)
	// The CollisionManager takes advantage of polymorphism which automatically choose which collision detection function to call - (http://www.cplusplus.com/doc/tutorial/polymorphism/) 

	//Circle-Circle
	static bool isColliding(ColliderCircle* object1, ColliderCircle* object2);

	//Circle-AABB
	static bool isColliding(ColliderCircle* object1, ColliderAABB* object2);
	static bool isColliding(ColliderAABB* object1, ColliderCircle* object2);

	//AABB-AABB
	static bool isColliding(ColliderAABB* object1, ColliderAABB* object2);




	/////////// --- SIMPLE COLLIDER-LESS CHECKS --- ///////////
	//// no Colliders therefore no anchors or transformations

	//Line-Line
	static bool lineLineCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);

	//Line-Circle
	static bool lineCircleCheck(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 circle_center, float circle_radius);

	//Line-AABB
	static bool lineAABBCheck(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 rec_start, float rect_width, float rect_height);

	//Point-Line?
	static bool pointLineCheck(glm::vec2 point, glm::vec2 line_start, glm::vec2 line_end);

	//Point-Circle
	static bool pointCircleCheck(glm::vec2 point, glm::vec2 circle_center, float circle_radius);

	//Point-AABB
	static bool pointAABBCheck(glm::vec2 point, glm::vec2 rect_start, float rect_width, float rect_height);

	//Point-AABB where the position of the rect is the middle
	static bool pointAABBCheckCentered(glm::vec2 point, glm::vec2 rect_start, float rect_width, float rect_height);



	// other utilities
	static inline float squaredDistance(glm::vec2 p1, glm::vec2 p2);
	static int minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);
	static int circleAABBsquaredDistance(glm::vec2 circle_centre, float circle_radius, glm::vec2 box_start, const float box_width, const float box_height);


	static glm::vec2 separationVector(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end);
	static float distanceToLine(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end);
	static float distanceToLineSq(const glm::vec2& point, const glm::vec2& line_start, const glm::vec2& line_end);

private:
	CollisionManager();
	~CollisionManager();
};

#endif /* defined (__COLLISION_MANAGER__) */