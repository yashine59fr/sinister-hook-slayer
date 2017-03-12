#include "LegitAimbot.h"

CLAimbot::CLAimbot(void)
{

}
bool IsValids(int iEnt, ValveSDK::CBaseEntity* pLocal, ValveSDK::CUserCmd *pCmd, bool &sniper)
{
	ValveSDK::CBaseEntity* pEnt = nullptr;
	int hitboxint = 0;

	if ((g_CVars.GetCVar("legit_awpbaim")->GetInt() && sniper))
		hitboxint = 6;
	else
		hitboxint = g_CVars.GetCVar("legit_hitbox")->GetInt();

	if ((pEnt = g_pEntityList->GetBaseEntity(iEnt)))
		if (!(pEnt == pLocal))
		{
			if (pEnt->GetTeam() != pLocal->GetTeam())
				if (!pEnt->IsDormant())
					if (pEnt->GetHealth() > 0)
						if (!pEnt->IsProtected() && g_pTools->IsVisible(pLocal->GetEyePosition(), pEnt->GetHitboxPosition(hitboxint), pLocal, pEnt))
						{

							return true;

						}
		}
	return false;
}
int CLAimbot::GetTarget(ValveSDK::CBaseEntity* pLocal, ValveSDK::CUserCmd* pCmd, bool &sniper)
{

	int minDist = 99999;
	int target = -1;
	ValveSDK::Vector ViewOffset = pLocal->GetEyePosition();
	ValveSDK::Vector View; g_pEngine->GetViewAngles(View);

	for (int i = 0; i < g_pEntityList->GetHighestEntityIndex(); i++)
	{

		ValveSDK::CBaseEntity* pEntity = g_pEntityList->GetBaseEntity(i);
		if (g_pTools->IsValids(i, pLocal,pCmd))
		{
			ValveSDK::Vector Difference = pLocal->GetAbsOrigin() - pEntity->GetAbsOrigin();
			float fov = g_pTools->GetFov(ViewOffset, View, pEntity, 0);
			if (fov < g_CVars.GetCVar("legit_fov")->GetInt())
			{
				target = i;
			}
		}
	}
	return target;
}
bool CLAimbot::Main(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, bool& bSendPacket)
{
	if (!g_CVars.GetCVar("legit_active")->GetBool())
		return false;
	bool shooting = pCmd->buttons & IN_ATTACK;

	if (!g_CVars.GetCVar("legit_autoshoot")->GetBool() && !shooting)
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
	bool issnip = pLocalWeapon->IsSniper();
	TargetID = GetTarget(pLocalEntity, pCmd, issnip);
	Global::targ = TargetID;
	if (TargetID == -1)
	{
		Global::targ = -1;
		return false;
	}

	auto pBaseEntity = g_pEntityList->GetBaseEntity(TargetID);

	if (!pBaseEntity)
		return false;
	int hitboxint = 0;

	if ((g_CVars.GetCVar("legit_awpbaim")->GetInt() && pLocalWeapon->IsSniper()))
		hitboxint = 6;
	else
		hitboxint = g_CVars.GetCVar("legit_hitbox")->GetInt();

	ValveSDK::Vector vecHit = pBaseEntity->GetHitboxPosition(hitboxint);
	if (vecHit == ValveSDK::Vector(0, 0, 0))
		return false;

	ValveSDK::QAngle qClientViewAngles;
	g_pEngine->GetViewAngles(qClientViewAngles);

	ValveSDK::Vector vForward;
	g_pTools->AngleVectors(qClientViewAngles, vForward);

	ValveSDK::Vector qAimAngles;
	g_pTools->CalcAngle(pLocalEntity->GetEyePosition(), vecHit, qAimAngles);


	if (g_CVars.GetCVar("legit_rcs")->GetBool() && pLocalWeapon->IsAutomatic())
	{
		auto qPunchAngles = pLocalEntity->GetAimPunch();
		qAimAngles -= qPunchAngles * 2.f;
		qAimAngles.z = 0.f;

		g_pTools->NormalizeVector(qAimAngles);
	}

	if (g_CVars.GetCVar("legit_smoothing")->GetFloat() > 0.f && !g_CVars.GetCVar("legit_silent")->GetBool())
	{
		g_pTools->NormalizeVector(qClientViewAngles);

		auto qDelta = qClientViewAngles - qAimAngles;
		g_pTools->NormalizeVector(qDelta);

		auto qSmooth = qClientViewAngles - qDelta / g_CVars.GetCVar("legit_smoothing")->GetFloat();
		g_pTools->NormalizeVector(qDelta);

		qAimAngles = qSmooth;
	}

	g_pTools->NormalizeVector(qAimAngles);
	if (g_CVars.GetCVar("misc_antiuntrusted")->GetBool())
	{
		g_pTools->ClampAngles(qAimAngles);
	}
	pCmd->viewangles = qAimAngles;

	if (g_CVars.GetCVar("legit_autoshoot")->GetBool())
	{
		pCmd->buttons |= IN_ATTACK;
	}

	if (!g_CVars.GetCVar("legit_silent")->GetBool())
	{
		g_pEngine->SetViewAngles(qAimAngles);
	}
	return true;
}
CLAimbot* g_pLAimbot = nullptr;