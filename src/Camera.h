#pragma once
#ifndef __CAMERA__
#define __CAMERA__

#include <vector>

#include "GameObject.h"
#include "DisplayObject.h"

class Camera : public GameObject {
	friend class DisplayObject;

	// Private member variables
	private:
	std::vector<DisplayObject *> m_children;

	// Private functions
	private:
	void SetGlobalPositions();
	void RemoveAllChildren();
	
	// Public functions
	public:

	Camera();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	void AddChild();
	void RemoveChild();

};

#endif