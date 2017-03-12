#include "Misc.h"
#include "SDK.h"

CMisc::CMisc(void)
{

}

void CMisc::FixMovement(ValveSDK::Vector& oang, ValveSDK::CUserCmd* pCmd) {
	ValveSDK::Vector vMove = ValveSDK::Vector(pCmd->forwardmove, pCmd->sidemove, 0.0f);
	float flSpeed = vMove.Length();
	ValveSDK::Vector qMove;
	g_pTools->VectorAngles(vMove, qMove);
	float normalized = fmod(pCmd->viewangles.y + 180.f, 360.f) - 180.f;
	float normalizedx = fmod(pCmd->viewangles.x + 180.f, 360.f) - 180.f;
	float flYaw = DEG2RAD((normalized - oang.y) + qMove.y);
	if (normalizedx >= 90.0f || normalizedx <= -90.0f) pCmd->forwardmove = -cos(flYaw) * flSpeed;
	else pCmd->forwardmove = cos(flYaw) * flSpeed;
	pCmd->sidemove = sin(flYaw) * flSpeed;
}

void CMisc::EnginePred(ValveSDK::CUserCmd* pCmd)
{
	if (!g_pMoveHelper)return;
	if (!g_pEngine->IsIngame() && !g_pEngine->IsConnected()) return;
	auto MoveData = *reinterpret_cast<void**>(reinterpret_cast<DWORD>(g_pGameMovement) + 0x8);
	if (!MoveData) return;
	auto* pLocal = g_pTools->GetLocalPlayer();
	auto oldCurtime = g_pGlobalVarsBase->curtime * pLocal->GetTickBase();
	auto oldFrame = g_pGlobalVarsBase->frametime;
	g_pGlobalVarsBase->frametime = g_pGlobalVarsBase->interval_per_tick;
	g_pGlobalVarsBase->curtime = pLocal->GetTickBase() * g_pGlobalVarsBase->interval_per_tick;

	g_pMoveHelper->SetHost(pLocal);
	g_pPrediction->SetupMove(pLocal, pCmd, nullptr, MoveData);
	g_pGameMovement->ProcessMovement(pLocal, MoveData);
	g_pPrediction->FinishMove(pLocal, pCmd, MoveData);

	g_pMoveHelper->SetHost(nullptr);
	g_pGlobalVarsBase->frametime = oldFrame;
	g_pGlobalVarsBase->curtime = oldCurtime;

}



bool CMisc::doaa(ValveSDK::CBaseEntity* pLocal)
{
	bool aa = false;
	for (int i = 0; i < g_pEngine->GetMaxClients(); i++)
	{

		if (!g_pTools->NonVisIsValid(i, pLocal))
			continue;
		aa = true;

	}
	return aa;
}

