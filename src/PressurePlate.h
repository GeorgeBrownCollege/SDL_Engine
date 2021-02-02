#pragma once
#ifndef __PRESSUREPLATE__
#define __PRESSUREPLATE__

#include "DisplayObject.h"
#include "Sprite.h"

using namespace std;

class PressurePlate final : public Sprite
{
public:
	PressurePlate();   // Constructor
	~PressurePlate();  // Destructor

	void Draw() override;
	void Update() override;
	void Clean() override;
	
};
#endif

 