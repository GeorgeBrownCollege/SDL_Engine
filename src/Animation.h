#pragma once
#ifndef __ANIMATION__
#define __ANIMATION__
#include "Frame.h"
#include <vector>

struct Animation {

	std::string m_name;
	std::vector<Frame> m_frames;
	int m_currFrame = 0;
};

#endif /* defined (__ANIMATION__) */