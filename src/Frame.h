#pragma once
#ifndef __FRAME__
#define __FRAME__
#include <string>

/*
 * Frame is a struct that holds the needed data
 * for one frame sliced out of a sprite sheet.
 */

struct Frame
{
	std::string name;
	int x;
	int y;
	int w;
	int h;
};

#endif /* defined (__FRAME__) */