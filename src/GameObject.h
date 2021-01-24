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
	virtual void Draw() = 0;

	// Update the object
	virtual void Update() = 0;

	// remove anything that needs to be deleted
	virtual void Clean() = 0;

	// getters for common variables
	Transform *GetTransform();

	// getters and setters for physics properties
	RigidBody *GetRigidBody();

	// getters and setters for game object properties
	int GetWidth() const;
	int GetHeight() const;
	void SetWidth(int new_width);
	void SetHeight(int new_height);
	GameObjectType GetType() const;
	void SetType(GameObjectType new_type);

	void SetEnabled(bool state);
	bool IsEnabled() const;

	private:
	// transform component
	Transform m_transform;

	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;
	GameObjectType m_type;

	bool m_enabled;
};

#endif /* defined (__GAME_OBJECT__) */