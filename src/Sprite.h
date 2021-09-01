#pragma once
#ifndef __SPRITE__
#define __SPRITE__

#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

/*
 *The Class Sprite is used to inherit from if the the child class needs animation.
 *If it doesn't need animation you can directly inherit from the DisplayObject Class
 *which inherits from the GameObject Class. If you do only use DisplayObject you must use the
 *TextureManager directly to display the image. The Class Sprite has getters and setters
 *to set and get animations.
 */

class Sprite : public DisplayObject
{
public:
	Sprite();
	virtual ~Sprite();
	
	// Life Cycle Functions
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	// getters
	SpriteSheet* getSpriteSheet();
	Animation& getAnimation(const std::string& name);
	
	// setters
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);
private:
	// private utility functions
	bool m_animationExists(const std::string& id);

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__SPRITE__) */