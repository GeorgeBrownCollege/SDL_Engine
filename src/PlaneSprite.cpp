#include "PlaneSprite.h"
#include "TextureManager.h"

PlaneSprite::PlaneSprite()
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
}

PlaneSprite::~PlaneSprite()
= default;

void PlaneSprite::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TheTextureManager::Instance()->playAnimation(
		"spritesheet", m_pAnimations["plane"],
		x, y, 0.5f, 0, 255, true);
}

void PlaneSprite::update()
{
}

void PlaneSprite::clean()
{
}

void PlaneSprite::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void PlaneSprite::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane1"));
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane2"));
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane3"));

	m_pAnimations["plane"] = planeAnimation;
}





