#ifndef __AIMBOT_H__
#define __AIMBOT_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CAimbot
{
private:

public:
	CAimbot(void);
	bool Main(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket);
	int GetTarget(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd);
	int Bone();
};

extern CAimbot* g_pAimbot;

#endif