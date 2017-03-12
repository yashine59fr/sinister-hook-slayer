#ifndef __MISC_H__
#define __MISC_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

class CMisc
{
private:
	ValveSDK::QAngle	m_qOldViewPunch;
	ValveSDK::QAngle	m_qOldAimPunch;
	ValveSDK::QAngle*	m_pqViewPunch;
	ValveSDK::QAngle*	m_pqAimPunch;
	ValveSDK::QAngle*	vOldAngles;
private:


public:
	CMisc(void);
	void RecoilControl(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd);
	void AutoHop(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity * pLocal);
	void Pitch(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity * pLocal, bool& bSendPacket);
	void Yaw(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity * pLocal, bool& bSendPacket);
	void FakeLag(ValveSDK::CUserCmd* pCmd, bool& bSendPacket);
	bool doaa(ValveSDK::CBaseEntity* pLocal);
	void EnginePred(ValveSDK::CUserCmd* pCmd);
	bool EdgeAntiAim(ValveSDK::CBaseEntity* pLocalBaseEntity, ValveSDK::CUserCmd* cmd, float flWall, float flCornor);
	void FixMovement(ValveSDK::Vector& oang, ValveSDK::CUserCmd* pCmd);
	bool IsVisible(ValveSDK::Vector& StartPos, ValveSDK::Vector& EndPos, ValveSDK::CBaseEntity* localPly, ValveSDK::CBaseEntity* pEnt);
	void HandleNames(const char* name);
};

extern CMisc* g_pMisc;

#endif