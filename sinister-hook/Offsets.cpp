#include "Offsets.h"
#include "NetVars.h"
#include <Psapi.h>
namespace Offsets
{
	DWORD m_bIsBroken = 0;
	DWORD m_bGunGameImmunity = 0;
	DWORD m_bIsDefusing = 0;
	DWORD m_bIsScoped = 0;
	DWORD m_bHasHelmet = 0;
	DWORD m_moveType = 0;
	DWORD m_fFlags = 0;
	DWORD m_lifeState = 0;
	DWORD m_hActiveWeapon = 0;
	DWORD m_hMyWeapons = 0;
	DWORD m_hViewModel = 0;
	DWORD m_hOwnerEntity = 0;
	DWORD m_ArmorValue = 0;
	DWORD m_CollisionGroup = 0;
	DWORD m_iAccount = 0;
	DWORD m_iShotsFired = 0;
	DWORD m_iTeamNum = 0;
	DWORD m_iHealth = 0;
	DWORD m_nHitboxSet = 0;
	DWORD m_nTickBase = 0;
	DWORD m_viewPunchAngle = 0;
	DWORD m_aimPunchAngle = 0;
	DWORD m_flLowerBodyYawTarget = 0;
	DWORD m_hObserverTarget = 0;
	DWORD m_vecOrigin = 0;
	DWORD m_vecViewOffset = 0;
	DWORD m_vecVelocity = 0;
	DWORD m_iItemDefinitionIndex = 0;
	DWORD m_OriginalOwnerXuidLow = 0;
	DWORD m_OriginalOwnerXuidHigh = 0;
	DWORD m_nFallbackPaintKit = 0;
	DWORD m_nFallbackSeed = 0;
	DWORD m_flFallbackWear = 0;
	DWORD m_iItemIDHigh = 0;
	DWORD m_nFallbackStatTrak = 0;
	DWORD m_szCustomName = 0;
	DWORD m_iClip1 = 0;
	DWORD m_iClip2 = 0;
	DWORD m_iState = 0;
	DWORD m_flNextPrimaryAttack = 0;
	DWORD m_flNextSecondaryAttack = 0;
	DWORD m_dwLoadFromBuffer = 0;
	DWORD m_iEntityQuality = 0;
	DWORD m_angEyeAngles = 0;
	DWORD m_angEyeAnglesX = 0;
	DWORD m_angEyeAnglesY = 0;
	DWORD m_hWeapon = 0;
	DWORD m_nModelIndex = 0;
	DWORD m_hOwner = 0;
	DWORD m_iDidCheckForOcclusion = 0;
	DWORD m_dOcclusionArray = 0;
	DWORD m_nWriteableBones = 0;
	DWORD InvalidateBoneCache = 0;
	DWORD m_iViewModelIndex = 0;
	DWORD m_hWorldModel = 0;
}
uint64_t FindPatternIDA(const char* szModule, const char* szSignature)
{
	//CREDITS: learn_more
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
	DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
	DWORD endAddress = startAddress + modInfo.SizeOfImage;
	const char* pat = szSignature;
	DWORD firstMatch = 0;
	for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;    //one ?
		}
		else {
			pat = szSignature;
			firstMatch = 0;
		}
	}
	return NULL;
}


