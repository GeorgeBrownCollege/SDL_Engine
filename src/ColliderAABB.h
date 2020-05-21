#pragma once
#ifndef __ColliderAABB__
#define __ColliderAABB__

#include "../src/Collider.h"

class ColliderAABB :
	public Collider
{
public:
	ColliderAABB(Transform* const owner, glm::vec2 anchor, glm::vec2 size) :Collider(owner, anchor), m_size(size) {};
	~ColliderAABB() override {};

	glm::vec2 m_size;
};

#endif




//EnumColliderShape getShape() const override; // The optional 'override' keyword says that this class implements a function which was abstract in its parent class. It will produce an error if the function is somehow unimplemented to let you know there's a bug

//bool isCollidingWith(ColliderLine* const other) const override;
//bool isCollidingWith(ColliderCircle* const other) const override;
//bool isCollidingWith(ColliderAABB* const other) const override;