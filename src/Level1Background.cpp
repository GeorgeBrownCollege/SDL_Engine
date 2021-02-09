#include "TextureManager.h"
#include "Level1Background.h"
#include "Target.h"

Background::Background() {
	TextureManager::Instance()->load("../Assets/textures/background_mark_1.png", "background");

	const auto size = TextureManager::Instance()->getTextureSize("background");
	SetWidth(1080);
	SetHeight(584);
	GetTransform()->local_position = glm::vec2(0, 0);
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
}

Background::~Background()
= default;

void Background::Draw() {

	// draw the target
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false);
}
void Background::Update() {
	m_move();
	m_checkBounds();
}

void Background::Clean() { }

void Background::m_move() {
	GetTransform()->local_position = GetTransform()->local_position + GetRigidBody()->velocity * 5.0f;
}

void Background::m_checkBounds() { }

void Background::m_reset() { }