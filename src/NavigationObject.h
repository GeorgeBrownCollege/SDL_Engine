#pragma once
#ifndef __NAVIGATION_OBJECT__
#define __NAVIGATION_OBJECT__
#include "DisplayObject.h"

class NavigationObject : public DisplayObject
{
public:
	// Constructor
	NavigationObject();
	
	// Destructor
	~NavigationObject() override;

	// Inherited from DisplayObject
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	// getters and setters
	[[nodiscard]] glm::vec2 GetGridPosition() const;
	void SetGridPosition(float col, float row);

private:
	glm::vec2 m_gridPosition;
};

#endif /* defined (__NAVIGATION_OBJECT__) */