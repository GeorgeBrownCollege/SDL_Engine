#include "Scene.h"

#include <algorithm>

#include "DisplayObject.h"

Scene::Scene()
= default;

Scene::~Scene()
{
	RemoveAllChildren();
}


void Scene::AddChild(DisplayObject * child, uint32_t layer_index, std::optional<uint32_t> order_index)
{
	uint32_t index = 0;
	// If we passed in an order index, override the auto-increment value
	if (order_index.has_value())
	{
		index = order_index.value();
	}
	// If we did not pass in an order index, generate one for them
	else
	{
		index = m_nextLayerIndex++;
	}
	child->SetLayerIndex(layer_index, index);
	child->m_pParentScene = this;
	m_displayList.push_back(child);
}

void Scene::RemoveChild(DisplayObject * child)
{
	delete child;
	m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), child), m_displayList.end());
}

void Scene::RemoveAllChildren()
{
	for (auto& count : m_displayList)
	{
		delete count;
		count = nullptr;
	}

	m_displayList.clear();
}


int Scene::NumberOfChildren() const
{
	return m_displayList.size();
}

bool Scene::SortObjects(DisplayObject * left, DisplayObject * right)
{
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

void Scene::UpdateDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), SortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (!display_object->IsEnabled())
				break;
			display_object->Update();
		}
	}
}

void Scene::DrawDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), SortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (display_object->IsEnabled() && display_object->IsVisible())
			{
				display_object->Draw();
			}

		}
	}

}

std::vector<DisplayObject*> Scene::GetDisplayList() const
{
	return m_displayList;
}
