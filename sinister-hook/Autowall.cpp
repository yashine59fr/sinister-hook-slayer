#include "AutoWall.h"
//#include "R.h"

#define    HITGROUP_GENERIC    0
#define    HITGROUP_HEAD        1
#define    HITGROUP_CHEST        2
#define    HITGROUP_STOMACH    3
#define HITGROUP_LEFTARM    4    
#define HITGROUP_RIGHTARM    5
#define HITGROUP_LEFTLEG    6
#define HITGROUP_RIGHTLEG    7
#define HITGROUP_GEAR        10



//bool HandleBulletPenetration(ValveSDK::CWeaponData *wpn_data, FireBulletData &data);

float GetHitgroupDamageMult(int iHitGroup)
{
	switch (iHitGroup)
	{
	case HITGROUP_GENERIC:
		return 1.0f;

	case HITGROUP_HEAD:
		return 2.0f;

	case HITGROUP_CHEST:
		return 1.0f;

	case HITGROUP_STOMACH:
		return 1.0f;

	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM:
		return 1.0f;

	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		return 1.0f;

	default:
		return 1.0f;
	}
}

void ScaleDamage(int hitgroup, ValveSDK::CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage)
{
	current_damage *= GetHitgroupDamageMult(hitgroup);

	if (enemy->GetArmorValue() > 0)
	{
		if (hitgroup == HITGROUP_HEAD)
		{
			if (enemy->HasHelmet())
				current_damage *= (weapon_armor_ratio * .5f);
		}
		else
		{
			current_damage *= (weapon_armor_ratio * .5f);
		}
	}
}
void UTIL_ClipTraceToPlayers(const ValveSDK::Vector& vecAbsStart, const ValveSDK::Vector& vecAbsEnd, unsigned int mask, ValveSDK::IEngineTrace::ITraceFilter* filter, ValveSDK::IEngineTrace::trace_t* tr)
{
	static DWORD dwAddress = g_pTools->FindPattern("client.dll", (BYTE*)"\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x81\xEC\x00\x00\x00\x00\x8B\x43\x10", "xxxxxxxxxxxxxxxxxxxxxxxx????xxx");

	if (!dwAddress)
		return;

	_asm
	{
		MOV		EAX, filter
		LEA		ECX, tr
		PUSH	ECX
		PUSH	EAX
		PUSH	mask
		LEA		EDX, vecAbsEnd
		LEA		ECX, vecAbsStart
		CALL	dwAddress
		ADD		ESP, 0xC
	}
}
bool HandleBulletPenetration(ValveSDK::CWeaponData *wpn_data, FireBulletData &data)
{
	ValveSDK::surfacedata_t *enter_surface_data = g_pPhysSurface->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = enter_surface_data->game.flPenetrationModifier;


	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow(wpn_data->m_flRangeModifier, (data.trace_length * 0.002));

	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	ValveSDK::Vector dummy;
	ValveSDK::IEngineTrace::trace_t trace_exit;
	if (!g_pTools->TraceToExit(dummy, &data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit))
		return false;

	ValveSDK::surfacedata_t *exit_surface_data = g_pPhysSurface->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	float exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;

	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
	{
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
	}

	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->m_flPenetration) * 1.25f);
	float thickness = VectorLength(trace_exit.endpos - data.enter_trace.endpos);

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;


	float lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

bool SimulateFireBullet(ValveSDK::CBaseEntity *local, ValveSDK::CBaseCombatWeapon *weapon, FireBulletData &data)
{
	//Utils::ToLog("SimulateFireBullet");
	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	auto *wpn_data = weapon->GetWeaponData();

	data.current_damage = (float)wpn_data->m_iDamage;

	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
	{
		data.trace_length_remaining = wpn_data->m_flRange - data.trace_length;

		ValveSDK::Vector end = data.src + data.direction * data.trace_length_remaining;

		g_pTools->UTIL_TraceLine(data.src, end, 0x4600400B, local, &data.enter_trace);
		UTIL_ClipTraceToPlayers(data.src, end + data.direction * 40.f, 0x4600400B, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if ((data.enter_trace.hitgroup <= 7)
			&& (data.enter_trace.hitgroup > 0)
			&& (local->GetTeam() != data.enter_trace.m_pEnt->GetTeam())
			/*&& (DoesRayTouchHitbox(end, &data))*/)
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= pow(wpn_data->m_flRangeModifier, data.trace_length * 0.002);
			ScaleDamage(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, wpn_data->m_flArmorRatio, data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration(wpn_data, data))
			break;
	}

	return false;
}


void AngleVectors(const ValveSDK::Vector &angles, ValveSDK::Vector *forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}
/*
*    CanHit() - example of how to use the code
*     @in  point: target hitbox vector
*     @out damage_given: amount of damage the shot would do
*/
bool CanHit(const ValveSDK::Vector &point, float *damage_given)
{
	auto *local = g_pEntityList->GetBaseEntity(g_pEngine->GetLocalPlayer());
	auto data = FireBulletData(local->GetEyePosition());
	data.filter = ValveSDK::IEngineTrace::CTraceFilter();
	data.filter.pSkip = local;

	ValveSDK::Vector angles;
	g_pTools->CalcAngle(data.src, point, angles);
	AngleVectors(angles, &data.direction);
	VectorNormalize(data.direction);

	if (SimulateFireBullet(local, (ValveSDK::CBaseCombatWeapon*)g_pEntityList->GetBaseEntityFromHandle((ValveSDK::EHANDLE)local->GetActiveWeapon()), data))
	{
		*damage_given = data.current_damage;
		return true;
	}

	return false;
}