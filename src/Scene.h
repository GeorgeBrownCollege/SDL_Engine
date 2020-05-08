#pragma once
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include "GameObject.h"


class Scene : public GameObject
{
public:
	friend class DisplayObject;
	Scene();
	virtual ~Scene();

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;
	virtual void handleEvents() = 0;
	virtual void start() = 0;

	void addChild(DisplayObject* child);
	void removeAllChildren();
	int numberOfChildren() const;

	void updateDisplayList();
	void drawDisplayList();

private:
	std::vector<DisplayObject*> m_displayList;
};

#endif /* defined (__SCENE__) */
