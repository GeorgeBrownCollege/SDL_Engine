#include "Sprite.h"

Sprite::Sprite() { }

Sprite::~Sprite()
= default;

SpriteSheet *Sprite::GetSpriteSheet() {
	return m_pSpriteSheet;
}

Animation &Sprite::GetAnimation(const std::string &_name) {
	return m_pAnimations[_name];
}

void Sprite::setSpriteSheet(SpriteSheet *_spriteSheet) {
	m_pSpriteSheet = _spriteSheet;
}

void Sprite::setAnimation(const Animation &_anim) {

	if (!m_animationExists(_anim.m_name)) {
		m_pAnimations[_anim.m_name] = _anim;
	}
}

bool Sprite::m_animationExists(const std::string &_id) {
	return m_pAnimations.find(_id) != m_pAnimations.end();
}