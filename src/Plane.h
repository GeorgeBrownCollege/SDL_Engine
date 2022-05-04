#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane() override;

	// Life Cycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

private:
	void BuildAnimations();
};

#endif /* defined (__PLANE__) */
