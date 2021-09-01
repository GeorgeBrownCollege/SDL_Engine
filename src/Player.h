#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

/*
 *Player Class inherits from Sprite which inherits from Display Object 
 *which inherits from GameObject. Player Class inherits from Sprite
 *to access Sprites Animation functions. If Player Class is not animated
 *then Player can inherit from DisplayObject which is used for non animated
 *images. In the DisplayObject Class you have to use the TextureManager to show a
 *still image. Player has the m_buildAnimations function which you
 *can create animations in. First you must use the Singleton
 *TextureManager Class function loadSpriteSheet to set the
 *spritesheet .txt file which slices the the spritesheet .png which
 *is also loaded along with the name you give the spritesheet. Next
 *you call setSpriteSheet function from the Sprite Class  in the constructor to
 *set the spritesheet just created in the TextureManager using the
 *TextureManager getter getSpriteSheet and pass it the name of the spritesheet.
 *After that everything is set up to add new Animation Class objects the Sprite Class
 *SpriteSheet object from the SpriteSheet Class.
 */

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */