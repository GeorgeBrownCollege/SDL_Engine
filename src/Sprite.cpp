#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
= default;

SpriteSheet* Sprite::GetSpriteSheet()
{
	return m_pSpriteSheet;
}

Animation& Sprite::GetAnimation(const std::string& name)
{
	return m_pAnimations[name];
}

void Sprite::SetSpriteSheet(SpriteSheet* sprite_sheet)
{
	m_pSpriteSheet = sprite_sheet;
}

void Sprite::SetAnimation(const Animation& animation)
{
	if(!CheckIfAnimationExists(animation.name))
	{
		m_pAnimations[animation.name] = animation;
	}
}

bool Sprite::CheckIfAnimationExists(const std::string& id)
{
	return m_pAnimations.find(id) != m_pAnimations.end();
}