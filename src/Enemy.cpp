#include "Enemy.h"

#include "SoundManager.h"
#include "TextureManager.h"

Enemy::Enemy() : m_currentAnimationState(ENEMY_IDLE_RIGHT) {
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/CatAtlas.txt",
		"../Assets/sprites/Cat-spriteSheet.png",
		"catsprite");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("catsprite"));

	// set frame width
	SetWidth(81);

	// set frame height
	SetHeight(64);

	GetTransform()->local_position = glm::vec2(600.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	GetRigidBody()->hasGravity = true;
	SetType(ENEMY);

	m_buildAnimations();
	
}

Enemy::~Enemy()
= default;

void Enemy::Draw() {
	// alias for x and y
	const auto x = GetTransform()->local_position.x;
	const auto y = GetTransform()->local_position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState) {
	case ENEMY_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("catsprite", GetAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case ENEMY_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("catsprite", GetAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case ENEMY_ROAM_RIGHT:
		TextureManager::Instance()->playAnimation("catsprite", GetAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case ENEMY_ROAM_LEFT:
		TextureManager::Instance()->playAnimation("catsprite", GetAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}

}

void Enemy::Update() { }

void Enemy::Clean() { }

void Enemy::setAnimationState(const EnemyAnimationState new_state) {
	m_currentAnimationState = new_state;
}

void Enemy::m_buildAnimations() {
	Animation idleAnimation = Animation();

	idleAnimation.m_name = "idle";
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-idle-0"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-idle-1"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-idle-2"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-idle-3"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-idle-4"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.m_name = "roam";
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-walk-0"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-walk-1"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-walk-2"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-walk-3"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("cat-walk-4"));

	setAnimation(runAnimation);
}