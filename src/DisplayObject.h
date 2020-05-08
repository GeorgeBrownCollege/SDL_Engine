#pragma once
#ifndef __DISPLAY_OBJECT__
#define __DISPLAY_OBJECT__

#include "GameObject.h"
#include "Scene.h"

class DisplayObject : public GameObject
{
public:
	DisplayObject();
	virtual ~DisplayObject();

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	Scene* getParent() const;
	void setParent(Scene* parent);

private:
	Scene* m_pParentScene{};
};

#endif /* defined (__DISPLAY_OBJECT__) */
