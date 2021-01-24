#include "ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Ship::Ship() : m_maxSpeed(10.0f) {
	TextureManager::Instance()->load("../Assets/textures/ship3.png", "ship");

	auto size = TextureManager::Instance()->getTextureSize("ship");
	SetWidth(size.x);
	SetHeight(size.y);

	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(SHIP);

	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame
}


Ship::~Ship()
= default;

void Ship::Draw() {
	// alias for x and y
	const auto x = GetTransform()->position.x;
	const auto y = GetTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("ship", x, y, m_currentHeading, 255, true);
}


void Ship::Update() {
	move();
	m_checkBounds();
}

void Ship::Clean() { }

void Ship::turnRight() {
	m_currentHeading += m_turnRate;
	if (m_currentHeading >= 360) {
		m_currentHeading -= 360.0f;
	}
	m_changeDirection();
}

void Ship::turnLeft() {
	m_currentHeading -= m_turnRate;
	if (m_currentHeading < 0) {
		m_currentHeading += 360.0f;
	}

	m_changeDirection();
}

void Ship::moveForward() {
	GetRigidBody()->velocity = m_currentDirection * m_maxSpeed;
}

void Ship::moveBack() {
	GetRigidBody()->velocity = m_currentDirection * -m_maxSpeed;
}

void Ship::move() {
	GetTransform()->position += GetRigidBody()->velocity;
	GetRigidBody()->velocity *= 0.9f;
}

glm::vec2 Ship::getTargetPosition() const {
	return m_targetPosition;
}

glm::vec2 Ship::getCurrentDirection() const {
	return m_currentDirection;
}

float Ship::getMaxSpeed() const {
	return m_maxSpeed;
}

void Ship::setTargetPosition(glm::vec2 newPosition) {
	m_targetPosition = newPosition;

}

void Ship::setCurrentDirection(glm::vec2 newDirection) {
	m_currentDirection = newDirection;
}

void Ship::setMaxSpeed(float newSpeed) {
	m_maxSpeed = newSpeed;
}



void Ship::m_checkBounds() {

	if (GetTransform()->position.x > Config::SCREEN_WIDTH) {
		GetTransform()->position = glm::vec2(0.0f, GetTransform()->position.y);
	}

	if (GetTransform()->position.x < 0) {
		GetTransform()->position = glm::vec2(800.0f, GetTransform()->position.y);
	}

	if (GetTransform()->position.y > Config::SCREEN_HEIGHT) {
		GetTransform()->position = glm::vec2(GetTransform()->position.x, 0.0f);
	}

	if (GetTransform()->position.y < 0) {
		GetTransform()->position = glm::vec2(GetTransform()->position.x, 600.0f);
	}

}

void Ship::m_reset() {
	GetRigidBody()->isColliding = false;
	const int halfWidth = GetWidth() * 0.5f;
	const auto xComponent = rand() % (640 - GetWidth()) + halfWidth + 1;
	const auto yComponent = -GetHeight();
	GetTransform()->position = glm::vec2(xComponent, yComponent);
}

void Ship::m_changeDirection() {
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}

