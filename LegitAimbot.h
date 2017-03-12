#ifndef __LAIMBOT_H__
#define __LAIMBOT_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CLAimbot
{
private:

public:
	CLAimbot(void);
	bool Main(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket);
	int GetTarget(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool &sniper);
};

extern CLAimbot* g_pLAimbot;

#endif#pragma once
