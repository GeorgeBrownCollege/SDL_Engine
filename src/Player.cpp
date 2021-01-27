#include "Player.h"
#include "TextureManager.h"

Player::Player() : m_currentAnimationState(PLAYER_IDLE_RIGHT) {
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/dog-spritesheet.png",
		"dogsprite");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("dogsprite"));

	// set frame width
	SetWidth(87);

	// set frame height
	SetHeight(58);

	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::Draw() {
	// alias for x and y
	const auto x = GetTransform()->position.x;
	const auto y = GetTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState) {
		case PLAYER_IDLE_RIGHT:
			TextureManager::Instance()->playAnimation("dogsprite", GetAnimation("idle"),
													  x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
			break;
		case PLAYER_IDLE_LEFT:
			TextureManager::Instance()->playAnimation("dogsprite", GetAnimation("idle"),
													  x, y, 0.12f, 0, 255, true);
			break;
		case PLAYER_RUN_RIGHT:
			TextureManager::Instance()->playAnimation("dogsprite", GetAnimation("run"),
													  x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
			break;
		case PLAYER_RUN_LEFT:
			TextureManager::Instance()->playAnimation("dogsprite", GetAnimation("run"),
													  x, y, 0.25f, 0, 255, true);
			break;
		default:
			break;
	}

}

void Player::Update() { }

void Player::Clean() { }

void Player::setAnimationState(const PlayerAnimationState new_state) {
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations() {
	Animation idleAnimation = Animation();

	idleAnimation.m_name = "idle";
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-0"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-1"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-2"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-3"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-4"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-5"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-idle-6"));
	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.m_name = "run";
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-dash-0"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-dash-1"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-dash-2"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-dash-3"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("dog-dash-4"));

	setAnimation(runAnimation);
}
