#pragma once

#include "SDK.h"
#include "stdafx.h"

struct FireBulletData
{
	FireBulletData(const ValveSDK::Vector &eye_pos)
		: src(eye_pos)
	{
	}

	ValveSDK::Vector           src;
	ValveSDK::IEngineTrace::trace_t          enter_trace;
	ValveSDK::Vector           direction;
	ValveSDK::IEngineTrace::CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};


bool CanHit(const ValveSDK::Vector &point, float *damage_given);