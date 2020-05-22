//This is a "pure virtual" class (may also called an interface), meaning it cannot be instantiated and is meant to be inherited from. 
//It mostly describes a list of function that all inheritors must implement. It has a data member all Colliders share, as well as a functions they all share.
//This allows a group of classes to follow the same conventions and have a common pool of functions. 
//Then, you can hold a base class reference to the generic type Collider and the child classes can implement their own unique behaviours for each function
//In this case, it allows you to hold a reference to Collider, which allows it to be changed to any type of Collider that implements the Collider interface.
//To learn more, see https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm

#pragma once
#ifndef __Collider__
#define __Collider__

#include "glm/vec2.hpp"

#include "Transform.h"

enum EnumColliderShape;

//Pure virtual class
class Collider
{
public:
	Collider(Transform* const ownerTransform, glm::vec2 anchor);
	virtual ~Collider() {}; // virtual destructor is a MUST in any virtual class or else you will cause memory leaks in the inheriting classes!

	// describes the origin of this collider as an offset from the GameObject
	glm::vec2 m_anchor;

	// Collider-specific function to determine what shape it is
	//virtual EnumColliderShape getShape() const = 0; // = 0 means "pure virtual", so every function that 

	//returns a mutable copy of the owner's transform
	Transform getTransformCopy() const { return Transform (*m_pTransform); }

	//returns a reference to the actual transform
	Transform& const getTransformRef() const { return *m_pTransform; }

	//returns collider position (offset by anchor, then scaled)
	glm::vec2 getPosition() const { return (m_pTransform->position + m_anchor) * m_pTransform->scale; }
	glm::vec2 getScale() const { return m_pTransform->scale; }

protected:
	// Each Collider holds a pointer to the Transform of the object it belongs to
	Transform* m_pTransform;
};

#endif