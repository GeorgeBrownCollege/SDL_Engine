#include "Scene.h"
#include "DisplayObject.h"

Scene::Scene()
= default;

Scene::~Scene()
{
	removeAllChildren();
}


void Scene::addChild(DisplayObject * child)
{
	m_displayList.push_back(child);
}

void Scene::removeAllChildren()
{
	for(auto child : m_displayList)
	{
		child = nullptr;
	}
	m_displayList.clear();
	m_displayList.resize(0);
	m_displayList.shrink_to_fit();
}


int Scene::numberOfChildren() const
{
	return m_displayList.size();
}

void Scene::updateDisplayList()
{
	for (auto displayObject : m_displayList)
	{
		if(displayObject != nullptr)
		{
			displayObject->update();
		}
		
	}
}

void Scene::drawDisplayList()
{
	for (auto displayObject : m_displayList)
	{
		if (displayObject != nullptr)
		{
			displayObject->draw();
		}
	}
}
