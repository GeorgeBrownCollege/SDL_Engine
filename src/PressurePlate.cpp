#include "PressurePlate.h"
#include "../src/SoundManager.h"
#include "../src/TextureManager.h"

PressurePlate::PressurePlate() {

	TextureManager::Instance()->load("../Assets/textures/pressureplate.png", "PressurePlate");
	auto size = TextureManager::Instance()->getTextureSize("PressurePlate");
	SetWidth(size.x);
	SetHeight(size.y);
	GetTransform()->position = glm::vec2(100.0f, 300.0f);
	GetRigidBody()->isColliding = false;
	SetType(PRESSURE_PLATE);

	//For Joshi
	//SoundManager::Instance().load();
}

PressurePlate::~PressurePlate()
= default;

void PressurePlate::Draw() {
	TextureManager::Instance()->draw("Pressureplate", GetTransform()->position.x, GetTransform()->position.y, 0, 100, false);
}

void PressurePlate::Update() {

}

void PressurePlate::Clean() {

}