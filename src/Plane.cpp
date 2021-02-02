#include "Plane.h"
#include "TextureManager.h"

Plane::Plane() {
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	SetWidth(65);

	// set frame height
	SetHeight(65);

	GetTransform()->position = glm::vec2(400.0f, 200.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(PLANE);

	m_buildAnimations();
}

Plane::~Plane()
= default;

void Plane::Draw() {
	// alias for x and y
	const auto x = GetTransform()->position.x;
	const auto y = GetTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", GetAnimation("plane"),
		x, y, 0.5f, 0, 255, true);
}

void Plane::Update() { }

void Plane::Clean() { }

void Plane::m_buildAnimations() {
	Animation planeAnimation = Animation();

	planeAnimation.m_name = "plane";
	planeAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("plane1"));
	planeAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("plane2"));
	planeAnimation.m_frames.push_back(GetSpriteSheet()->GetFrame("plane3"));

	setAnimation(planeAnimation);
}