bool CMisc::EdgeAntiAim(ValveSDK::CBaseEntity* pLocalBaseEntity, ValveSDK::CUserCmd* cmd, float flWall, float flCornor)
{
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::IEngineTrace::trace_t tr;

	ValveSDK::IEngineTrace::CTraceFilter traceFilter;
	traceFilter.pSkip = pLocalBaseEntity;

	auto bRetVal = false;
	auto vecCurPos = pLocalBaseEntity->GetEyePosition();
	ValveSDK::QAngle meme = cmd->viewangles;
	g_pTools->NormalizeVector(meme);
	int xval = g_CVars.GetCVar("misc_edge_pitch")->GetInt();
	float setpitch = 89;
	if (xval == 0) setpitch = 0;
	if (xval == 1) setpitch = 89;
	if (xval == 2) setpitch = 180;
	if (xval == 3) setpitch = 35000089;
	int yval = g_CVars.GetCVar("misc_edge_yaw")->GetInt();
	float setyaw = 0;
	bool switchb = cmd->command_number % 2;
	if (yval == 1) setyaw = 360;
	if (yval == 2) setyaw = 180;
	if (yval == 3) setyaw = (switchb ? 25 : -25);
	if (yval == 4) setyaw = (Global::bSendPacket ? 0 : 180);
	if (yval == 5) setyaw = 36000180;
	for (float i = 0; i < 360; i += 2)
	{
		ValveSDK::Vector vecDummy(10.f, meme.y, 0.f);
		vecDummy.y += i;

		g_pTools->NormalizeVector(vecDummy);

		ValveSDK::Vector vecForward;
		g_pTools->AngleVectors(vecDummy, vecForward);

		auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
		vecForward *= flLength;

		ray.Init(vecCurPos, (vecCurPos + vecForward));
		g_pEngineTrace->TraceRay(ray, MASK_SHOT, (ValveSDK::IEngineTrace::CTraceFilter *)&traceFilter, &tr);

		if (tr.fraction != 1.0f)
		{
			ValveSDK::QAngle qAngles;
			auto vecNegate = tr.plane.normal;

			vecNegate *= -1.f;
			g_pTools->VectorAngles(vecNegate, qAngles);

			vecDummy.y = qAngles.y;

			g_pTools->NormalizeVector(vecDummy);
			ValveSDK::IEngineTrace::trace_t leftTrace, rightTrace;

			ValveSDK::Vector vecLeft;
			g_pTools->AngleVectors(vecDummy + ValveSDK::Vector(0.f, 30.f, 0.f), vecLeft);

			ValveSDK::Vector vecRight;
			g_pTools->AngleVectors(vecDummy - ValveSDK::Vector(0.f, 30.f, 0.f), vecRight);

			vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
			vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

			ray.Init(vecCurPos, (vecCurPos + vecLeft));
			g_pEngineTrace->TraceRay(ray, MASK_SHOT, (ValveSDK::IEngineTrace::CTraceFilter*)&traceFilter, &leftTrace);

			ray.Init(vecCurPos, (vecCurPos + vecRight));
			g_pEngineTrace->TraceRay(ray, MASK_SHOT, (ValveSDK::IEngineTrace::CTraceFilter*)&traceFilter, &rightTrace);

			if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
				vecDummy.y -= flCornor; // left
			else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
				vecDummy.y += flCornor; // right			
			cmd->viewangles.x = setpitch;
			cmd->viewangles.y = vecDummy.y + setyaw;
			bRetVal = true;
		}
	}
	return bRetVal;
}

void CMisc::RecoilControl(ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CUserCmd* pCmd)
{
	if (!g_CVars.GetCVar("rage_norecoil")->GetBool())
		return;
	if (!pLocalEntity || !pCmd)
		return;

	auto pWeapon = pLocalEntity->GetWeapon();
	if (!pWeapon)
		return;

	if (!pWeapon->IsValid())
		return;

	if (pCmd->buttons & IN_ATTACK)
	{
		auto qPunchAngles = pLocalEntity->GetAimPunch();
		auto qAimAngles = pCmd->viewangles;
		qAimAngles -= qPunchAngles * 2.f;
		g_pTools->NormalizeVector(qAimAngles);
		pCmd->viewangles = qAimAngles;
	}
}

template<class T, class U>
T Clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

void AngleNormalize(float& angle) {
	while (angle > 180.f)
		angle -= 360.f;
	while (angle < -180.f)
		angle += 360.f;
}
bool JustStarted = true;
bool CircleDone = true;


float RightMovement;
bool IsActive = false;
float StrafeAngle = 0;

static float GetTraceFraction(ValveSDK::Vector start, ValveSDK::Vector end)
{
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::IEngineTrace::trace_t tr;
	ValveSDK::IEngineTrace::CTraceFilter filter;
	filter.pSkip = g_pTools->GetLocalPlayer();

	ray.Init(start, end);
	g_pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	return tr.fraction;
}


