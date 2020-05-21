#pragma once
#include "CollisionShape.h"
#include "glm/vec3.hpp"
class GameObject;

class CollidableEmpty;
class CollidableLine;
class CollidableCircle;
class CollidableAABB;

// virtual class
class ICollidable
{
public:
	ICollidable();
	virtual ~ICollidable(); // virtual destructor is a MUST in any virtual class or else you will cause memory leaks in the child classes!

	// Collider-specific
	virtual ColliderShape getShape() const = 0;

	// unique collision implementations
	virtual bool isCollidingWith(CollidableLine* const other) const = 0;
	virtual bool isCollidingWith(CollidableCircle* const other) const = 0;
	virtual bool isCollidingWith(CollidableAABB* const other) const = 0;

	//minimum translation vector, i.e. what would i have to translate my shape by such that it is no longer colliding with the shape other
	virtual glm::vec3 mtv(SphereCollider* const other) const = 0;
	virtual glm::vec3 mtv(CapsuleCollider* const other) const = 0;

protected:
	GameObject owner; // which gameObject does this Collider belong to?
};
