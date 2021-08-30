#pragma once
#ifndef __ANIMATION__
#define __ANIMATION__
#include "Frame.h"
#include <vector>

/*
 * A struct used by the Sprite Class to hold the data for one animation
 */
struct Animation
{
	std::string name; //name 
	std::vector<Frame> frames; // 
	int current_frame = 0;
};

#endif /* defined (__ANIMATION__) */