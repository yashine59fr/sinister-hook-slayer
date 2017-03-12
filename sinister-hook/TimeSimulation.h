#pragma once
#include "Vector.h"



#define MAX_PLAYERS 64


struct LagRecord_t
{
	LagRecord_t();
	float						m_flSimulationTime;
	bool						m_bValidRecord;
	ValveSDK::Vector						m_vecPreviousOrigin;
};

class CTimeSimulator
{
public:
	//Singleton
	static CTimeSimulator*		Get() { static CTimeSimulator m_sTimeSimulator; return &m_sTimeSimulator; }
	void						Cache();
	bool						ProcessCmd(int iTargetIndex, ValveSDK::CUserCmd* pCmd);

private:
	LagRecord_t					m_PlayerTable[MAX_PLAYERS];
};