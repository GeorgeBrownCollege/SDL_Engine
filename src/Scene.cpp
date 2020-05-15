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
	for (int count = 0; count < m_displayList.size(); ++count)
	{
		m_displayList[count] = nullptr;
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
	for (auto count = 0; count < m_displayList.size(); ++count)
	{
		if (m_displayList[count] != nullptr)
		{
			m_displayList[count]->update();
		}
	}	
}

void Scene::drawDisplayList()
{
	for (auto count = 0; count < m_displayList.size(); ++count)
	{
		if (m_displayList[count] != nullptr)
		{
			m_displayList[count]->draw();
		}
	}

}
