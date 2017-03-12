#include "stdafx.h"
#include "SDK.h"
#include "Offsets.h"
#include <Psapi.h>
#include "PaintTraverse.h"
#include "CreateMove.h"
#include "KeyEvent.h"
#include "FrameStageNotify.h"
#include "DrawModelExecute.h"
#include "Menu.h"
#include "Misc.h"
#include "Aimbot.h"
#include "LegitAimbot.h"
#include "Visuals.h"
CVMTHookManager* g_pClientVMTHook = nullptr;
CVMTHookManager* g_pClientMVMTHook = nullptr;
CVMTHookManager* g_pPredictionVMTHook = nullptr;
CVMTHookManager* g_pPanelVMTHook = nullptr;
CVMTHookManager* g_pModelRenderVMTHook = nullptr;
CVMTHookManager* g_pMaterialSystemVmt = nullptr;

__declspec(naked) void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		PUSH	EBP
		MOV		EBP, ESP
		PUSH	EBX
		LEA		ECX, [ESP]
		PUSH	ECX
		PUSH	active
		PUSH	input_sample_frametime
		PUSH	sequence_number
		CALL	CreateMoveProxy
		POP		EBX
		POP		EBP
		RETN	0xC
	}
}

DWORD IdleHWID;
bool good = false;


