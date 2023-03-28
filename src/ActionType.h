#pragma once
#ifndef __ACTION_TYPE__
#define __ACTION_TYPE__

enum class ActionType
{
	FLEE,
	MELEE_ATTACK,
	MOVE_TO_COVER,
	MOVE_TO_LOS,
	MOVE_TO_RANGE,
	MOVE_TO_TARGET,
	PATROL,
	RANGED_ATTACK,
	WAIT_IN_COVER,
	NUM_OF_ACTIONS
};
#endif /* defined (__ACTION_TYPE__) */