void InitOffsets( void )
{
	Offsets::m_bIsDefusing = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bIsDefusing" );
	Offsets::m_bIsBroken = g_pNetVars->GetOffset( "DT_BreakableSurface", "m_bIsBroken" );
	Offsets::m_bIsScoped = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bIsScoped" );
	Offsets::m_bGunGameImmunity = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bGunGameImmunity" );
	Offsets::m_bHasHelmet = g_pNetVars->GetOffset( "DT_CSPlayer", "m_bHasHelmet" );
	Offsets::m_moveType = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nRenderMode" ) + 0x1;
	Offsets::m_fFlags = g_pNetVars->GetOffset( "DT_CSPlayer", "m_fFlags" );
	Offsets::m_lifeState = g_pNetVars->GetOffset( "DT_CSPlayer", "m_lifeState" );
	Offsets::m_hActiveWeapon = g_pNetVars->GetOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	Offsets::m_hMyWeapons = g_pNetVars->GetOffset( "DT_BasePlayer", "m_hMyWeapons");
	Offsets::m_hViewModel = g_pNetVars->GetOffset( "DT_BasePlayer", "m_hViewModel");
	Offsets::m_iViewModelIndex = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");

	Offsets::m_hOwnerEntity = g_pNetVars->GetOffset( "DT_CSPlayer", "m_hOwnerEntity" );
	Offsets::m_ArmorValue = g_pNetVars->GetOffset( "DT_CSPlayer", "m_ArmorValue" );
	Offsets::m_CollisionGroup = g_pNetVars->GetOffset( "DT_PlantedC4", "m_CollisionGroup" );
	Offsets::m_iShotsFired = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iShotsFired" );
	Offsets::m_iAccount = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iAccount" );
	Offsets::m_iTeamNum = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iTeamNum" );
	Offsets::m_iHealth = g_pNetVars->GetOffset( "DT_CSPlayer", "m_iHealth" );
	Offsets::m_nHitboxSet = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nHitboxSet" );
	Offsets::m_angEyeAnglesX = g_pNetVars->GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
	Offsets::m_angEyeAnglesY = g_pNetVars->GetOffset("DT_CSPlayer", "m_angEyeAngles[1]");
	Offsets::m_nTickBase = g_pNetVars->GetOffset( "DT_CSPlayer", "m_nTickBase" );
	Offsets::m_viewPunchAngle = g_pNetVars->GetOffset( "DT_CSPlayer", "m_viewPunchAngle" );
	Offsets::m_aimPunchAngle = g_pNetVars->GetOffset( "DT_CSPlayer", "m_aimPunchAngle" );
	Offsets::m_flLowerBodyYawTarget = g_pNetVars->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
	Offsets::m_hObserverTarget = g_pNetVars->GetOffset("DT_CSPlayer", "m_hObserverTarget");
	Offsets::m_iItemDefinitionIndex = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_iItemDefinitionIndex" );
	Offsets::m_nFallbackPaintKit = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_nFallbackPaintKit" );
	Offsets::m_nFallbackSeed = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_nFallbackSeed" );
	Offsets::m_OriginalOwnerXuidLow = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	Offsets::m_OriginalOwnerXuidHigh = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	Offsets::m_flFallbackWear = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_flFallbackWear" );
	Offsets::m_iItemIDHigh = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_iItemIDHigh" );
	Offsets::m_nFallbackStatTrak = g_pNetVars->GetOffset( "DT_BaseAttributableItem", "m_nFallbackStatTrak" );
	Offsets::m_szCustomName = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_szCustomName");
	Offsets::m_iEntityQuality = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
	Offsets::m_iClip1 = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iClip1" );
	Offsets::m_iClip2 = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iClip2" );
	Offsets::m_iState = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_iState" );
	Offsets::m_flNextPrimaryAttack = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	Offsets::m_flNextSecondaryAttack = g_pNetVars->GetOffset( "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
	Offsets::m_hWeapon = g_pNetVars->GetOffset( "DT_BaseViewModel", "m_hWeapon" );
	Offsets::m_nModelIndex = g_pNetVars->GetOffset( "DT_BaseViewModel", "m_nModelIndex" );
	Offsets::m_hOwner = g_pNetVars->GetOffset( "DT_BaseViewModel", "m_hOwner" );
	Offsets::m_hWorldModel = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
	Offsets::m_nWriteableBones = g_pNetVars->GetOffset("DT_CSPlayer", "m_nForceBone") + 0x20;
	Offsets::m_dOcclusionArray = *(uintptr_t*)(FindPatternIDA("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0x1); //ida
	Offsets::m_iDidCheckForOcclusion = *(uintptr_t*)(FindPatternIDA("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0xE); //ida
	Offsets::InvalidateBoneCache = FindPatternIDA("client.dll", "80 3D ? ? ? ? 00 74 16 A1"); //ida
	//Offsets::m_iDidCheckForOcclusion = g_pNetVars->GetOffset("DT_CSPlayer", "m_iDidCheckForOcclusion");
	//Offsets::m_dOcclusionArray = g_pNetVars->GetOffset("DT_CSPlayer", "m_dOcclusionArray");
	//Offsets::m_nWriteableBones = g_pNetVars->GetOffset("DT_CSPlayer", "m_nWriteableBones");
	Offsets::m_vecOrigin = 0x134;
	Offsets::m_vecViewOffset = 0x104;
	Offsets::m_vecVelocity = 0x110;
}