void CircleStrafer(ValveSDK::CUserCmd* cmd, ValveSDK::CBaseEntity* localPly) {
	static float angle = 0.f;
	static int inv = -1;

	CircleDone = false;

	if (JustStarted) {
		JustStarted = false;
		angle = cmd->viewangles.y;
	}

	ValveSDK::IEngineTrace::Ray_t left_trace;
	ValveSDK::IEngineTrace::Ray_t right_trace;
	ValveSDK::IEngineTrace::Ray_t normal_trace;
	ValveSDK::IEngineTrace::CTraceFilter Filter = ValveSDK::IEngineTrace::CTraceFilter(localPly);
	ValveSDK::Vector EyePos = localPly->GetAbsAngles() + localPly->GetAbsOrigin();

	ValveSDK::Vector vleft = ValveSDK::Vector(10.f, angle - 50.f, 0.f), vright = ValveSDK::Vector(10.f, angle + 50.f, 0.f), vnormal = ValveSDK::Vector(10.f, angle, 0.f), left, right, normal;
	g_pTools->AngleVectors(vright, &right, 0, 0);
	g_pTools->AngleVectors(vleft, &left, 0, 0);
	g_pTools->AngleVectors(vnormal, &normal, 0, 0);

	left_trace.Init(EyePos, EyePos + left * 50.f);
	right_trace.Init(EyePos, EyePos + right * 50.f);
	normal_trace.Init(EyePos, EyePos + normal * 50.f);

	ValveSDK::IEngineTrace::trace_t result_left, result_right, result;	

	g_pEngineTrace->TraceRay(left_trace, MASK_SOLID, &Filter, &result_left);
	g_pEngineTrace->TraceRay(right_trace, MASK_SOLID, &Filter, &result_right);
	g_pEngineTrace->TraceRay(normal_trace, MASK_SOLID, &Filter, &result);
	static int amount;
	amount = 10 + localPly->GetVelocity().Length2D()/50;
	if ((result.fraction != 1.f && !result.m_pEnt) || (result_right.fraction != 1.f && !result_right.m_pEnt)) {
		inv = -1;
		angle -= 30.f;
		cmd->sidemove = -250.f;
	}
	else if (result_left.fraction != 1.f && !result_left.m_pEnt) {
		inv = 1;
		angle += 30.f;
		cmd->sidemove = 250.f;
	}
	else {
		float flAdd = (200 / localPly->GetVelocity().Length2D()) * amount;
		if (flAdd > 5.f) flAdd = 5.f;
		angle += flAdd * (float)inv;
		cmd->sidemove = 250.f * (float)inv;
	}

	AngleNormalize(Global::strafeang.y);

	ValveSDK::Vector noob(0.f, angle - cmd->viewangles.y, 0.f);
	g_pTools->NormalizeVector(noob);

	if (noob.y > 170.f && noob.y < 180.f)
		CircleDone = true;

	Global::strafeang.y = angle;
}
void CMisc::AutoHop(ValveSDK::CUserCmd* cmd, ValveSDK::CBaseEntity * localPly)
{
	static bool OldBool;
	bool CircleStrafe = GetAsyncKeyState('C') & 0x8000 || !CircleDone;

	if (OldBool != CircleStrafe)
		JustStarted = true;

	if (!(cmd->buttons & IN_JUMP)) {
		CircleStrafe = false;
		CircleDone = true;
		JustStarted = true;
		return;
	}

	OldBool = CircleStrafe;


	if (!(localPly->GetFlags() & FL_ONGROUND) || (localPly->GetFlags() & FL_INWATER) && cmd->buttons & IN_JUMP) {
		if (g_CVars.GetCVar("misc_autohop")->GetBool())
		{
			cmd->buttons &= ~IN_JUMP;
		}
		if (CircleStrafe && g_CVars.GetCVar("misc_circlestrafer")->GetBool()) {
			CircleStrafer(cmd, localPly);
			return;
		}
		if (g_CVars.GetCVar("misc_autostrafe")->GetBool())
		{
			if (cmd->mousedx > 1 || cmd->mousedx < -1) {
				cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else {
				cmd->forwardmove = (1800.f * 4.f) / localPly->GetVelocity().Length2D();
				cmd->sidemove = (cmd->command_number % 2) == 0 ? -450.f : 450.f;
				if (cmd->forwardmove > 450.f)
					cmd->forwardmove = 450.f;
			}	
		}
	}
	else {
		if (g_CVars.GetCVar("misc_autostrafe")->GetBool())
		{
			if (cmd->buttons & IN_JUMP && !CircleStrafer) {
				cmd->forwardmove = 450.f;
			}
		}
	}
}
int FakelagTick = 0;
void CMisc::FakeLag(ValveSDK::CUserCmd* pCmd, bool& bSendPacket)
{
	if (pCmd->command_number == 0) return;
	int flagval = g_CVars.GetCVar("misc_fakelagval")->GetFloat();
	static int FakelagFactor = 8;
	FakelagTick++;
	bSendPacket = g_CVars.GetCVar("misc_fakelag")->GetBool() ? !(FakelagTick % (FakelagFactor + 1)) : 1;
	if (bSendPacket) {
		FakelagFactor = (rand() % 10) + 3;
	}
}
bool CMisc::IsVisible(ValveSDK::Vector& StartPos, ValveSDK::Vector& EndPos, ValveSDK::CBaseEntity* localPly, ValveSDK::CBaseEntity* pEnt)
{
	ValveSDK::IEngineTrace::trace_t tr;
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::Vector vStart, vEnd, vEndPos[3];
	vStart = StartPos;
	vEnd = EndPos;
	ValveSDK::IEngineTrace::CTraceFilterSkipTwoEntities filter = ValveSDK::IEngineTrace::CTraceFilterSkipTwoEntities(localPly, pEnt);

	ray.Init(vStart, vEnd);
	g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

	if (tr.fraction == 1.f || tr.m_pEnt == pEnt) return true;

	if (!g_CVars.GetCVar("rage_autowall")->GetBool()) return false;

	vEndPos[0] = tr.endpos;

	ray.Init(vEnd, vStart);
	g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

	vEndPos[1] = tr.endpos;

	VectorSubtract(vEndPos[0], vEndPos[1], vEndPos[2]);

	float flLength = vEndPos[2].Length();

	if (tr.fraction != 0)
		if (flLength < 14)
			return true;

	return false;

}

float getyaw(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity* pLocal, float setyaw)
{
	if (g_CVars.GetCVar("misc_antiaimAT")->GetBool() && g_CVars.GetCVar("misc_yaw")->GetInt() != 16 || g_CVars.GetCVar("customaa_attarget")->GetBool() && g_CVars.GetCVar("misc_yaw")->GetInt() == 16)
	{
		auto pWeapon = pLocal->GetWeapon();
		float targ = Global::targ;
		if (targ == -1)
		{
			targ = g_pTools->AATARGE(pCmd, pLocal, pWeapon);
		}
		if (targ != -1)
		{
			if (g_pTools->IsValidTARGET(targ, pLocal))
			{
				auto pBaseEntity = g_pEntityList->GetBaseEntity(targ);

				if (pBaseEntity)
				{

					ValveSDK::Vector vecHit = pBaseEntity->GetHitboxPosition(g_CVars.GetCVar("rage_hitbox")->GetInt());
					if (vecHit != ValveSDK::Vector(0, 0, 0))
					{

						ValveSDK::QAngle qClientViewAngles;
						g_pEngine->GetViewAngles(qClientViewAngles);

						ValveSDK::Vector vForward;
						g_pTools->AngleVectors(qClientViewAngles, vForward);

						ValveSDK::Vector qAimAngles;
						g_pTools->CalcAngle(pLocal->GetEyePosition(), vecHit, qAimAngles);

						g_pTools->NormalizeVector(qAimAngles);
						pCmd->viewangles.y = qAimAngles.y;
						return qAimAngles.y;
					}
				}
			}
		}
	}
	return 0;
}
bool WallDetection(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity* localPly) {
	ValveSDK::Vector eyepos = localPly->GetAbsAngles() + localPly->GetAbsOrigin();
	ValveSDK::Vector tmp = ValveSDK::Vector(10.f, 0.f, 0.f);
	float lowestFraction = 1.f;

	for (float y = 0.f; y < 360.f; y += 2.f) {
		tmp.y = y;
		ValveSDK::IEngineTrace::Ray_t ray;
		ValveSDK::Vector forward;
		ValveSDK::IEngineTrace::trace_t result;
		g_pTools->AngleVectors(tmp, &forward, 0, 0);
		ray.Init(eyepos, eyepos + (forward * 27.3f));

		ValveSDK::IEngineTrace::CTraceFilter Filter = ValveSDK::IEngineTrace::CTraceFilter(localPly);

		g_pEngineTrace->TraceRay(ray, 0x200400B, &Filter, &result);

		if (result.fraction < lowestFraction) {
			lowestFraction = result.fraction;
			pCmd->viewangles.y = tmp.y;

			ValveSDK::Vector left, right;
			ValveSDK::Vector vleft = ValveSDK::Vector(10.f, y + 25.f, 0.f);
			ValveSDK::Vector vright = ValveSDK::Vector(10.f, y - 25.f, 0.f);

			g_pTools->AngleVectors(vleft, &left, 0, 0);
			g_pTools->AngleVectors(vright, &right, 0, 0);

			ValveSDK::IEngineTrace::Ray_t trace_left, trace_right;

			trace_left.Init(eyepos, eyepos + (left * 46.f));
			trace_right.Init(eyepos, eyepos + (right * 46.f));

			ValveSDK::IEngineTrace::trace_t result_left, result_right;

			g_pEngineTrace->TraceRay(trace_left, 0x200400B, &Filter, &result_left);
			g_pEngineTrace->TraceRay(trace_right, 0x200400B, &Filter, &result_right);

			if (result_left.fraction == 1.f && result_right.fraction != 1.f)
				pCmd->viewangles.y -= 45.f;
			else if (result_right.fraction == 1.f && result_left.fraction != 1.f)
				pCmd->viewangles.y += 45.f;
		}
	}

	return lowestFraction != 1.f;
}
void CMisc::HandleNames(const char *name)
{
	ValveSDK::ConVar* Name = g_pICvar->FindVar("name");
	static int TickCounter = 0;

	if (TickCounter > 0 && TickCounter < 100)
		Name->SetValue("1337Dank.COM");
	else if (TickCounter > 100 && TickCounter < 200)
		Name->SetValue(" 1337Dank.CO");
	else if (TickCounter > 200 && TickCounter < 300)
		Name->SetValue("  1337Dank.C");
	else if (TickCounter > 300 && TickCounter < 400)
		Name->SetValue("   1337Dank.");
	else if (TickCounter > 400 && TickCounter < 500)
		Name->SetValue("    1337Dank");
	else if (TickCounter > 500 && TickCounter < 600)
		Name->SetValue("     1337Dan");
	else if (TickCounter > 600 && TickCounter < 700)
		Name->SetValue("      1337Da");
	else if (TickCounter > 700 && TickCounter < 800)
		Name->SetValue("       1337Da");
	else if (TickCounter > 800 && TickCounter < 900)
		Name->SetValue("        1337D");
	else if (TickCounter > 900 && TickCounter < 1000)
		Name->SetValue("         1337");
	else if (TickCounter > 1000 && TickCounter < 1100)
		Name->SetValue("          133");
	else if (TickCounter > 1100 && TickCounter < 1200)
		Name->SetValue("           133");
	else if (TickCounter > 1200 && TickCounter < 1300)
		Name->SetValue("            13");
	else if (TickCounter > 1300 && TickCounter < 1400)
		Name->SetValue("             1");
	if (TickCounter > 3500)
		TickCounter = 0;
	TickCounter += 6;
}
float DegreesToRadians(float Angle)
{
	return Angle * M_PI / 180.0f;
}
bool jitter = false;
int spin = 0;
void CMisc::Pitch(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity * pLocal, bool& bSendPacket)
{
	int Pitch = g_CVars.GetCVar("misc_aa")->GetInt();
	int choked = g_CVars.GetCVar("customaa_chokedticks")->GetInt();
	float customrealpitch = g_CVars.GetCVar("customaa_realanglex")->GetInt();
	float customfakepitch = g_CVars.GetCVar("customaa_fakeanglex")->GetInt();
	int modeAA = g_CVars.GetCVar("customaa_mode")->GetInt();
	int add = pCmd->viewangles.x;



	float setpitch = pCmd->viewangles.x;
	static int ticks;
	static bool mode;
	mode = pCmd->command_number % 2;

	if (Pitch == 1) setpitch = 89;
	if (Pitch == 2) setpitch = 179.99999947f;
	if (Pitch == 3) setpitch = 36000089.f;
	if (Pitch == 4) setpitch = 35999912.f;
	if (Pitch == 5) setpitch = 35999820.f;
	if (Pitch == 6)
	{
		if (modeAA == 0)
		{

			if (ticks >= choked)
			{
				if (!bSendPacket) setpitch = customfakepitch;
				ticks = 0;
			}
			else
			{
				setpitch = customrealpitch;
			}
			if (!bSendPacket)
				ticks++;
		}
		if (modeAA == 1)
		{
			setpitch = (pCmd->command_number % 2 ? customrealpitch : customfakepitch);
			if (ticks >= choked)
			{
				if (!bSendPacket) setpitch = (pCmd->command_number % 2 ? customrealpitch : customfakepitch);
				ticks = 0;
			}
			else
			{
				setpitch = customrealpitch;
			}
			if (!bSendPacket)
				ticks++;
		}
		if (modeAA == 2)
		{
			
			if (ticks >= choked)
			{
				if (!bSendPacket) setpitch = 11796880 + (pCmd->command_number % 2 ? customfakepitch + rand() % 2 : customfakepitch);
				ticks = 0;
			}
			else
			{
				setpitch = 11796880 + customrealpitch;
			}
			if (!bSendPacket)
				ticks++;
		}
		if (modeAA == 3)
		{
			
			if (ticks >= choked)
			{
				if (!bSendPacket) setpitch = (pCmd->command_number % 2 ? customrealpitch : customfakepitch);
				ticks = 0;
			}
			else
			{
				setpitch = customrealpitch;
			}
			if (!bSendPacket)
				ticks++;
		}
		if (modeAA == 4)
		{
			if (ticks >= choked)
			{
				if (!bSendPacket) setpitch = customfakepitch;
				ticks = 0;
			}
			else
			{
				setpitch = customrealpitch;
			}
			if (!bSendPacket)
				ticks++;
		}
	}
	pCmd->viewangles.x = setpitch;
}

void CMisc::Yaw(ValveSDK::CUserCmd* pCmd, ValveSDK::CBaseEntity * pLocal, bool& bSendPacket)
{
	int Yaw = g_CVars.GetCVar("misc_yaw")->GetInt();
	int choked = g_CVars.GetCVar("customaa_chokedticks")->GetInt();
	float customrealyaw = g_CVars.GetCVar("customaa_realangley")->GetFloat();
	float customfakeyaw = g_CVars.GetCVar("customaa_fakeangley")->GetFloat();
	int modeAA = g_CVars.GetCVar("customaa_mode")->GetInt();
	static int ticks;
	getyaw(pCmd, pLocal, pCmd->viewangles.y);
	float setyaw = pCmd->viewangles.y;
	static bool mode;
	static bool twitch;
	static int Command2;
	static int Command3;
	static int CommandAdd;
	static bool flip;
	mode = (!bSendPacket) ? !mode : mode;
	twitch = (bSendPacket) ? !twitch : twitch;
	flip = !flip;
	Command2 = pCmd->command_number % 2;
	Command3 = pCmd->command_number % 3;
	CommandAdd += 185;
	if (CommandAdd > 10000)
		CommandAdd = 0;
	if (Yaw == 1) setyaw += 180;
	if (Yaw == 2) setyaw += ( bSendPacket ? 180 : 0);
	if (Yaw == 3) setyaw += ( bSendPacket ? 90 : -90);
	if (Yaw == 4) setyaw += ( bSendPacket ? 0 : 180);
	if (Yaw == 5) setyaw += (Command2 ? flip ? -179.990005f : 180.f : !flip ? 0.990005f : 0.f);
	if (Yaw == 6) setyaw += ((Command2 ? 60.f : -60.f) * ((bSendPacket) ? 1.f : -1.f));
	if (Yaw == 7) setyaw += (Command2 ? flip ? -180.f : 90.f : !flip ? -90.f : 180.f);
	if (Yaw == 8) setyaw += CommandAdd^Global::missedshots;
	if (Yaw == 9) setyaw += ( Command2 ? bSendPacket ? 140 : -120 : !bSendPacket ? 75 : -180);
	if (Yaw == 10) setyaw += ( bSendPacket ? g_pGlobalVarsBase->curtime * 8 : fmod(DegreesToRadians(g_pGlobalVarsBase->framecount * g_pGlobalVarsBase->curtime), 360));
	if (Yaw == 11) setyaw += 11796880 + rand() % 90 + (Command2 ? flip ? -179.990005f : 180.f : !flip ? 0.990005f : 0.f);
	if (Yaw == 12) setyaw += 11796880 + (bSendPacket ? 180 : 0);
	if (Yaw == 13) setyaw += 11796880 + (bSendPacket ? 90 : -90);
	if (Yaw == 14) setyaw += 11796880 + (Command2 ? flip ? -179.990005f : 180.f : !flip ? 0.990005f : 0.f);
	if (Yaw == 15) setyaw += 11796880 + g_pGlobalVarsBase->curtime * 60;
	//pCVar->AddArg("Add", 0);
	//pCVar->AddArg("Jitter", 1);
	//pCVar->AddArg("Lisp", 2);
	//pCVar->AddArg("Spin", 3);
	//pCVar->AddArg("Static", 4);
	float added;
	added += (pCmd->command_number % 2 ? customrealyaw : customfakeyaw);
	if (Yaw == 16)
	{
		if (modeAA == 0)
		{
			setyaw += customrealyaw;
		}
		if (modeAA == 1)
		{
			setyaw += (pCmd->command_number % 2 ? customrealyaw : customfakeyaw);
		}
		if (modeAA == 2)
		{
			setyaw += 11796880 + (pCmd->command_number % 2 ? customrealyaw : customfakeyaw);
		}
		if (modeAA == 3)
		{
			setyaw += added;
		}
		if (modeAA == 4)
		{
			if (ticks > choked)
			{
				if (!bSendPacket) setyaw += customfakeyaw;
				ticks = 0;
			}
			else
			{
				setyaw += customrealyaw;
			}
			if (!bSendPacket)
				ticks++;
		}
	}
	pCmd->viewangles.y = setyaw;
}

CMisc* g_pMisc = nullptr;