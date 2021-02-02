#include "UIControl.h"
#include "CollisionManager.h"
#include "EventManager.h"

UIControl::UIControl() :
	m_mouseOver(false), m_mouseOverActive(false), m_mouseOutActive(false), m_leftMouseButtonClicked(false) { }

UIControl::~UIControl()
= default;

bool UIControl::AddEventListener(const Event _event, const EventHandler & _handler) {
	if (m_eventExists(_event)) {
		return false;
	}

	m_events[_event] = _handler;
	return true;
}

UIControl::EventHandler UIControl::GetEventHandler(Event _event) {
	return m_events[_event];
}

void UIControl::OnMouseOver() {

	const auto mousePosition = EventManager::Instance().getMousePosition();

	if (CollisionManager::pointRectCheck(mousePosition, GetTransform()->position, GetWidth(), GetHeight())) {
		m_mouseOver = true;
	} else {
		m_mouseOver = false;
	}

	if ((m_events[MOUSE_OVER]) && (!m_mouseOverActive)) {
		if (m_mouseOver) {
			m_events[MOUSE_OVER]();
			m_mouseOverActive = true;
		}
	} else if ((m_events[MOUSE_OVER]) && (!m_mouseOver)) {
		m_mouseOverActive = false;
	}
}

void UIControl::OnMouseOut() {

	if ((m_events[MOUSE_OUT]) && (m_mouseOutActive) && (!m_mouseOver)) {
		m_events[MOUSE_OUT]();
		m_mouseOutActive = false;
	} else if ((m_events[MOUSE_OUT]) && (m_mouseOver)) {
		m_mouseOutActive = true;
	}
}

void UIControl::OnLeftMouseButtonClick() {

	if (EventManager::Instance().getMouseButton(LEFT)) {
		if ((m_events[CLICK]) && (m_mouseOver) && !m_leftMouseButtonClicked) {
			m_leftMouseButtonClicked = true;
			m_events[CLICK](); // call click event
			SoundManager::Instance().load("../Assets/audio/buttonClick1.wav", "buttonClick", SOUND_SFX);
			SoundManager::Instance().playSound("buttonClick", 0, 0);
			std::cout << "Button has been clicked." << std::endl;
		}
	} else {
		m_leftMouseButtonClicked = false;
	}
}

bool UIControl::m_eventExists(Event _id) {
	return m_events.find(_id) != m_events.end();
}
