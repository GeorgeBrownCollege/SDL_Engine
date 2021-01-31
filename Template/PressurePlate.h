#pragma once
#ifndef __PRESSUREPLATE__
#define __PRESSUREPLATE__
#include "../src/DisplayObject.h"
using namespace std;

class Pressureplate final : public DisplayObject
{
public:
	Pressureplate();   // Constructor
	~Pressureplate();  // Destructor

	void Draw() override;
	void Update() override;
	void Clean() override;
	
};
#endif

 