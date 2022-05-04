#include "Obstacle.h"


#include "SoundManager.h"
#include "TextureManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance().Load("../Assets/textures/obstacle.png", "obstacle");

	auto size = TextureManager::Instance().GetTextureSize("obstacle");
	SetWidth(size.x);
	SetHeight(size.y);

	GetTransform()->position = glm::vec2(300.0f, 300.0f);

	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;

	SoundManager::Instance().Load("../Assets/audio/yay.ogg", "yay", SoundType::SOUND_SFX);
}

Obstacle::~Obstacle()
= default;

void Obstacle::Draw()
{
	TextureManager::Instance().Draw("obstacle",
		GetTransform()->position.x, GetTransform()->position.y, 0, 255, true);
}

void Obstacle::Update()
{
}

void Obstacle::Clean()
{
}
