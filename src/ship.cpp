#include "Ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Ship::Ship() : m_maxSpeed(10.0f)
{
	TextureManager::Instance().Load("../Assets/textures/ship3.png", "ship");

	const auto size = TextureManager::Instance().GetTextureSize("ship");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::AGENT);

	SetCurrentHeading(0.0f);// current facing angle
	SetCurrentDirection(glm::vec2(1.0f, 0.0f)); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame

	SetLOSDistance(400.0f); // 5 ppf x 80 feet
	SetLOSColour(glm::vec4(1, 0, 0, 1));
}


Ship::~Ship()
= default;

void Ship::Draw()
{
	// draw the ship
	TextureManager::Instance().Draw("ship", GetTransform()->position, GetCurrentHeading(), 255, true);

	// draw LOS
	Util::DrawLine(GetTransform()->position, GetTransform()->position + GetCurrentDirection() * GetLOSDistance(), GetLOSColour());
}


void Ship::Update()
{
	/*move();
	m_checkBounds();*/
}

void Ship::Clean()
{
}

void Ship::TurnRight()
{
	SetCurrentHeading(GetCurrentHeading() + m_turnRate);
	if (GetCurrentHeading() >= 360)
	{
		SetCurrentHeading(GetCurrentHeading() - 360.0f);
	}
}

void Ship::TurnLeft()
{
	SetCurrentHeading(GetCurrentHeading() - m_turnRate);
	if (GetCurrentHeading() < 0)
	{
		SetCurrentHeading(GetCurrentHeading() + 360.0f);
	}
}

void Ship::MoveForward()
{
	GetRigidBody()->velocity = GetCurrentDirection() * m_maxSpeed;
}

void Ship::MoveBack()
{
	GetRigidBody()->velocity = GetCurrentDirection() * -m_maxSpeed;
}

void Ship::Move()
{
	GetTransform()->position += GetRigidBody()->velocity;
	GetRigidBody()->velocity *= 0.9f;
}

float Ship::GetMaxSpeed() const
{
	return m_maxSpeed;
}

void Ship::SetMaxSpeed(const float new_speed)
{
	m_maxSpeed = new_speed;
}

void Ship::CheckBounds()
{

	if (GetTransform()->position.x > Config::SCREEN_WIDTH)
	{
		GetTransform()->position = glm::vec2(0.0f, GetTransform()->position.y);
	}

	if (GetTransform()->position.x < 0)
	{
		GetTransform()->position = glm::vec2(800.0f, GetTransform()->position.y);
	}

	if (GetTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		GetTransform()->position = glm::vec2(GetTransform()->position.x, 0.0f);
	}

	if (GetTransform()->position.y < 0)
	{
		GetTransform()->position = glm::vec2(GetTransform()->position.x, 600.0f);
	}

}

void Ship::Reset()
{
	GetRigidBody()->isColliding = false;
	const int half_width = static_cast<int>(GetWidth() * 0.5);
	const auto x_component = rand() % (640 - GetWidth()) + half_width + 1;
	const auto y_component = -GetHeight();
	GetTransform()->position = glm::vec2(x_component, y_component);
}

