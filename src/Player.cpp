#include "Player.h"
#include <iostream>
#include "EventManager.h"
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
	SetAccelerationRate(1.0f);
	SetMaxSpeed(8.25f);

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

void Player::Update() {

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) {

		Move(false);

	} else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)) {

		Move(true);

	} else {

		Decellerate();
	}

}

void Player::Clean() { }

// Setters
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

	//std::string tmp_str = "dog-idle-";
	//for (int i = 0; i < 7; i++) 
	//	idleAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame(tmp_str + std::to_string(i)));

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

void Player::Move(bool _direction) {

	GetRigidBody()->acceleration.x = m_accelerationRate;

	if (GetRigidBody()->velocity.x != 0)
		GetRigidBody()->velocity.x = abs(GetRigidBody()->velocity.x) + 0.5f * GetRigidBody()->acceleration.x;
	else
		GetRigidBody()->velocity.x = 0.5f * GetRigidBody()->acceleration.x;

	// If the player wants to move left the velocity will be turned into a negative
	if (_direction == false)
		GetRigidBody()->velocity.x *= -1;

	// if the absolute value of the new velocity is greater than the max speed the velocity will be set to the max speed in the proper direction
	abs(GetRigidBody()->velocity.x) < m_maxSpeed ? GetRigidBody()->velocity.x = GetRigidBody()->velocity.x :
		_direction == false ? GetRigidBody()->velocity.x = -m_maxSpeed : GetRigidBody()->velocity.x = m_maxSpeed;

	GetTransform()->position += GetRigidBody()->velocity;
}

void Player::Decellerate() {

	float decellerateRate = 0.2f;

	if (GetRigidBody()->velocity.x != 0) {
		if (GetRigidBody()->velocity.x < 1.0f && GetRigidBody()->velocity.x > -1.0f)
			GetRigidBody()->velocity.x = 0.0f;

		// If the player's velocity is not equal to zero, it's velocity will be decreased until it's zero
		GetRigidBody()->velocity.x == 0
			? GetRigidBody()->velocity.x == GetRigidBody()->velocity.x
			: GetRigidBody()->velocity.x < 0
			? GetRigidBody()->velocity.x += abs(GetRigidBody()->velocity.x * decellerateRate)
			: GetRigidBody()->velocity.x -= abs(GetRigidBody()->velocity.x * decellerateRate);

		GetTransform()->position += GetRigidBody()->velocity;
	}
}

// Setters
void Player::SetAccelerationRate(float _accel) { m_accelerationRate = _accel; }
void Player::SetMaxSpeed(float _speed) { m_maxSpeed = _speed; }

// Getters
float Player::GetAcceleration() { return m_accelerationRate; }
float Player::GetMaxSpeed() { return m_maxSpeed; }