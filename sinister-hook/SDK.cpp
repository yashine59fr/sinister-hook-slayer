#include "SDK.h"
#include "Autowall.h"
#define MAT( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$ignorez\" \"0\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"
#define MAT_IGNOREZ( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$ignorez\" \"1\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"

typedef float( *RandomFloat_t )( float, float );
typedef void( *RandomSeed_t )( UINT );

using namespace ValveSDK;

namespace Global
{
	ValveSDK::QAngle VisualAngle;
	ValveSDK::QAngle pLocalAngles;
	ValveSDK::QAngle strafeang;
	ValveSDK::QAngle velocity;
	ValveSDK::QAngle AAA;
	ValveSDK::CBaseEntity *GlobalpLocal;
	float OldSimulationTime[65];
	int missedshots;
	int maxmissedshots = 3;
	bool retarget = false;
	bool retargetplayer[65];
	int missedticks;
	int chokedticks;
	int iSelectedPlayer;
	bool SelectedPlayerIgnore[65] = { false };
	int renderedticks;
	int predictedticks;
	int command_number;
	bool strafing = false;
	int command;
	float yAAA = 0;
	float xAAA = 0;
	int targ = -1;
	bool xSwitch = false;
	bool aiming = false;
	bool bSendPacket;
}

void GenerateRandomString(char *s, const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

CTools::CTools(void)
{

}

bool CTools::IsValidTARGET(int iEnt, ValveSDK::CBaseEntity* pLocal)
{
	ValveSDK::CBaseEntity* pEnt = nullptr;

	if ((pEnt = g_pEntityList->GetBaseEntity(iEnt)))
		if (!(pEnt == pLocal))
		{
			if (pEnt->GetTeam() != pLocal->GetTeam())
				if (!pEnt->IsDormant())
					if (pEnt->GetHealth() > 0)
						return true;
		}
	return false;
}
int CTools::AATARGE(ValveSDK::CUserCmd *pCmd, ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pWeapon)
{
	int target = -1;
	int minDist = 99999;


	ValveSDK::Vector ViewOffset = pLocalEntity->GetEyePosition();
	ValveSDK::Vector View; g_pEngine->GetViewAngles(View);

	for (int i = 0; i < g_pEntityList->GetHighestEntityIndex(); i++)
	{
		ValveSDK::CBaseEntity* pEntity = g_pEntityList->GetBaseEntity(i);
		if (IsValidTARGET(i, pLocalEntity))
		{
			//ValveSDK::Vector Difference = pLocalEntity->GetAbsOrigin() - pEntity->GetAbsOrigin();
			target = i;
		}
	}
	return target;

}
#include "Aimbot.h"
ValveSDK::Vector vecHit;
int hitboxes[7] =
{
	HITBOX_HEAD,
	HITBOX_CHEST,
	HITBOX_PELVIS,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF
};
bool CTools::IsValids(int iEnt, ValveSDK::CBaseEntity* pLocal, ValveSDK::CUserCmd *pCmd)
{
	int hitbox = g_pAimbot->Bone();

	auto pBaseEntity = g_pEntityList->GetBaseEntity(iEnt);

	if (!pBaseEntity)
		return false;

		if (!(pBaseEntity == pLocal))
		{

			if (pBaseEntity->GetTeam() != pLocal->GetTeam())
				if (!pBaseEntity->IsDormant())
					if (pBaseEntity->GetHealth() > 0)
						if (!pBaseEntity->IsProtected() && g_pTools->IsVisible(pLocal->GetEyePosition(), pBaseEntity->GetHitboxPosition(hitbox), pLocal, pBaseEntity))
						{

							return true;

						}
		}
	
	return false;
}
bool CTools::NonVisIsValid(int iEnt, ValveSDK::CBaseEntity* pLocal)
{
	ValveSDK::CBaseEntity* pEnt = nullptr;

	if ((pEnt = g_pEntityList->GetBaseEntity(iEnt)))
		if (!(pEnt == pLocal))
		{
			if (pEnt->GetTeam() != pLocal->GetTeam())
				if (!pEnt->IsDormant())
					if (pEnt->GetHealth() > 0)
							return true;
						
		}
	return false;
}
void CTools::NormalizeDelta(ValveSDK::Vector &vIn, ValveSDK::Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

float CTools::GetFov(ValveSDK::Vector ViewOffSet, ValveSDK::Vector View, ValveSDK::CBaseEntity* pEntity, int aHitBox)
{
	// Anything past 180 degrees is just going to wrap around
	CONST FLOAT MaxDegrees = 180.0f;

	// Get local angles
	ValveSDK::Vector Angles = View;

	// Get local view / eye position
	ValveSDK::Vector Origin = ViewOffSet;

	// Create and intiialize vectors for calculations below
	ValveSDK::Vector Delta(0, 0, 0);
	//Vector Origin(0, 0, 0);
	ValveSDK::Vector Forward(0, 0, 0);

	// Convert angles to normalized directional forward vector
	g_pTools->AngleVectors(Angles, Forward);
	ValveSDK::Vector AimPos = pEntity->GetHitboxPosition(aHitBox);
	// Get delta vector between our local eye position and passed vector
	VectorSubtract(AimPos, Origin, Delta);
	//Delta = AimPos - Origin;

	// Normalize our delta vector
	NormalizeDelta(Delta, Delta);

	// Get dot product between delta position and directional forward vectors
	FLOAT DotProduct = Forward.Dot(Delta);

	// Time to calculate the field of view
	return (acos(DotProduct) * (MaxDegrees / 3.14159265358979323846f));
}

ULONG CTools::FindPatternAlt(std::string szModuleName, PBYTE pbPattern, std::string szMask, ULONG uCodeBase, ULONG uSizeOfCode)
{
	BOOL bPatternDidMatch = FALSE;
	HMODULE hModule = GetModuleHandleA(szModuleName.c_str());

	if (!hModule)
		return 0x0;

	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(LONG(hModule) + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

	if (uCodeBase == 0x0)
		uCodeBase = (ULONG)hModule + pOptionalHeader->BaseOfCode;

	if (uSizeOfCode == 0x0)
		uSizeOfCode = pOptionalHeader->SizeOfCode;

	ULONG uArraySize = szMask.length();

	if (!uCodeBase || !uSizeOfCode || !uArraySize)
		return 0x0;

	for (size_t i = uCodeBase; i <= uCodeBase + uSizeOfCode; i++)
	{
		for (size_t t = 0; t < uArraySize; t++)
		{
			if (*((PBYTE)i + t) == pbPattern[t] || szMask.c_str()[t] == '?')
				bPatternDidMatch = TRUE;

			else
			{
				bPatternDidMatch = FALSE;
				break;
			}
		}

		if (bPatternDidMatch)
			return i;
	}

	return 0x0;
}


bool CTools::GetHitboxVector(CBaseEntity* pBaseEntity, int iBone, Vector& vecHitbox)
{
	if (!pBaseEntity)
		return false;

	matrix3x4_t boneMatrixes[128];
	if (pBaseEntity->SetupBones(boneMatrixes, 128, 0x100, 0))
	{
		
		matrix3x4_t boneMatrix = boneMatrixes[iBone];
		vecHitbox = Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
		return true;
	}
	else return false;
}

void CTools::VectorTransform(Vector& in1, matrix3x4a_t& in2, Vector &out)
{
	out.x = in1.Dots(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dots(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dots(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}


void CTools::AngleVectors(const ValveSDK::Vector &angles, ValveSDK::Vector *forward, ValveSDK::Vector *right, ValveSDK::Vector *up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void CTools::Normalize(ValveSDK::Vector &vIn, ValveSDK::Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}
bool CTools::GetHitboxVector2(CBaseEntity* target, int iBone, Hitbox* hitbox)
{
	matrix3x4a_t matrix[128];

	if (!target->SetupBones(matrix, 128, 0x00000100, 0))
		return false;


	studiohdr_t* hdr = g_pModelInfo->GetStudioModel(target->GetModel());

	auto hitboxSet = hdr->pHitboxSet(target->GetHitboxSet());
	auto untransformedBox = hitboxSet->pHitbox(hitbox->hitbox);

	auto bbmin = untransformedBox->bbmin;
	auto bbmax = untransformedBox->bbmax;


	Vector points[] = { ((bbmin + bbmax) * .5f),
		Vector(bbmin.x, bbmin.y, bbmin.z),
		Vector(bbmin.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmin.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmin.y, bbmax.z),
		Vector(bbmax.x, bbmin.y, bbmax.z) };


	for (auto index = 0; index <= 8; ++index)
	{
		if (index != 0)
			points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);

		VectorTransform(points[index], matrix[untransformedBox->bone], hitbox->points[index]);
	}

	return true;
}

bool CTools::IsAbleToShoot(CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon)
{
	if (!g_pGlobalVarsBase)
		return false;

	if (!pBaseEntity || !pWeapon)
		return false;

	auto flServerTime = (float)pBaseEntity->GetTickBase() * g_pGlobalVarsBase->interval_per_tick;
	auto flNextPrimaryAttack = pWeapon->GetNextPrimaryAttack();

	return(flNextPrimaryAttack < flServerTime);
}

bool CTools::IsBreakableEntity(CBaseEntity* pBaseEntity)
{
	if (!pBaseEntity)
		return false;

	if (pBaseEntity->GetCollisionGroup() != COLLISION_GROUP_PUSHAWAY && pBaseEntity->GetCollisionGroup() != COLLISION_GROUP_BREAKABLE_GLASS && pBaseEntity->GetCollisionGroup() != COLLISION_GROUP_NONE)
		return false;

	if (pBaseEntity->GetHealth() > 200)
		return false;

	IMultiplayerPhysics* pPhysicsInterface = (IMultiplayerPhysics*)pBaseEntity;
	if (pPhysicsInterface)
	{
		if (pPhysicsInterface->GetMultiplayerPhysicsMode() != 1)
			return false;
	}
	else
	{
		if (!pBaseEntity->GetClientClass()->GetName().compare("func_breakable") || !pBaseEntity->GetClientClass()->GetName().compare("func_breakable_surf"))
		{
			if (!pBaseEntity->GetClientClass()->GetName().compare("func_breakable_surf"))
				if (pBaseEntity->IsBroken())
					return false;
		}
		else if (pBaseEntity->PhysicsSolidMaskForEntity() & CONTENTS_PLAYERCLIP)
			return false;
	}

	IBreakableWithPropData* pBreakableInterface = (IBreakableWithPropData*)pBaseEntity;
	if (pBreakableInterface)
		if (pBreakableInterface->GetDmgModBullet() <= 0.0f)
			return false;

	return true;
}

Vector GetBonePosition(int iBone, CBaseEntity* pEntity)
{
	matrix3x4_t boneMatrixes[128];
	if (pEntity->SetupBones(boneMatrixes, 128, 0x100, 0))
	{
		matrix3x4_t boneMatrix = boneMatrixes[iBone];
		return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
	}
	else return Vector(0, 0, 0);
}

Vector GetEyePosition(CBaseEntity* pLocal)
{
	Vector origin = pLocal->GetAbsOrigin();
	Vector offset = *(Vector*)((DWORD)pLocal + Offsets::m_vecViewOffset);

	return(origin + offset);
}

bool CTools::IsVisible(Vector& StartPos, Vector& EndPos, CBaseEntity* localPly, CBaseEntity* pEnt)
{
		IEngineTrace::trace_t tr;
		IEngineTrace::Ray_t ray;
		Vector vStart, vEnd, vEndPos[3];
		vStart = StartPos;
		vEnd = EndPos;
		IEngineTrace::CTraceFilterSkipTwoEntities filter = IEngineTrace::CTraceFilterSkipTwoEntities(localPly, pEnt);
		static bool canhit = false;
		ray.Init(vStart, vEnd);
		g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);

		if (tr.fraction == 1.f || tr.m_pEnt == pEnt) return true;

		if (!g_CVars.GetCVar("rage_autowall")->GetBool()) return false;

		float Damage = 0.f;

		if (CanHit(EndPos, &Damage))
		{
			
			if (Damage >= g_CVars.GetCVar("rage_autowall_damage")->GetFloat())
			{
				return true;
			}
		}
		return false;

}

bool CTools::IsVisibles(int BoneID, CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	Vector vEnd;
	(vEnd = pEntity->GetHitboxPosition(BoneID));

	IEngineTrace::trace_t tr;
	IEngineTrace::Ray_t ray;

	IEngineTrace::CTraceFilter filter;
	filter.pSkip = pLocal;
	ray.Init(pLocal->GetEyePosition(), vEnd);
	g_pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);
	if (!tr.m_pEnt)
		return false;
	if (tr.m_pEnt == pEntity)
		return true;
	return false;
}



bool CTools::TraceDidHitWorld(IEngineTrace::trace_t* pTrace)
{
	if (!g_pEntityList)
		return false;

	return(pTrace->m_pEnt == g_pEntityList->GetBaseEntity(0));
}

bool CTools::TraceDidHitNonWorldEntity(IEngineTrace::trace_t* pTrace)
{
	if (!pTrace)
		return false;

	if (pTrace->m_pEnt == NULL)
		return false;

	if (TraceDidHitWorld(pTrace))
		return false;

	return true;
}
bool DidHitNonWorldEntity(CBaseEntity* m_pEnt)
{
	return m_pEnt != nullptr && m_pEnt == g_pEntityList->GetBaseEntity(0);
}
bool CTools::TraceToExit(Vector& vecEnd, IEngineTrace::trace_t* pEnterTrace, Vector vecStart, Vector vecDir, IEngineTrace::trace_t* pExitTrace)
{
	auto distance = 0.0f;

	while (distance < 90.1f)
	{
		distance += 4.0f;
		vecEnd = vecStart + vecDir * distance;

		auto point_contents = g_pEngineTrace->GetPointContents(vecEnd, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr);
		if (point_contents & MASK_SHOT_HULL && (!(point_contents & CONTENTS_HITBOX)))
			continue;

		auto new_end = vecEnd - (vecDir * 4.0f);

		IEngineTrace::Ray_t ray;
		ray.Init(vecEnd, new_end);
		g_pEngineTrace->TraceRay(ray, 0x4600400B, nullptr, pExitTrace);

		if (pExitTrace->m_pEnt == nullptr)
			return false;

		if (pExitTrace->startSolid && pExitTrace->surface.flags & SURF_HITBOX)
		{
			IEngineTrace::CTraceFilter filter;
			filter.pSkip = pExitTrace->m_pEnt;

			ray.Init(vecEnd, vecStart);
			g_pEngineTrace->TraceRay(ray, 0x600400B, &filter, pExitTrace);

			if ((pExitTrace->fraction < 1.0f || pExitTrace->allSolid) && !pExitTrace->startSolid)
			{
				vecEnd = pExitTrace->endpos;
				return true;
			}

			continue;
		}

		if (!(pExitTrace->fraction < 1.0 || pExitTrace->allSolid || pExitTrace->startSolid) || pExitTrace->startSolid)
		{
			if (pExitTrace->m_pEnt)
			{
				if (!DidHitNonWorldEntity(pExitTrace->m_pEnt))
					return true;
			}

			continue;
		}

		if (((pExitTrace->surface.flags >> 7) & 1) && !((pExitTrace->surface.flags >> 7) & 1))
			continue;

		if (pExitTrace->plane.normal.Dot(vecDir) < 1.1f)
		{
			float fraction = pExitTrace->fraction * 4.0f;
			vecEnd = vecEnd - (vecDir * fraction);

			return true;
		}
	}

	return false;
}

bool CTools::WorldToScreen(const Vector& vecOrigin, Vector& vecScreen)
{
	if (!g_pDebugOverlay)
		return false;

	return(g_pDebugOverlay->ScreenPoint(vecOrigin, vecScreen) != 1);
}

CBaseEntity* CTools::GetLocalPlayer(void)
{
	if (!g_pEntityList || !g_pEngine)
		return nullptr;

	int iIndex = g_pEngine->GetLocalPlayer();
	if (iIndex <= 0 || iIndex > 64)
		return nullptr;

	return g_pEntityList->GetBaseEntity(iIndex);
}

DWORD_PTR CTools::FindPattern(std::string strModuleName, PBYTE pbPattern, std::string strMask, DWORD_PTR nCodeBase, DWORD_PTR nSizeOfCode)
{
	BOOL bPatternDidMatch = FALSE;
	HMODULE hModule = GetModuleHandleA(strModuleName.c_str());

	if (!hModule)
		return 0;

	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(LONG(hModule) + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

	if (!nCodeBase)
		nCodeBase = (ULONG)hModule + pOptionalHeader->BaseOfCode;

	if (!nSizeOfCode)
		nSizeOfCode = pOptionalHeader->SizeOfCode;

	std::size_t nMaskSize = strMask.length();

	if (!nCodeBase || !nSizeOfCode || !nMaskSize)
		return 0;

	for (DWORD_PTR i = nCodeBase; i <= nCodeBase + nSizeOfCode; i++)
	{
		for (size_t t = 0; t < nMaskSize; t++)
		{
			if (*((PBYTE)i + t) == pbPattern[t] || strMask.c_str()[t] == '?')
				bPatternDidMatch = TRUE;

			else
			{
				bPatternDidMatch = FALSE;
				break;
			}
		}

		if (bPatternDidMatch)
			return i;
	}

	return 0;
}

float CTools::DotProduct(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float CTools::DotProduct(const Vector& v1, const Vector& v2)
{
	return DotProduct(&v1.x, &v2.x);
}
double inline __declspec (naked) __fastcall FASTSQRT(double n)
{
	_asm fld qword ptr[esp + 4]
	_asm fsqrt
	_asm ret 8
}
float CTools::GetDistance(const Vector& vecOrigin, const Vector& vecOther)
{
	return FASTSQRT(pow(vecOrigin.x - vecOther.x, 2) + pow(vecOrigin.y - vecOther.y, 2) + pow(vecOrigin.z - vecOther.z, 2));
}

float CTools::GetFoV(const QAngle& qViewAngle, const QAngle& qAimAngle)
{
	Vector ang, aim;

	AngleVectors(qViewAngle, aim);
	AngleVectors(qAimAngle, ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

void NormalizeAngles(QAngle& angles)
{
	while (angles.x > 180.0)
		angles.x -= 360.0;

	while (angles.x < -180.0)
		angles.x += 360.0;

	while (angles.y > 180.0)
		angles.y -= 360.0;

	while (angles.y < -180.0)
		angles.y += 360.0;

	while (angles.z > 180.0)
		angles.z -= 360.0;

	while (angles.z < -180.0)
		angles.z += 360.0;
}


float CTools::GetHitgroupDamageMult(int iHitgroup)
{
	switch (iHitgroup)
	{
	case HITGROUP_GENERIC:
		return 1.f;
	case HITGROUP_HEAD:
		return 4.f;
	case HITGROUP_CHEST:
		return 1.f;
	case HITGROUP_STOMACH:
		return 1.5f;
	case HITGROUP_LEFTARM:
		return 1.f;
	case HITGROUP_RIGHTARM:
		return 1.f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.f;
	default:
		break;
	}

	return 1.f;
}

IMaterial* CTools::CreateMaterial(bool bFullbright, bool bIgnorez)
{
	char pszMaterial[2048];

	std::string strMaterialType = (bFullbright ? "UnlitGeneric" : "VertexLitGeneric");
	std::string strMaterial((bIgnorez ? MAT_IGNOREZ(strMaterialType) : MAT(strMaterialType)));
	sprintf_s(pszMaterial, strMaterial.c_str());

	auto pKeyValues = new KeyValues(strMaterialType.c_str());

	char szMaterialName[128];
	GenerateRandomString(szMaterialName, 17);
	strcat_s(szMaterialName, ".vmt");

	pKeyValues->LoadFromBuffer(pKeyValues, szMaterialName, pszMaterial);

	auto pNewMaterial = g_pMaterialSystem->CreateMaterial(szMaterialName, pKeyValues);

	if (pNewMaterial)
		pNewMaterial->IncrementReferenceCount();

	return pNewMaterial;
}

IMaterial* CTools::CreateMaterial(bool bShouldIgnoreZ, bool bFullBright, bool bIsWireframe)
{
	static int iCreated = 0;

	static const char szTmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$receiveflashlight\" \"1\"\
		\n\t\"$singlepassflashlight\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};

	char szMaterial[512];
	char szBaseType[64];

	if (bFullBright)
	{
		static const char pszBaseType[] = "UnlitGeneric";
		sprintf_s(szMaterial, sizeof(szMaterial), szTmp, pszBaseType, (bShouldIgnoreZ) ? 1 : 0, (bIsWireframe) ? 1 : 0);
		strcpy_s(szBaseType, pszBaseType);
	}
	else
	{
		static const char pszBaseType[] = "VertexLitGeneric";
		sprintf_s(szMaterial, sizeof(szMaterial), szTmp, pszBaseType, (bShouldIgnoreZ) ? 1 : 0, (bIsWireframe) ? 1 : 0);
		strcpy_s(szBaseType, pszBaseType);
	}

	char szName[512];
	sprintf_s(szName, sizeof(szName), "custom_material_%i.vmt", iCreated);

	++iCreated;

	auto pKeyValues = new KeyValues(szBaseType);
	pKeyValues->LoadFromBuffer(pKeyValues, szName, szMaterial);
	auto pCreatedMaterial = g_pMaterialSystem->CreateMaterial(szName, pKeyValues);
	pCreatedMaterial->IncrementReferenceCount();
	return pCreatedMaterial;
}

mstudiobbox_t* CTools::GetHitboxData(CBaseEntity* pBaseEntity, int iHitbox)
{
	if (!g_pModelInfo)
		return nullptr;

	if (iHitbox >= HITBOX_MAX)
		return nullptr;

	const model_t* pModel = pBaseEntity->GetModel();
	if (!pModel)
		return nullptr;

	studiohdr_t* pStudioHdr = g_pModelInfo->GetStudioModel(pModel);
	if (!pStudioHdr)
		return nullptr;

	return pStudioHdr->pHitbox(iHitbox, 0);
}


bool CTools::GetHitboxPosition(CBaseEntity* pBaseEntity, int iHitBox, Vector& vOut)
{
	if (iHitBox < 0 || iHitBox >= HITBOX_MAX)
		return false;

	matrix3x4_t pmatrix[128];

	Vector vMin, vMax;

	const model_t* model = pBaseEntity->GetModel();

	if (!model)
		return false;

	studiohdr_t *pStudioHdr = g_pModelInfo->GetStudioModel(model);

	if (pStudioHdr == NULL)
		return false;

	if (!pBaseEntity->SetupBones(pmatrix, 128, 0x100, 0))
		return false;

	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet( 0 /*pBaseEntity->GetHitboxSet( )*/ );

	if (!set)
		return false;

	mstudiobbox_t* pbox = 0;//set->pHitbox(iHitBox);

	pbox = pStudioHdr->pHitbox(iHitBox, 0);


	MatrixToVector(pmatrix[pbox->bone], vOut);


	VectorTransform(pbox->bbmin, pmatrix[pbox->bone], vMin);
	VectorTransform(pbox->bbmax, pmatrix[pbox->bone], vMax);

	vOut = (vMin + vMax) * 0.5f;

	return true;
}

PlayerData* CTools::GetPlayerData(int iIndex)
{
	for (int i = 0; i < 64; i++)
		if (m_PlayerData[i].m_iIndex == iIndex)
			return &m_PlayerData[i];

	return nullptr;
}

QAngle CTools::GetAntiAimAngles(CBaseEntity* pBaseEntity, bool bEnemyOnly)
{
	if (!pBaseEntity)
		return QAngle(0.f, 0.f, 0.f);

	auto flMaxDistance = 9999.f;
	auto qAntiAimAngles = QAngle(0.f, -90.f, 0.f);

	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = g_pEntityList->GetBaseEntity(i);
		if (!pEntity)
			continue;

		if (!pEntity->IsValid())
			continue;

		if (bEnemyOnly && pBaseEntity->GetTeam() == pEntity->GetTeam())
			continue;

		auto vecCurPos = pBaseEntity->GetAbsOrigin() + pBaseEntity->GetAbsAngles();
		auto vecTargetPos = pEntity->GetAbsOrigin() + pEntity->GetAbsAngles();

		float flDistance = GetDistance(vecTargetPos, vecCurPos);
		if (flDistance < flMaxDistance)
		{
			flMaxDistance = flDistance;
			CalcAngle(vecCurPos, vecTargetPos, qAntiAimAngles);
			NormalizeVector(qAntiAimAngles);
		}
	}

	return qAntiAimAngles;
}

void CTools::AngleVectors(const QAngle& qAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp*cy;
	vecForward[1] = cp*sy;
	vecForward[2] = -sp;
}

void CTools::AngleVectors2(const QAngle& qAngles, Vector& vecForward, Vector& vecRight, Vector& vecUp)
{
	float sp, sy, sr, cp, cy, cr;
	SinCos((float)(qAngles[2] * (M_PI / 180.f)), &sr, &cr);
	SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp*cy;
	vecForward[1] = cp*sy;
	vecForward[2] = -sp;

	vecRight[0] = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
	vecRight[1] = -1.0f * sr * sp * sy + -1.0f * cr * cy;
	vecRight[2] = -1.0f * sr * cp;

	vecUp[0] = cr * sp * cy + -sr * -sy;
	vecUp[1] = cr * sp * sy + -sr * cy;
	vecUp[2] = cr * cp;

	
}

void CTools::CalcAngle(const Vector& vecSource, const Vector& vecDestination, QAngle& qAngles)
{
	QAngle delta = QAngle((vecSource[0] - vecDestination[0]), (vecSource[1] - vecDestination[1]), (vecSource[2] - vecDestination[2]));
	double hyp = sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
	qAngles[0] = (float)(atan(delta[2] / hyp) * (180.0 / M_PI));
	qAngles[1] = (float)(atan(delta[1] / delta[0]) * (180.0 / M_PI));
	qAngles[2] = 0.f;
	if (delta[0] >= 0.f)
		qAngles[1] += 180.f;
}

void CTools::ClampAngles(QAngle& qAngles)
{
	if (qAngles.x > 89.0f)
		qAngles.x = 89.0f;

	if (qAngles.x < -89.0f)
		qAngles.x = -89.0f;

	if (qAngles.y > 180)
		qAngles.y = 180;

	if (qAngles.y < -180)
		qAngles.y = -180;

	qAngles.z = 0;
}
void CTools::ClampMovement(CUserCmd *pCmd)
{
	if (pCmd->forwardmove > 450.f)
		pCmd->forwardmove = 450.f;
	else if (pCmd->forwardmove < -450.f)
		pCmd->forwardmove = -450.f;

	if (pCmd->sidemove > 450.f)
		pCmd->sidemove = 450.f;
	else if (pCmd->sidemove < -450.f)
		pCmd->sidemove = -450.f;

	if (pCmd->upmove > 320.f)
		pCmd->upmove = 320.f;
	else if (pCmd->upmove < -320.f)
		pCmd->upmove = -320.f;
}
void CTools::UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, CBaseEntity* pCSIgnore, IEngineTrace::trace_t* pTrace)
{
	IEngineTrace::CTraceFilter TraceFilter(pCSIgnore);
	IEngineTrace::Ray_t ray;
	ray.Init(vecStart, vecEnd);

	g_pEngineTrace->TraceRay(ray, nMask, &TraceFilter, pTrace);
}

void CTools::ForceFullUpdate(void)
{
	static PVOID pClientState = NULL;
	if (!pClientState)
		pClientState = **(PVOID**)(FindPattern("engine.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x8A\xF9", "xx????xx") + 0x2);

	if (!pClientState)
		return;

	static DWORD dwFreeEntityBaselines = 0;
	if (!dwFreeEntityBaselines)
		dwFreeEntityBaselines = FindPattern("engine.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00", "x????x????x????xx????????");

	if (!dwFreeEntityBaselines)
		return;

	static DWORD dwRelAddress = *(DWORD*)(dwFreeEntityBaselines + 0x1);
	static DWORD sub_B5E60 = ((dwFreeEntityBaselines + 0x5) + dwRelAddress);

	__asm
	{
		PUSHAD
		MOV	EDI, pClientState
			LEA	ECX, DWORD PTR[EDI + 0x8]
			CALL sub_B5E60
			MOV	DWORD PTR[EDI + 0x154], 0xFFFFFFFF
			POPAD
	}
}

void CTools::ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float blend[3] = { color.R< float >() / 255, color.G< float >() / 255, color.B< float >() / 255 };
		float alpha = color.A< float >() / 255;

		g_pRenderView->SetBlend(alpha);
		g_pRenderView->SetColorModulation(blend);
	}

	if (forceMaterial)
		g_pModelRender->ForcedMaterialOverride(material);
}

void CTools::MakeVector(QAngle qAngles, Vector& vecOut)
{
	auto pitch = float(qAngles[0] * M_PI / 180.f);
	auto yaw = float(qAngles[1] * M_PI / 180.f);
	auto tmp = float(cos(pitch));
	vecOut[0] = float(-tmp * -cos(yaw));
	vecOut[1] = float(sin(yaw)*tmp);
	vecOut[2] = float(-sin(pitch));
}

void CTools::MatrixToVector(const matrix3x4_t& pMatrix, Vector& out)
{
	out[0] = pMatrix[0][3];
	out[1] = pMatrix[1][3];
	out[2] = pMatrix[2][3];
}

void CTools::NormalizeVector(Vector& vecIn)
{
	for (int axis = 0; axis < 3; ++axis)
	{
		while (vecIn[axis] > 180.f)
			vecIn[axis] -= 360.f;

		while (vecIn[axis] < -180.f)
			vecIn[axis] += 360.f;

	}

	vecIn[2] = 0.f;
}

float CTools::RandomFloat( float fMin, float fMax )
{
	static RandomFloat_t m_RandomFloat = 0;

	if( m_RandomFloat == NULL )
		m_RandomFloat = ( RandomFloat_t )GetProcAddress( GetModuleHandle( "vstdlib.dll" ), "RandomFloat" );

	return m_RandomFloat( fMin, fMax );
}

void CTools::RandomSeed(UINT Seed)
{
	static RandomSeed_t m_RandomSeed = 0;

	if( m_RandomSeed == NULL )
		m_RandomSeed = ( RandomSeed_t )GetProcAddress( GetModuleHandle( "vstdlib.dll" ), "RandomSeed" );

	m_RandomSeed( Seed );

	return;
}

void CTools::ScaleDamage(int iHitgroup, CBaseEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage)
{
	if (!pBaseEntity)
		return;

	flDamage *= GetHitgroupDamageMult(iHitgroup);

	if (pBaseEntity->GetArmorValue() > 0)
	{
		if (iHitgroup == HITGROUP_HEAD)
		{
			if (pBaseEntity->HasHelmet())
				flDamage *= (flWeaponArmorRatio * 1.5f);
		}
		else flDamage *= (flWeaponArmorRatio * 0.5f);
	}
}

void CTools::SinCos(float flRadians, float* pflSine, float* pflCosine)
{
	__asm
	{
		fld	DWORD PTR[flRadians]
		fsincos
			mov edx, DWORD PTR[pflCosine]
			mov eax, DWORD PTR[pflSine]
			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
	}
}

void CTools::VectorAngles(const Vector &vecForward, Vector &vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}

void CTools::VectorTransform(const float *in1, const matrix3x4_t& in2, float *out)
{
	Assert(in1 != out);
	out[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out[2] = DotProduct(in1, in2[2]) + in2[2][3];
}

void CTools::VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
	VectorTransform(&in1.x, in2, &out.x);
}

void CTools::ClearPlayerData(void)
{
	for (int i = 0; i < 64; i++)
		m_PlayerData[i].Reset();
}

ValveSDK::CEntityList* g_pEntityList = nullptr;
ValveSDK::CGlobalVarsBase* g_pGlobalVarsBase = nullptr;
ValveSDK::IGameMovement* g_pGameMovement = nullptr;
ValveSDK::CGlowObjectManager* g_pGlowObjectManager = nullptr;
ValveSDK::CHLClient* g_pClient = nullptr;
ValveSDK::CInput* g_pInput = nullptr;
ValveSDK::CMoveHelper* g_pMoveHelper = nullptr;
ValveSDK::IPrediction* g_pPrediction = nullptr;
ValveSDK::IDebugOverlay* g_pDebugOverlay = nullptr;
ValveSDK::ICVar* g_pICvar = nullptr;
ValveSDK::IInputSystem* g_pIInput = nullptr;
ValveSDK::SpoofedConvar* g_pSCvar = nullptr;
ValveSDK::IEngineClient* g_pEngine = nullptr;
ValveSDK::IEngineTrace* g_pEngineTrace = nullptr;
ValveSDK::IGameEventManager2* g_pGameEventManager = nullptr;
ValveSDK::IModelInfo* g_pModelInfo = nullptr;
ValveSDK::IModelRender* g_pModelRender = nullptr;
ValveSDK::IRenderView* g_pRenderView = nullptr;
ValveSDK::IMaterialSystem* g_pMaterialSystem = nullptr;
ValveSDK::IPhysicsSurfaceProps* g_pPhysSurface = nullptr;
ValveSDK::IPanel* g_pPanel = nullptr;
ValveSDK::ISurface* g_pSurface = nullptr;
ValveSDK::CRenderSurface* g_pRenderSurface = nullptr;
ValveSDK::SpoofedConvar* g_pSpoofConvar = nullptr;
ValveSDK::CTools* g_pTools = nullptr;
ValveSDK::IViewRender* g_pViewRender = nullptr;