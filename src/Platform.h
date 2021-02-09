#pragma once
#ifndef __PLATFORM__
#define __PLATFORM__

#include "DisplayObject.h"

class Platform final : public DisplayObject { 

	private:

	public:
	Platform(glm::vec2, int, int);
	~Platform();

	void Draw() override;
	void Update() override;
	void Clean() override;
};

#endif