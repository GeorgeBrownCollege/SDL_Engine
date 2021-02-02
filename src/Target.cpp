#include "Target.h"
#include "TextureManager.h"


Target::Target() {
	TextureManager::Instance()->load("../Assets/textures/Circle.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	SetWidth(size.x);
	SetHeight(size.y);
	GetTransform()->position = glm::vec2(100.0f, 100.0f);
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetType(TARGET);
}

Target::~Target()
= default;

void Target::Draw() {
	// alias for x and y
	const auto x = GetTransform()->position.x;
	const auto y = GetTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Target::Update() {
	m_move();
	m_checkBounds();
}

void Target::Clean() { }

void Target::m_move() {
	GetTransform()->position = GetTransform()->position + GetRigidBody()->velocity * 5.0f;
}

void Target::m_checkBounds() { }

void Target::m_reset() { }
