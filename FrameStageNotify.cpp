#include "FrameStageNotify.h"
#include "Misc.h"




typedef void(__stdcall* oFrameStageNotify)(ValveSDK::ClientFrameStage_t);

static int CurrentStage[65];
void FixAngel1(ValveSDK::CBaseEntity* pEnt, float* pfPitch, float* pfYaw)
{
	int index = pEnt->GetIndex();
	if (pfPitch) {
		if (CurrentStage[index] < 4)
			*pfPitch = 89.f;
		else if (CurrentStage[index] < 8)
			*pfPitch = -89.f;
	}
}
void FixAngel2(ValveSDK::CBaseEntity* pEnt, float* pfPitch, float* pfYaw)
{
	int index = pEnt->GetIndex();
	if (pfYaw) {
		static float SpinYaw[65], TwitchTime[65];
		static bool Twitch[65];
		SpinYaw[index] += g_pGlobalVarsBase->frametime * 135.f;
		if (SpinYaw[index] > 360.f) SpinYaw[index] = 0.f;

		TwitchTime[index] -= g_pGlobalVarsBase->frametime;
		if (TwitchTime[index] <= 0.f) {
			Twitch[index] = !Twitch[index];
			TwitchTime[index] = 0.02f;
		}

		*pfYaw = SpinYaw[index] - (Twitch[index] ? 180.f : 0.f);
	}
}
ValveSDK::QAngle	m_qOldViewPunch;
ValveSDK::QAngle	m_qOldAimPunch;
ValveSDK::QAngle*	m_pqViewPunch;
ValveSDK::QAngle*	m_pqAimPunch;
ValveSDK::QAngle*	vOldAngles;
bool RemoveVisualsRecoil(ValveSDK::CBaseEntity* pLocalEntity)
{
	if (!g_CVars.GetCVar("vis_norec")->GetBool())
		return false;

	m_pqAimPunch = (ValveSDK::QAngle*)((DWORD)pLocalEntity + Offsets::m_aimPunchAngle);
	m_pqViewPunch = (ValveSDK::QAngle*)((DWORD)pLocalEntity + Offsets::m_viewPunchAngle);

	if (m_pqAimPunch && m_pqViewPunch)
	{
		m_qOldAimPunch = *m_pqAimPunch;
		m_qOldViewPunch = *m_pqViewPunch;

		m_pqAimPunch->Zero();
		m_pqViewPunch->Zero();

		return true;
	}

	return false;
}
void RestoreVisualRecoil(void)
{
	if (m_pqAimPunch && m_pqViewPunch)
	{
		*m_pqAimPunch = m_qOldAimPunch;
		*m_pqViewPunch = m_qOldViewPunch;
	}
}

float getadd(float meme)
{
	if (meme == 0)
		return rand() % 180 + 90;
	if (meme == 1)
		return 90;
	if (meme == 2)
		return 180;
	if (meme == 3)
		return -90;
}
int GetEstimatedServerTickCount(float latency)
{
	return (int)floorf((float)((float)(latency) / (float)((uintptr_t)&g_pGlobalVarsBase->interval_per_tick)) + 0.5) + 1 + (int)((uintptr_t)&g_pGlobalVarsBase->tickcount);
}

float inline GetEstimatedServerTime()
{
	return Global::GlobalpLocal->GetTickBase() * (float)((uintptr_t)&g_pGlobalVarsBase->interval_per_tick);
}


