#include "PressurePlate.h"
#include "../src/SoundManager.h"
#include "../src/TextureManager.h"

Pressureplate::Pressureplate()
{
	TextureManager::Instance()->load("../Assets/textures/pressureplate.png", "Pressureplate");
	auto size = TextureManager::Instance()->getTextureSize("Pressureplate");
	SetWidth(size.x);
	SetHeight(size.y);
	GetTransform()->position = glm::vec2(100.0f, 100.0f);
	GetRigidBody()->isColliding = false;

	//For Joshi
	//SoundManager::Instance().load();
}

Pressureplate::~Pressureplate()
= default;

void Pressureplate::Draw()
{
	TextureManager::Instance()->draw("Pressureplate", GetTransform()->position.x, GetTransform()->position.y, 0, 100, false);
}

void Pressureplate::Update()
{
	
}

void Pressureplate::Clean()
{

}



