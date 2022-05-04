#include "ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Ship::Ship() : m_maxSpeed(10.0f)
{
	TextureManager::Instance().Load("../Assets/textures/ship3.png", "ship");

	auto size = TextureManager::Instance().GetTextureSize("ship");
	SetWidth(size.x);
	SetHeight(size.y);

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
	// alias for x and y
	const auto x = GetTransform()->position.x;
	const auto y = GetTransform()->position.y;

	// draw the ship
	TextureManager::Instance().Draw("ship", x, y, GetCurrentHeading(), 255, true);

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

void Ship::turnRight()
{
	SetCurrentHeading(GetCurrentHeading() + m_turnRate);
	if (GetCurrentHeading() >= 360)
	{
		SetCurrentHeading(GetCurrentHeading() - 360.0f);
	}
}

void Ship::turnLeft()
{
	SetCurrentHeading(GetCurrentHeading() - m_turnRate);
	if (GetCurrentHeading() < 0)
	{
		SetCurrentHeading(GetCurrentHeading() + 360.0f);
	}
}

void Ship::moveForward()
{
	GetRigidBody()->velocity = GetCurrentDirection() * m_maxSpeed;
}

void Ship::moveBack()
{
	GetRigidBody()->velocity = GetCurrentDirection() * -m_maxSpeed;
}

void Ship::move()
{
	GetTransform()->position += GetRigidBody()->velocity;
	GetRigidBody()->velocity *= 0.9f;
}

float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Ship::m_checkBounds()
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

void Ship::m_reset()
{
	GetRigidBody()->isColliding = false;
	const int halfWidth = GetWidth() * 0.5f;
	const auto xComponent = rand() % (640 - GetWidth()) + halfWidth + 1;
	const auto yComponent = -GetHeight();
	GetTransform()->position = glm::vec2(xComponent, yComponent);
}