class CClientModeShared;
void DLL_Main_Thread(PVOID pParam)
{

	//AttachDebugConsole();

	

	g_pMisc = new CMisc();
	g_pMenu = new CMenu();
	g_pAimbot = new CAimbot();
	g_pLAimbot = new CLAimbot();
	g_pVisuals = new CVisuals();
	g_pTools = new ValveSDK::CTools();
	while (FindWindowA("Valve001", 0) == 0)
		Sleep(100);

	while (GetModuleHandleA("engine.dll") == 0 || GetModuleHandleA("client.dll") == 0)
		Sleep(100);

	InitCVars();

	g_pEntityList = ValveSDK::GetInterface< ValveSDK::CEntityList >("client.dll", "VClientEntityList");
	g_pGlobalVarsBase = (ValveSDK::CGlobalVarsBase*)*(DWORD*)*(DWORD*)(g_pTools->FindPattern("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x8B\x40\x10\x89\x41\x04", "x????xxxxxx", NULL, NULL) + 0x1);
	g_pGameMovement = ValveSDK::GetInterface< ValveSDK::IGameMovement >("client.dll", "GameMovement");
	g_pClient = ValveSDK::GetInterface< ValveSDK::CHLClient >("client.dll", "VClient"); //VClient
	g_pPrediction = ValveSDK::GetInterface< ValveSDK::IPrediction >("client.dll", "VClientPrediction");
	g_pDebugOverlay = ValveSDK::GetInterface< ValveSDK::IDebugOverlay >("engine.dll", "VDebugOverlay");
	g_pEngine = ValveSDK::GetInterface< ValveSDK::IEngineClient >("engine.dll", "VEngineClient"); //VEngineClient
	g_pEngineTrace = ValveSDK::GetInterface< ValveSDK::IEngineTrace >("engine.dll", "EngineTraceClient");
	g_pGameEventManager = ValveSDK::GetInterface< ValveSDK::IGameEventManager2 >("engine.dll", "GAMEEVENTSMANAGER", true);
	g_pModelInfo = ValveSDK::GetInterface< ValveSDK::IModelInfo >("engine.dll", "VModelInfoClient");
	g_pModelRender = ValveSDK::GetInterface< ValveSDK::IModelRender >("engine.dll", "VEngineModel");
	g_pRenderView = ValveSDK::GetInterface< ValveSDK::IRenderView >("engine.dll", "VEngineRenderView");
	g_pMaterialSystem = ValveSDK::GetInterface< ValveSDK::IMaterialSystem >("materialsystem.dll", "VMaterialSystem");
	g_pPhysSurface = ValveSDK::GetInterface< ValveSDK::IPhysicsSurfaceProps >("vphysics.dll", "VPhysicsSurfaceProps");
	g_pPanel = ValveSDK::GetInterface< ValveSDK::IPanel >("vgui2.dll", "VGUI_Panel");
	g_pSurface = ValveSDK::GetInterface< ValveSDK::ISurface >("vguimatsurface.dll", "VGUI_Surface");
	g_pRenderSurface = new ValveSDK::CRenderSurface(g_pSurface);
	g_pMoveHelper = **reinterpret_cast<ValveSDK::CMoveHelper***>(g_pTools->FindPatternAlt("client.dll", reinterpret_cast<PBYTE>("\x8B\x0D\x00\x00\x00\x00\x6A\x02\x8B\x01\xFF\x50\x28"), "xx????xxxxxxx", 0, 0) + 0x2);
	g_pICvar = ValveSDK::GetInterface< ValveSDK::ICVar >("vstdlib.dll", "VEngineCvar");
	g_pIInput = ValveSDK::GetInterface<ValveSDK::IInputSystem>("inputsystem.dll", "InputSystemVersion001");
	PDWORD pdwClientVMT = *(DWORD**)g_pClient;
	CClientModeShared **ClientMode = *(CClientModeShared***)*(void***)((DWORD)(*(void***)g_pClient)[10] + 5);
	g_pInput = *(ValveSDK::CInput**)(pdwClientVMT[15] + 0x1);
	g_pNetVars = new ValveSDK::CNetVars(g_pClient->GetFirstClass());
	int iScreenSize[2] = { 0 };
	g_pEngine->GetScreenSize(iScreenSize);


	if (g_pNetVars->Setup())
	{
		InitOffsets();
		Offsets::m_dwLoadFromBuffer = g_pTools->FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x34\x53\x8B\x5D\x0C\x89", "xxxxxxxxxxxxxx", 0, 0);

		g_pNetVars->DumpNetVars();

		//g_pClientMVMTHook = new CVMTHookManager((PDWORD*)ClientMode);
		//g_pClientMVMTHook->HookMethod((DWORD)hkOverrideView, 18);
		//g_pClientMVMTHook->ReHook();

		g_pClientVMTHook = new CVMTHookManager((PDWORD*)g_pClient);
		g_pClientVMTHook->HookMethod((DWORD)hkKeyEvent, 20);
		g_pClientVMTHook->HookMethod((DWORD)hkCreateMove, 21);
		g_pClientVMTHook->HookMethod((DWORD)hkFrameStageNotify, 36);
		g_pClientVMTHook->ReHook();



		g_pPanelVMTHook = new CVMTHookManager((PDWORD*)g_pPanel);
		g_pPanelVMTHook->HookMethod((DWORD)hkPaintTraverse, 41);
		g_pPanelVMTHook->ReHook();

		g_pModelRenderVMTHook = new CVMTHookManager((PDWORD*)g_pModelRender);
		g_pModelRenderVMTHook->HookMethod((DWORD)hkDrawModelExecute, 21);
		g_pModelRenderVMTHook->ReHook();

	}
}

//Broken Null Char: ""
//Invisible - Char: "­"
void Dll_Eject(HMODULE hModule)
{

	FreeConsole();

	SafeDelete(&g_pNetVars);
	SafeDelete(&g_pRenderSurface);
	SafeDelete(&g_pTools);

	g_pClientVMTHook->UnHook();
	g_pPanelVMTHook->UnHook();
	g_pPredictionVMTHook->UnHook();
	g_pModelRenderVMTHook->UnHook();

	SafeDelete(&g_pClientVMTHook);
	SafeDelete(&g_pPanelVMTHook);
	SafeDelete(&g_pPredictionVMTHook);
	SafeDelete(&g_pModelRenderVMTHook);

	FreeLibraryAndExitThread(hModule, 0);
}

void Dll_Eject_Thread(LPARAM hModule) {
	while (!(GetKeyState(VK_END) & 0x8000))
		Sleep(100);
	FreeLibraryAndExitThread((HMODULE)hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		
			_beginthread(DLL_Main_Thread, 0, NULL);
		
		
		//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Dll_Eject_Thread, hModule, 0, NULL);
		break;
	case DLL_PROCESS_DETACH:
		Dll_Eject(hModule);
		break;
	}

	return TRUE;
}