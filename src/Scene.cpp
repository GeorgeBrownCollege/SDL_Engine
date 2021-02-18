#include "Scene.h"

#include <algorithm>

#include "DisplayObject.h"

Scene::Scene()
= default;

Scene::~Scene() {
	RemoveAllChildren();
}

void Scene::AddChild(DisplayObject * _child, uint32_t _layerIndex, std::optional<uint32_t> _orderIndex) {

	uint32_t index = 0;
	// If we passed in an order index, override the auto-increment value
	if (_orderIndex.has_value()) {
		index = _orderIndex.value();
	}
	// If we did not pass in an order index, generate one for them
	else {
		index = m_nextLayerIndex++;
	}
	_child->SetLayerIndex(_layerIndex, index);
	_child->m_pParentScene = this;
	m_displayList.push_back(_child);
}

void Scene::RemoveChild(DisplayObject * _child) {

	delete _child;
	m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), _child), m_displayList.end());
}

void Scene::RemoveAllChildren() {

	for (auto &count : m_displayList) {

		delete count;
		count = nullptr;
	}

	m_displayList.clear();
}


int Scene::NumberOfChildren() const {
	return m_displayList.size();
}

bool Scene::sortObjects(DisplayObject * left, DisplayObject * right) {

	/*
	 * First check if they have the same enabled status, if they have the same enabled status,
	 * we first check to see if they're on the same layer, if they are then we sort by layer order index,
	 * otherwise we simply sort by layer index
	 * If they do not have the same enabled status, one is true and one is false, so if left is true, it gets
	 * sorted first, otherwise right is true and it goes first
	 * This will effectively sort by layer indices, and move disabled elements to the end of the list
	 */
	return
		(left->IsEnabled() == right->IsEnabled()) ?
		(left->m_layerIndex == right->m_layerIndex ?
		 left->m_layerOrderIndex < right->m_layerOrderIndex :
		 left->m_layerIndex < right->m_layerIndex) :
		left->IsEnabled();
}

void Scene::UpdateDisplayList() {

	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto &count : m_displayList) {
		if (count != nullptr) {
			if (!count->IsEnabled())
				break;
			count->Update();
		}
	}
}

void Scene::DrawDisplayList() {

	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto &count : m_displayList) {
		if (count != nullptr) {
			if (!count->IsEnabled())
				break;
			count->Draw();
		}
	}
}

void Scene::TickGravity() { 

	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto &count : m_displayList) { 
		if (count != nullptr) { 
			if (!count->IsEnabled())
				break;
			if (count->GetRigidBody()->hasGravity)
				count->GetRigidBody()->velocity.y += m_gravityForce;
		}
	}
}
