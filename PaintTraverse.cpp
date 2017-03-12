#include "PaintTraverse.h"
#include "Menu.h"
#include "Misc.h"
#include <Psapi.h>

typedef void(__thiscall* oPaintTraverse)(ValveSDK::IPanel*, unsigned int, bool, bool);
void __fastcall hkPaintTraverse(ValveSDK::IPanel* thisptr, int edx, unsigned int VGUIPanel, bool forceRepaint, bool allowForce)
{
	g_pPanelVMTHook->GetMethod< oPaintTraverse >(41)(thisptr, VGUIPanel, forceRepaint, allowForce);

	g_pRenderSurface->AddFont("FONT_WATERMARK", "Unifont", 13, FW_DONTCARE, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS);
	g_pRenderSurface->AddFont("FONT_ESP", "Trebuchet", 13, 250, 0, 0, ValveSDK::FONTFLAG_OUTLINE);
	g_pRenderSurface->AddFont("FONT_MENU", "Unifont", 13, 400, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS);
	g_pRenderSurface->AddFont("FONT_TABNOTE", "Unifont", 13, 0, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS);
	g_pRenderSurface->AddFont("FONT_MENUBUTTON", "Unifont", 13, 400, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS);
	g_pRenderSurface->CreateAllFonts();


	if (!thisptr->GetName(VGUIPanel).compare("MatSystemTopPanel"))
	{
		static bool draw = true;
		if (GetAsyncKeyState(VK_F4))
			draw = false;
		if (draw)
			g_pRenderSurface->String(20, 40, ValveSDK::Color(255, 255, 255), "FONT_WATERMARK", "1337Dank - SLAYER");

		ValveSDK::CBaseEntity* pLocal = g_pTools->GetLocalPlayer();
		if (g_CVars.GetCVar("misc_namespam")->GetBool())
		{
			g_pMisc->HandleNames("null");
		}
		if (pLocal)
		{
			g_pVisuals->Main(pLocal);

		}
		g_pMenu->Render();
		//draw menu
	}
}