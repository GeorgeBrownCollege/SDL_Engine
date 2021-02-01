#pragma once
#ifndef __PRESSUREPLATE__
#define __PRESSUREPLATE__

#include "DisplayObject.h"

using namespace std;

class PressurePlate final : public DisplayObject
{
public:
	PressurePlate();   // Constructor
	~PressurePlate();  // Destructor

	void Draw() override;
	void Update() override;
	void Clean() override;
	
};
#endif

 