#include "PressurePlate.h"
#include "../src/SoundManager.h"
#include "../src/TextureManager.h"

PressurePlate::PressurePlate() {

	TextureManager::Instance()->load("../Assets/textures/pressure_plate.png", "PressurePlate");
	TextureManager::Instance()->getTextureSize("PressurePlate");
	SetWidth(140.0f);
	SetHeight(146.0f);
	GetTransform()->position = glm::vec2(167.0f, 146.0f);
	GetRigidBody()->isColliding = false;
	SetType(PRESSURE_PLATE);

	//For Joshi
	//SoundManager::Instance().load();
}

PressurePlate::~PressurePlate()
= default;

void PressurePlate::Draw() {
	TextureManager::Instance()->draw("PressurePlate", GetTransform()->position.x, GetTransform()->position.y, 0, 250, true);
}

void PressurePlate::Update() {

}

void PressurePlate::Clean() {

}