bool bVisNoRecoil;
void __stdcall hkFrameStageNotify(ValveSDK::ClientFrameStage_t curStage)
{
	ValveSDK::QAngle aimold;
	ValveSDK::QAngle viewold;
	ValveSDK::QAngle* aim = NULL;
	ValveSDK::QAngle* view = NULL;

	auto* pLocal = g_pTools->GetLocalPlayer();
	if (!pLocal)
		return;

	if (pLocal && pLocal->IsValid())
	{
		if (curStage == ValveSDK::FRAME_RENDER_START)
		{


			bVisNoRecoil = RemoveVisualsRecoil(pLocal);
			pLocal->SetFov(90 + g_CVars.GetCVar("vis_fov")->GetFloat());
			if (*(bool*)((DWORD)g_pInput + 0xA5)) {
				*(ValveSDK::Vector*)((DWORD)pLocal + g_pNetVars->GetOffset("DT_CSPlayer", "deadflag") + 4) = Global::VisualAngle;
			}
		}

	}
	if (curStage == ValveSDK::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		std::vector<int> NextShotVector;
		for (auto i = 0; i < g_pEntityList->GetHighestEntityIndex(); i++)
		{
			static float Jittering[64] = { 0 };
			ValveSDK::CBaseEntity* pEnt = nullptr;
			if (!(pEnt = g_pEntityList->GetBaseEntity(i)))
				continue;
			if ((pEnt == pLocal))
				continue;
			ValveSDK::IEngineClient::player_info_t pTemp;

			if (!g_pEngine->GetPlayerInfo(i, &pTemp))
				continue;
			auto *FYaw = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + Offsets::m_flLowerBodyYawTarget);
			auto *Pitch = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + Offsets::m_angEyeAnglesX);
			auto *Yaw = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + Offsets::m_angEyeAnglesY);
			if (g_CVars.GetCVar("misc_resolver")->GetBool())
			{

					float curtime = g_pGlobalVarsBase->curtime;
					
					if (*Pitch == 180.f) *Pitch = 89.f;
					else if (*Pitch > 180.f && *Pitch < 290.f) *Pitch = -89.f;
					else if (*Pitch >= 89.f && *Pitch <= 180.f) *Pitch = 89.f;
					else if (*Pitch == 0.f)
						FixAngel1(pEnt, Pitch, 0);
					static ValveSDK::Vector angles = ValveSDK::Vector(0, 0, 0);
					static float difference = 0;

					float PlayerIsMoving = abs(pEnt->GetVelocity().Length());
					bool bLowerBodyUpdated = false;
					bool IsUsingFakeAngles = false;
					float oldlowerbodyyaw;
					if (oldlowerbodyyaw != *FYaw)
					{
						bLowerBodyUpdated = true;
					}
					float bodyeyedelta = pEnt->GetEyeAnglesXY().y - *Yaw;
					if (PlayerIsMoving || bLowerBodyUpdated)// || LastUpdatedNetVars->eyeangles.x != CurrentNetVars->eyeangles.x || LastUpdatedNetVars->eyeyaw != CurrentNetVars->eyeangles.y)
					{
						if (bLowerBodyUpdated || (PlayerIsMoving && bodyeyedelta >= 35.0f))
						{
							*Yaw = *FYaw;
							oldlowerbodyyaw = *Yaw;
						}

						IsUsingFakeAngles = false;
					}
					else
					{
						if (bodyeyedelta > 35.0f)
						{
							*Yaw = oldlowerbodyyaw;
							IsUsingFakeAngles = true;
						}
						else
						{
							IsUsingFakeAngles = false;
						}
					}
					if (IsUsingFakeAngles)
					{
						int com = GetEstimatedServerTickCount(90);

						if (com % 2)
						{
							*Yaw += 90;
						}
						else if (com % 3)
							*Yaw -= 90;
						else
							*Yaw -= 0;
					}
					//bool ong = pEnt->GetFlags() & FL_ONGROUND;
					//if (PlayerIsMoving && !ong)
					//{
					//	if (Global::retargetplayer[i] == true)
					//	{
					//		if (oldlowerbodyyaw)
					//		{
					//			float curyaw = (360.0 / 65536) * (oldlowerbodyyaw / *Yaw + *FYaw);
					//			*Yaw = (360.0 / 65536) * ((int)(curyaw*(65536 / 360.0)) & 65535);
					//		}
					//	}
					//}

			}

		}

		//SKINCHANGER
		auto nCTDefault = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
		auto nBayonet = g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
		auto nGut = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
		auto nTDefault = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		auto nButterfly = g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
		auto nFlip = g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
		auto nGunGame = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");
		auto nFalchion = g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
		auto nM9Bayonet = g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
		auto nKarambit = g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
		auto nHuntsman = g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
		auto nDagger = g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
		auto nBowie = g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
		auto pWeapon = pLocal->GetWeapon();
		if (pWeapon)
		{
			auto weaponID = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pWeapon) + Offsets::m_iItemDefinitionIndex);

				*reinterpret_cast<int*>(DWORD(pWeapon) + Offsets::m_iEntityQuality) = 3;

				char* a = (char*)((DWORD)pWeapon + Offsets::m_szCustomName);
					sprintf_s(a, 32, "%s", "1337Dank");


			
		}
	}

	g_pClientVMTHook->GetMethod< oFrameStageNotify >(36)(curStage);

	if (bVisNoRecoil)
		RestoreVisualRecoil();
}
