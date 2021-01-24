#include "DisplayObject.h"

DisplayObject::DisplayObject()
= default;

DisplayObject::~DisplayObject()
= default;

Scene *DisplayObject::GetParent() const {
	return m_pParentScene;
}

void DisplayObject::SetParent(Scene * _parent) {
	m_pParentScene = _parent;
}

uint32_t DisplayObject::GetLayerIndex() const {
	return m_layerIndex;
}
uint32_t DisplayObject::GetLayerOrderIndex() const {
	return m_layerOrderIndex;
}

void DisplayObject::SetLayerIndex(const uint32_t _newIndex, const uint32_t _newOrder) {
	m_layerIndex = _newIndex;
	m_layerOrderIndex = _newOrder;
}
