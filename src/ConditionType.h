#pragma once
#ifndef __CONDITION_TYPE__
#define __CONDITION_TYPE__

enum class ConditionType
{
	HAS_LOS,
	LOW_HEALTH,
	TARGET_DETECTED,
	WITHIN_MELEE,
	WITHIN_RADIUS,
	WITHIN_RANGE,
	NUM_OF_CONDITIONS
};
#endif /* defined (__CONDITION_TYPE__) */