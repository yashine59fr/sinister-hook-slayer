//========= Flow, All rights reserved. ================//
// TimeSimulator
// Purpose: Shifting cmd time accordingly to targeted entity.
//			for more accurate lagcompensation results.
//=====================================================//
#include "Vector.h"
#include "SDK.h"
#include "TimeSimulation.h"


#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / g_pGlobalVarsBase->interval_per_tick ) )
#define TICKS_TO_TIME( t )		( g_pGlobalVarsBase->interval_per_tick *( t ) )

LagRecord_t::LagRecord_t()
{
	m_vecPreviousOrigin = ValveSDK::Vector(0, 0, 0);
	m_flSimulationTime = 0.0f;
	m_bValidRecord = false;
}

void CTimeSimulator::Cache()
{
	ValveSDK::CBaseEntity* pLP = g_pEntityList->GetBaseEntity(g_pEngine->GetLocalPlayer());
	static DWORD s_dwTickbaseoffs = g_pNetVars->GetOffset("DT_BasePlayer", "m_nTickBase");
	static DWORD s_dwSimtimmeoffs = g_pNetVars->GetOffset("DT_BaseEntity", "m_flSimulationTime");
	int iTickBase = *(int*)((unsigned long)pLP + s_dwTickbaseoffs);

	float flCurrentTime = g_pGlobalVarsBase->interval_per_tick * iTickBase;

	for (int s = 1; s <= g_pGlobalVarsBase->maxclients; ++s)
	{
		m_PlayerTable[s].m_bValidRecord = false;
		ValveSDK::CBaseEntity* pEntity = g_pEntityList->GetBaseEntity(s);
		if (!pEntity)
			continue;

		if (!pEntity->IsValid())
			continue;

		float flSimTime = *(float*)((DWORD)pEntity + s_dwSimtimmeoffs);

		// Origin delta differance rejection
		if (m_PlayerTable[s].m_vecPreviousOrigin.Length() > 0)
		{
			ValveSDK::Vector delta = pEntity->GetAbsOrigin() - m_PlayerTable[s].m_vecPreviousOrigin;
			if (delta.Length2DSqr() > (64 * 64))
			{
				m_PlayerTable[s].m_vecPreviousOrigin = pEntity->GetAbsOrigin();
				continue;
			}
		}
		m_PlayerTable[s].m_vecPreviousOrigin = pEntity->GetAbsOrigin();

		// Time differance rejection
		if (fabs(flSimTime - flCurrentTime) > 1.0f)
			continue;

		m_PlayerTable[s].m_flSimulationTime = flSimTime;
		m_PlayerTable[s].m_bValidRecord = true;
	}
}

bool CTimeSimulator::ProcessCmd(int iTargetIndex,/*pBad*/ ValveSDK::CUserCmd* pCmd)
{
	if (iTargetIndex == -1 || iTargetIndex > g_pGlobalVarsBase->maxclients)
		return false;

	if (!m_PlayerTable[iTargetIndex].m_bValidRecord)
		return false;

	pCmd->tick_count = TIME_TO_TICKS(m_PlayerTable[iTargetIndex].m_flSimulationTime);
	return true;
}