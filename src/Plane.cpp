#include "Plane.h"
#include "TextureManager.h"

Plane::Plane()
{
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("spritesheet"));

	// set frame width
	SetWidth(65);

	// set frame height
	SetHeight(65);

	GetTransform()->position = glm::vec2(400.0f, 200.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PLANE);

	BuildAnimations();
}

Plane::~Plane()
= default;

void Plane::Draw()
{
	// draw the plane sprite with simple propeller animation
	TextureManager::Instance().PlayAnimation("spritesheet", GetAnimation("plane"),
		GetTransform()->position, 0.5f, 0, 255, true);
}

void Plane::Update()
{
}

void Plane::Clean()
{
}

void Plane::BuildAnimations()
{
	auto plane_animation = Animation();

	plane_animation.name = "plane";
	plane_animation.frames.push_back(GetSpriteSheet()->GetFrame("plane1"));
	plane_animation.frames.push_back(GetSpriteSheet()->GetFrame("plane2"));
	plane_animation.frames.push_back(GetSpriteSheet()->GetFrame("plane3"));

	SetAnimation(plane_animation);
}