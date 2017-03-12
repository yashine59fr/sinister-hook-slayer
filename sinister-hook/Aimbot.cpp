#include "Aimbot.h"
#include "Autowall.h"
#include "xor.h"
CAimbot::CAimbot(void)
{

}

int CAimbot::Bone()
{
	auto pLocal = g_pTools->GetLocalPlayer();
	auto pLocalWeapon = pLocal->GetWeapon();

	if (!pLocalWeapon)
		return g_CVars.GetCVar("rage_hitbox")->GetInt();
	if (Global::missedshots > 3 && g_CVars.GetCVar("rage_smartaim")->GetBool())
	{
		return 4;
	}
	else if (pLocalWeapon->IsSniper() && g_CVars.GetCVar("rage_awpbaim")->GetBool())
		return 4;
	else
		return g_CVars.GetCVar("rage_hitbox")->GetInt();
}
int NextShot;
int ticks = 0;
void handleshots(ValveSDK::CBaseEntity* pBaseEntity,bool add)
{
	if (add)
	{

			if (Global::missedshots >= Global::maxmissedshots)
			{
				Global::retarget = true;
				Global::retargetplayer[pBaseEntity->GetIndex()] = true;
				
			}
			else if (Global::missedshots < Global::maxmissedshots)
			{
				Global::retargetplayer[pBaseEntity->GetIndex()] = false;
				Global::retarget = false;
				ticks = 0;
			}
			ticks++;
			Global::missedshots++;
	}
}
int CAimbot::GetTarget(ValveSDK::CBaseEntity* pLocal, ValveSDK::CUserCmd* pCmd)
{
	
	int minDist = 99999;
	int target = -1;
	bool NextShotValid = false;
	std::vector<int> NextShotVector;
	ValveSDK::Vector ViewOffset = pLocal->GetEyePosition();
	ValveSDK::Vector View; g_pEngine->GetViewAngles(View);

	for (int i = 0; i < g_pEntityList->GetHighestEntityIndex(); i++)
	{
	
		ValveSDK::CBaseEntity* pEntity = g_pEntityList->GetBaseEntity(i);
		if (Global::targ == i)
		{
			if (pEntity->GetHealth() < 1)
				Global::missedshots = 0;
		}
		if (g_pTools->IsValids(i, pLocal,pCmd))
		{
			ValveSDK::Vector Difference = pLocal->GetAbsOrigin() - pEntity->GetAbsOrigin();
			float fov = g_pTools->GetFov(ViewOffset, View, pEntity, 0);
			if (fov < g_CVars.GetCVar("rage_fov")->GetInt())
			{
				target = i;
			}
			if (i == NextShot)
				NextShotValid = true;
			else
				NextShotVector.push_back(i);
		}
	}
	int iIndex = -1;

	if (!NextShotVector.empty() && NextShotVector.size() != 0) {
		iIndex = NextShotVector.at(rand() % NextShotVector.size());
	}

	if (iIndex == -1 && NextShotValid)
		iIndex = NextShot;

	NextShot = iIndex;
	if (iIndex != -1 && g_pTools->IsValids(iIndex, pLocal, pCmd)) {
		return iIndex;
	}
	return target;
}
template<class T, class U>
T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}
float LagFix()
{
	float updaterate = g_pICvar->FindVar("cl_updaterate")->fValue;
	ValveSDK::ConVar* minupdate = g_pICvar->FindVar("sv_minupdaterate");
	ValveSDK::ConVar* maxupdate = g_pICvar->FindVar("sv_maxupdaterate");

	if (minupdate && maxupdate)
		updaterate = maxupdate->fValue;

	float ratio = g_pICvar->FindVar("cl_interp_ratio")->fValue;

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = g_pICvar->FindVar("cl_interp")->fValue;
	ValveSDK::ConVar* cmin = g_pICvar->FindVar("sv_client_min_interp_ratio");
	ValveSDK::ConVar* cmax = g_pICvar->FindVar("sv_client_max_interp_ratio");

	if (cmin && cmax && cmin->fValue != 1)
		ratio = clamp(ratio, cmin->fValue, cmax->fValue);


	return max(lerp, ratio / updaterate);
}

ValveSDK::Vector BestPoint(ValveSDK::CBaseEntity* targetPlayer, ValveSDK::Vector &final)
{
	ValveSDK::IEngineTrace::trace_t tr;
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::IEngineTrace::CTraceFilter filter;

	filter.pSkip = targetPlayer;
	ray.Init(final + ValveSDK::Vector(rand() % 15, rand() % 15, rand() % 15), final);
	g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
	if (tr.fraction == 1.f || tr.m_pEnt == targetPlayer) return tr.endpos;
	else
	return final;
}
bool CAimbot::Main(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket)
{
	if (!g_CVars.GetCVar("rage_active")->GetBool())
		return false;

	if (!pLocalEntity || !pCmd)
		return false;

	auto pLocalWeapon = pLocalEntity->GetWeapon();

	if (!pLocalWeapon)
		return false;

	if (!pLocalWeapon->IsValid(true))
		return false;

	auto pLocalWeaponData = pLocalWeapon->GetWeaponData();

	if (!pLocalWeaponData)
		return false;

	int TargetID = -1;

	TargetID = GetTarget(pLocalEntity,pCmd);

	if (TargetID == -1)
	{
		Global::targ = -1;
		return false;
	}
	if (Global::SelectedPlayerIgnore[TargetID] == true)
		return false;
	Global::targ = TargetID;

	auto pBaseEntity = g_pEntityList->GetBaseEntity(TargetID);

	if (!pBaseEntity)
		return false;

	int hitbox = Bone();

	ValveSDK::Vector vecHit = pBaseEntity->GetHitboxPosition(hitbox);
	if (vecHit == ValveSDK::Vector(0, 0, 0))
		return false;


	if (!pLocalWeapon->HitChance(g_CVars.GetCVar("rage_hitchance_val")->GetFloat()))
		return false;

	ValveSDK::QAngle qClientViewAngles; 
	g_pEngine->GetViewAngles(qClientViewAngles);

	ValveSDK::Vector vForward;
	g_pTools->AngleVectors(qClientViewAngles, vForward);

	ValveSDK::Vector qAimAngles;
	g_pTools->CalcAngle(pLocalEntity->GetEyePosition(), vecHit, qAimAngles);

	g_pTools->NormalizeVector(qAimAngles);

	if (!pLocalWeapon->HitChance(g_CVars.GetCVar("rage_hitchance_val")->GetFloat()))
		return false;
	
	pCmd->viewangles = qAimAngles;
	Global::aiming = true;

	if (g_CVars.GetCVar("rage_autoshoot")->GetBool()) pCmd->buttons |= IN_ATTACK;

	if (!g_CVars.GetCVar("rage_silent")->GetBool())
	{
		g_pEngine->SetViewAngles(qAimAngles);
	}
	if (g_CVars.GetCVar("misc_antiuntrusted")->GetBool())
	{
		g_pTools->ClampAngles(pCmd->viewangles);
	}
	handleshots(pBaseEntity, true);
	
	pCmd->tick_count = TIME_TO_TICKS(LagFix());
	return true;
}
CAimbot* g_pAimbot = nullptr;