#pragma once
#ifndef __PLANE_SPRITE__
#define __PLANE_SPRITE__

#include "Sprite.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();
};

#endif /* defined (__PLANE__SPRITE__) */
