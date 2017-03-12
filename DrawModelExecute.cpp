#include "DrawModelExecute.h"

typedef void(__thiscall* oDrawModelExecute)(PVOID, PVOID, const ValveSDK::DrawModelState_t&, const ValveSDK::ModelRenderInfo_t&, ValveSDK::matrix3x4*);
void __fastcall hkDrawModelExecute(PVOID thisptr, int edx, PVOID pContext, const ValveSDK::DrawModelState_t& pState, const ValveSDK::ModelRenderInfo_t& pInfo, ValveSDK::matrix3x4* pCustomBoneToWorld)
{
	// Normal engine materials
	static ValveSDK::IMaterial* pNormalMaterial[4] =
	{
		g_pTools->CreateMaterial(false, false, false),
		g_pTools->CreateMaterial(false, false, false),
	};

	// Engine materials witout Z buffer
	static ValveSDK::IMaterial* pIgnoreZMaterial[4] =
	{
		g_pTools->CreateMaterial(true, false, false),
		g_pTools->CreateMaterial(true, false, false),
	};

	// Get the current model name
	auto strModelName = g_pModelInfo->GetModelName(pInfo.pModel);
	if (g_CVars.GetCVar("vis_enabled")->GetBool())
	{

		auto iChams = g_CVars.GetCVar("vis_chams")->GetBool();
		//if (g_CVars.GetCVar("misc_antiss")->GetBool() && g_pEngine->IsTakingScreenshot())
		//{

		//}
		//else
		//{
		if (g_CVars.GetCVar("vis_chams")->GetBool() && strModelName.find("models/player") != std::string::npos)
		{
			auto pLocalEntity = g_pEntityList->GetBaseEntity(g_pEngine->GetLocalPlayer());
			auto pBaseEntity = g_pEntityList->GetBaseEntity(pInfo.entity_index);

			if (pLocalEntity && pBaseEntity && pBaseEntity->GetHealth() > 0)
			{
				if (g_CVars.GetCVar("vis_enemy")->GetBool() && pBaseEntity->GetTeam() == pLocalEntity->GetTeam())
				{
					g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >(21)(thisptr, pContext, pState, pInfo, pCustomBoneToWorld);
					return;
				}

				ValveSDK::Color pColorT = ValveSDK::Color(255, 54, 54);
				ValveSDK::Color pColorCT = ValveSDK::Color(54, 61, 255);
				ValveSDK::Color color = pBaseEntity->GetTeamColor();
				if (pBaseEntity->GetTeam() == 2)
					color = pColorT;
				else
					color = pColorCT;
				if (iChams == 1)
					g_pTools->ForceMaterial(color, pIgnoreZMaterial[1]);
				else g_pTools->ForceMaterial(color, pIgnoreZMaterial[2]);

				g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >(21)(thisptr, pContext, pState, pInfo, pCustomBoneToWorld);
				color = pBaseEntity->GetTeamColor(true);
				if (pBaseEntity->GetTeam() == 2)
					color = pColorT;
				else
					color = pColorCT;

				if (iChams == 1)
					g_pTools->ForceMaterial(color, pNormalMaterial[0]);
				else g_pTools->ForceMaterial(color, pNormalMaterial[2]);

			}
			/*}*/
		}
		if (g_CVars.GetCVar("vis_handchams")->GetBool() && strModelName.find("arms") != std::string::npos)
		{
			auto pLocalEntity = g_pEntityList->GetBaseEntity(g_pEngine->GetLocalPlayer());

			if (pLocalEntity)
			{

				ValveSDK::Color color = pLocalEntity->GetTeamColor();
				if (pLocalEntity->GetTeam() == 2)
					color = ValveSDK::Color(255, 81, 110);
				else
					color = ValveSDK::Color(255, 81, 110);
				if (iChams == 1)
					g_pTools->ForceMaterial(color, pIgnoreZMaterial[1]);
				else g_pTools->ForceMaterial(color, pIgnoreZMaterial[2]);

				g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >(21)(thisptr, pContext, pState, pInfo, pCustomBoneToWorld);
				color = pLocalEntity->GetTeamColor(true);
				if (pLocalEntity->GetTeam() == 2)
					color = ValveSDK::Color(255, 81, 110);
				else
					color = ValveSDK::Color(255, 81, 110);

				if (iChams == 1)
					g_pTools->ForceMaterial(color, pNormalMaterial[0]);
				else g_pTools->ForceMaterial(color, pNormalMaterial[2]);

			}
		}

		if (g_CVars.GetCVar("vis_weaponchams")->GetBool() && strModelName.find("models/weapons/w_") != std::string::npos) {

			g_pTools->ForceMaterial(ValveSDK::Color(255, 255, 255), pNormalMaterial[0]);
		}
	}
	g_pModelRenderVMTHook->GetMethod< oDrawModelExecute >(21)(thisptr, pContext, pState, pInfo, pCustomBoneToWorld);
	g_pModelRender->ForcedMaterialOverride(NULL);

}