#pragma once
#ifndef __PLANE_SPRITE__
#define __PLANE_SPRITE__

#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

class PlaneSprite : public DisplayObject
{
public:
	PlaneSprite();
	~PlaneSprite();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	
	void setAnimation(const Animation& animation);

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__PLANE__SPRITE__) */
