#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
#include <string>

// enums
#include "GameObjectType.h"


class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	Transform* getTransform();

	// getters and setters for physics properties
	RigidBody* getRigidBody();
	
	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	void setWidth(int new_width);
	void setHeight(int new_height);
	GameObjectType getType() const;
	void setType(GameObjectType new_type);

private:
	// transform component
	Transform m_transform;
	
	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;
	GameObjectType m_type;
};

#endif /* defined (__GAME_OBJECT__) */