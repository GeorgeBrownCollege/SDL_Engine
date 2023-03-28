#pragma once
#ifndef __EDITOR_NODE__
#define __EDITOR_NODE__
#include "EditorNodeType.h"

#include <string>
#include <chrono>

struct EditorNode
{
	int id;
	EditorNodeType type;
	int pins[3];
	int specificType = -1;

	EditorNode(const EditorNodeType type): type(type)
	{
		id = static_cast<int>( std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		for (int i = 0; i < 3; ++i)
		{
			pins[i] = id + i + 1;
		}
	}
};

#endif /* defined (__EDITOR_NODE__) */