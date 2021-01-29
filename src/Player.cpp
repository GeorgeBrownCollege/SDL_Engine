#include "Player.h"
#include "TextureManager.h"

Player::Player() : m_currentAnimationState(PLAYER_IDLE_RIGHT) {
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	SetWidth(53);

	// set frame height
	SetHeight(58);

	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	GetRigidBody()->hasGravity = true;
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
			TextureManager::Instance()->playAnimation("spritesheet", GetAnimation("idle"),
													  x, y, 0.12f, 0, 255, true);
			break;
		case PLAYER_IDLE_LEFT:
			TextureManager::Instance()->playAnimation("spritesheet", GetAnimation("idle"),
													  x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
			break;
		case PLAYER_RUN_RIGHT:
			TextureManager::Instance()->playAnimation("spritesheet", GetAnimation("run"),
													  x, y, 0.25f, 0, 255, true);
			break;
		case PLAYER_RUN_LEFT:
			TextureManager::Instance()->playAnimation("spritesheet", GetAnimation("run"),
													  x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
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
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-0"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-1"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-2"));
	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.m_name = "run";
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-0"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-1"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-2"));
	runAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-3"));

	setAnimation(runAnimation);
}
