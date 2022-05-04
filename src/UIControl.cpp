#include "UIControl.h"
#include "CollisionManager.h"
#include "EventManager.h"

UIControl::UIControl():
	m_mouseOver(false), m_mouseOverActive(false), m_mouseOutActive(false), m_leftMouseButtonClicked(false)
{
}

UIControl::~UIControl()
= default;

bool UIControl::AddEventListener(const Event event, const EventHandler& handler)
{
	if (CheckIfEventExists(event))
	{
		return false;
	}

	m_events[event] = handler;
	return true;
}

UIControl::EventHandler UIControl::GetEventHandler(const Event event)
{
	return m_events[event];
}

void UIControl::OnMouseOver()
{
	if (const auto mouse_position = EventManager::Instance().GetMousePosition(); 
		CollisionManager::PointRectCheck( mouse_position, GetTransform()->position, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()) ))
	{
		m_mouseOver = true;
	}
	else
	{
		m_mouseOver = false;
	}

	if ((m_events[Event::MOUSE_OVER]) && (!m_mouseOverActive))
	{
		if (m_mouseOver)
		{
			m_events[Event::MOUSE_OVER]();
			m_mouseOverActive = true;
		}
	}
	else if ((m_events[Event::MOUSE_OVER]) && (!m_mouseOver))
	{
		m_mouseOverActive = false;
	}
}

void UIControl::OnMouseOut()
{
	if ((m_events[Event::MOUSE_OUT]) && (m_mouseOutActive) && (!m_mouseOver))
	{
		m_events[Event::MOUSE_OUT]();
		m_mouseOutActive = false;
	}
	else if ((m_events[Event::MOUSE_OUT]) && (m_mouseOver))
	{
		m_mouseOutActive = true;
	}
}

void UIControl::OnLeftMouseButtonClick()
{
	if (EventManager::Instance().GetMouseButton(static_cast<int>(MouseButtons::LEFT)))
	{
		if ((m_events[Event::CLICK]) && (m_mouseOver) && !m_leftMouseButtonClicked)
		{
			m_leftMouseButtonClicked = true;
			m_events[Event::CLICK](); // call click event
		}
	}
	else
	{
		m_leftMouseButtonClicked = false;
	}
}

bool UIControl::CheckIfEventExists(const Event id)
{
	return m_events.find(id) != m_events.end();
}
