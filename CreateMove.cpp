#include "CreateMove.h"
#include "Misc.h"
#include "Aimbot.h"
#include "LegitAimbot.h"
#include "TimeSimulation.h"
bool bCanFire = false;
bool bOldBullet = false;
int iMaxChokedticks = 2;
int iChokedticks = -1;
float flNextPrimary;
float flCurTime;

CVMTHookManager* g_pCreateMoveVMTHook = nullptr;
typedef void(__stdcall* oCreateMove)(int, float, bool);


void Setup(ValveSDK::CBaseEntity* pLocalPlayer, ValveSDK::CUserCmd* pCmd)
{
	bCanFire = true;
	flCurTime = g_pGlobalVarsBase->interval_per_tick * (pLocalPlayer->GetTickBase() + 1);
	flNextPrimary = pLocalPlayer->GetWeapon()->GetNextPrimaryAttack();
	if (flNextPrimary > flCurTime || bOldBullet)
		bCanFire = false;
	if (!(flNextPrimary > flCurTime))
		bOldBullet = false;
}

void Handle(bool& bSendPackets, ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd, ValveSDK::Vector &oldang, float oldside, float oldforward, ValveSDK::QAngle oldpunch)
{
	if (g_CVars.GetCVar("rage_silent")->GetBool() || g_CVars.GetCVar("legit_silent")->GetBool())
	{
		Global::aiming = true;
		if (bCanFire && pCmd->buttons & IN_ATTACK)
		{
			bSendPackets = false;
			iChokedticks++;
		}
		//So we dont kill ourselfs
		if (iChokedticks > iMaxChokedticks)
			bSendPackets = true;

		if (bSendPackets)
		{
			Global::aiming = false;
			iChokedticks = 0;
			pCmd->viewangles = oldang;
			pCmd->forwardmove = oldforward;
			pCmd->sidemove = oldside;
		}
	}
}


