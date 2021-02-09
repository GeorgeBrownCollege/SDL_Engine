#pragma once
#ifndef __CAMERA__
#define __CAMERA__

#include <vector>

#include "GameObject.h"

class Camera : public GameObject {
	friend class DisplayObject;

	private:
	std::vector<DisplayObject *> m_children;


	public:

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

};

#endif