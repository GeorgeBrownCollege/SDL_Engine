#pragma once
#ifndef __NODE_LINK__
#define __NODE_LINK__

struct NodeLink
{
	int id;
	int start;
	int end;
	bool dirty_flag;
};

#endif /* defined (__NODE_LINK__) */