bool init = false;
bool flip = false;
void __stdcall CreateMoveProxy(int sequence_number, float input_sample_frameTime, bool active, bool& bSendPacket)
{
	g_pClientVMTHook->GetMethod< oCreateMove >(21)(sequence_number, input_sample_frameTime, active);

	auto pCmd = &(*(ValveSDK::CUserCmd**)((DWORD_PTR)g_pInput + 0xEC))[sequence_number % 150];
	if (!pCmd)
		return;

	auto pVerifiedCmd = &(*(ValveSDK::CInput::CVerifiedUserCmd**)((DWORD_PTR)g_pInput + 0xF0))[sequence_number % 150];
	if (!pVerifiedCmd)
		return;
			
	auto pLocalEntity = g_pTools->GetLocalPlayer();
	//Global::GlobalpLocal = pLocalEntity;
	ValveSDK::ConVar* Name = g_pICvar->FindVar("name");
	*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
	ValveSDK::ConVar* interpolate = g_pICvar->FindVar("cl_interpolate");
	*(int*)((DWORD)&interpolate->fnChangeCallback + 0xC) = 0;
	interpolate->SetValue(0.0000000);
	ValveSDK::ConVar* interp = g_pICvar->FindVar("cl_interp");
	*(int*)((DWORD)&interp->fnChangeCallback + 0xC) = 0;
	interp->SetValue(0.0000000);
	ValveSDK::ConVar* interpratio = g_pICvar->FindVar("cl_interp_ratio");
	*(int*)((DWORD)&interpratio->fnChangeCallback + 0xC) = 0;
	interpratio->SetValue(0.0000000);

	
	if (pLocalEntity && pLocalEntity->IsValid())
	{
		auto OldPunch = pLocalEntity->GetAimPunch();
		Global::strafeang = pCmd->viewangles;
		ValveSDK::Vector oldAngles = pCmd->viewangles;

		g_pMisc->AutoHop(pCmd, pLocalEntity);

		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			ValveSDK::CBaseEntity* pBaseEntity = g_pEntityList->GetBaseEntity(i);
			if (pBaseEntity && !pBaseEntity->IsDormant() && !pBaseEntity->GetTeam() != pLocalEntity->GetTeam() && pBaseEntity->GetLifeState() == 0) Global::OldSimulationTime[i] = pBaseEntity->m_flSimulationTime();
		}

		auto pWeapon = pLocalEntity->GetWeapon();
		if (pWeapon)
			Setup(pLocalEntity, pCmd);
		bool ladder = pLocalEntity->GetMoveType() == ValveSDK::MOVETYPE_LADDER;
		bool knife = pWeapon->IsKnife();
		bool attacking = pCmd->buttons & IN_ATTACK;
		bool weapon = pWeapon->IsValid(true);
		bool grenade = pWeapon->IsGrenade();
		if (g_CVars.GetCVar("misc_antiaim")->GetBool() && !ladder && !knife && !grenade)
		{
			if (g_pMisc->doaa(pLocalEntity))
			{
				g_pMisc->Pitch(pCmd, pLocalEntity, bSendPacket);
				g_pMisc->Yaw(pCmd, pLocalEntity, bSendPacket);
			}
		}
		auto iEdge = g_CVars.GetCVar("misc_edge")->GetBool();
		if (iEdge && g_CVars.GetCVar("misc_antiaim")->GetBool() && !ladder && !knife && !grenade)
		{
			if (pLocalEntity->GetVelocity().Length2D() < 150)
				auto bEdge = g_pMisc->EdgeAntiAim(pLocalEntity, pCmd, 0.f, 82.f);
		}

		if (g_CVars.GetCVar("misc_fakeduck")->GetBool() && pCmd->buttons & IN_DUCK)
		{
			static int ticks = 0;

			if (ticks != 0)
			{
				bSendPacket = false;
				ticks--;
			}
			else
			{
				pCmd->buttons &= ~IN_DUCK;
				ticks = 4;
				bSendPacket = true;
			}
		}
		
		ValveSDK::Vector oldAngle = pCmd->viewangles;
		float sidemove = pCmd->sidemove;
		float forwardmove = pCmd->forwardmove;
		if (attacking && bCanFire)
		{
			pCmd->viewangles = oldAngles;
		}
		if (g_CVars.GetCVar("vis_noparticles")->GetBool())
		{
			ValveSDK::ConVar* interpratio = g_pICvar->FindVar("r_drawparticles");
			*(int*)((DWORD)&interpratio->fnChangeCallback + 0xC) = 0;
			interpratio->SetValue(0);
		}
		else
		{
			ValveSDK::ConVar* interpratio = g_pICvar->FindVar("r_drawparticles");
			interpratio->SetValue(1);
		}
		g_pMisc->EnginePred(pCmd);
		Global::pLocalAngles = pLocalEntity->GetEyePosition();
		if (bCanFire)
		{
			g_pAimbot->Main(pLocalEntity, pCmd, bSendPacket);
			g_pLAimbot->Main(pLocalEntity, pCmd, bSendPacket);
		}
		g_pMisc->RecoilControl(pLocalEntity, pCmd);
		int choke = g_CVars.GetCVar("misc_fakelagval")->GetInt() + 1;
		if (choke > 15)
			choke = 14;
		if (g_CVars.GetCVar("misc_fakelag")->GetBool())
		{
			
			static int FakelagTick;
			FakelagTick++;
			int Mode = g_CVars.GetCVar("misc_fakelag_mode")->GetInt();
			if (Mode == 0) bSendPacket = g_CVars.GetCVar("misc_fakelag")->GetBool() ? !(FakelagTick % (choke)) : 1; // Normal
			if (Mode == 1)
			{
				static int FakelagFactor = 2;
				bSendPacket = g_CVars.GetCVar("misc_fakelag_mode")->GetInt() ? !(FakelagTick % (FakelagFactor + 1)) : 1;
				if (bSendPacket)
					FakelagFactor = max(1, min((int)(fabs(pLocalEntity->GetVelocity().Length2D() / 80.f)), 12));
			}
			if (Mode == 2)
			{
				static int FakelagFactor = 8;
				bSendPacket = g_CVars.GetCVar("misc_fakelag_mode")->GetInt() ? !(FakelagTick % (FakelagFactor + 1)) : 1;
				if (bSendPacket) {
					FakelagFactor = (rand() % 7) + 6;
				}
			}
			if (Mode == 3)
			{
				static int FakelagFactor = g_CVars.GetCVar("misc_fakelagval")->GetInt();
				bSendPacket = g_CVars.GetCVar("misc_fakelag_mode")->GetInt() ? !(FakelagTick % (FakelagFactor + 1)) : 1;
				if (bSendPacket) {
					FakelagFactor = (rand() % 10) + 1;
				}
			}
			if (Mode == 4)
			{
				static int FakelagFactor = 5;
				int Based = FakelagFactor / 3;
				bSendPacket = g_CVars.GetCVar("misc_fakelag_mode")->GetInt() ? !(FakelagTick % (Based)) : 1;
				if (bSendPacket) {
					FakelagFactor += 1;
				if (Based >= g_CVars.GetCVar("misc_fakelagval")->GetInt()) FakelagFactor = 3;
				}
			}
			if (Mode == 5)
			{
				static int FakelagFactor = 10;
				static int m_iOldHealth = 0;
				static int iChoked;
				if (m_iOldHealth != pLocalEntity->GetHealth()) {
					m_iOldHealth = pLocalEntity->GetHealth();
					FakelagFactor = rand() % 7 + 6 + 1;
				}
				bSendPacket = g_CVars.GetCVar("misc_fakelag_mode")->GetInt() ? !(FakelagTick % (FakelagFactor + 1)) : 1;
				if (!bSendPacket)
					iChoked++;
				else iChoked = 0;

				if (iChoked > 14) {
					bSendPacket = 1;
					FakelagTick = -1;
				}
			}
		}
		Handle(bSendPacket, pLocalEntity, pCmd, oldAngle, sidemove, forwardmove,OldPunch);

		if (bSendPacket)
			Global::VisualAngle = pLocalEntity->GetEyeAngles();
		if (GetAsyncKeyState(VK_XBUTTON2) && !g_CVars.GetCVar("misc_antiuntrusted")->GetBool() && g_CVars.GetCVar("misc_teleport")->GetBool())
			pCmd->viewangles.z = 99999999999999999999999999.999999999999999f;
		if (g_CVars.GetCVar("misc_antiuntrusted")->GetBool())
		{
			g_pTools->ClampAngles(pCmd->viewangles);
			g_pTools->ClampMovement(pCmd);
		}
		Global::bSendPacket = bSendPacket;
		g_pMisc->FixMovement(Global::strafeang, pCmd);
		Global::command_number = pCmd->command_number;
	}

	pVerifiedCmd->m_cmd = *pCmd;
	pVerifiedCmd->m_crc = pCmd->GetChecksum();
}
