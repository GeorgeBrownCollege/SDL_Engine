#include "GameObject.h"

GameObject::GameObject() :
	m_width(0), m_height(0), m_type(GameObjectType::NONE), m_enabled(true), m_visible(true)
{
}

GameObject::~GameObject()
= default;

Transform* GameObject::GetTransform()
{
	return &m_transform;
}

RigidBody* GameObject::GetRigidBody()
{
	return &m_rigidBody;
}

int GameObject::GetWidth() const
{
	return m_width;
}

int GameObject::GetHeight() const
{
	return m_height;
}

GameObjectType GameObject::GetType() const
{
	return m_type;
}

void GameObject::SetWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::SetHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::SetType(const GameObjectType new_type)
{
	m_type = new_type;
}

void GameObject::SetEnabled(const bool state)
{
	m_enabled = state;
}

bool GameObject::IsEnabled() const
{
	return m_enabled;
}

void GameObject::SetVisible(const bool state)
{
	m_visible = state;
}

bool GameObject::IsVisible() const
{
	return m_visible;
}
