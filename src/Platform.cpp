#include "Platform.h"

#include "Util.h"

Platform::Platform(glm::vec2 position, int _width, int _height) {

	SetWidth(_width);
	SetHeight(_height);
}

Platform::~Platform() 
= default;

void Platform::Draw()  {
	Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight());
}

void Platform::Update()  {

}

void Platform::Clean()  {}
