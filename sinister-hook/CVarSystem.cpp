	#include "CVarSystem.h"
	#include "const.h"

	std::size_t CVar::GetArgIndexByArg(std::string strArg)
	{
		if (strArg.empty())
			return -1;

		for (std::size_t i = 0; i < m_vArgs.size(); i++)
			if (!m_vArgs.at(i).m_strName.compare(strArg))
				return i;

		return -1;
	}

	CVar::CVar(std::string strName, std::string strDescription, bool active, bool bCommand)
	{
		Setup(strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand);
	}

	CVar::CVar(std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand)
	{
		Setup(strName, strDescription, flValue, flMaxValue, flMinValue, bCommand);
	}

	CVar::CVar(std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand)
	{
		Setup(strName, strDescription, iValue, iMaxValue, iMinValue, bCommand);
	}

	CVar::~CVar(void)
	{
		Release();
	}

	bool CVar::GetBool(void)
	{
		return (m_flValue >= 1.f);
	}

	bool CVar::HasArgs(void)
	{
		return !m_vArgs.empty();
	}

	bool CVar::IsArg(std::string strArg)
	{
		return(GetArgIndexByArg(strArg) != -1);
	}

	bool CVar::IsCommand(void)
	{
		return m_bCommand;
	}

	bool CVar::SetByArg(std::string strArg)
	{
		if (!HasArgs())
			return false;

		std::size_t i = GetArgIndexByArg(strArg);
		if (i == -1)
			return false;

		Set(m_vArgs.at(i).m_flValue);

		return true;
	}

	float CVar::GetFloat(void)
	{
		return m_flValue;
	}

	float CVar::GetMax(void)
	{
		return m_flMaxValue;
	}

	float CVar::GetMin(void)
	{
		return m_flMinValue;
	}

	int CVar::GetInt(void)
	{
		return int(m_flValue);
	}

	std::string CVar::GetName(void)
	{
		return m_strName;
	}

	std::string CVar::GetInfoString(void)
	{
		static char pszBuffer[0x400];
		if (m_flMaxValue == 1.f && m_flMinValue == 0.f)
			sprintf_s(pszBuffer, "%s", GetBool() ? "true" : "false");
		else sprintf_s(pszBuffer, "%.2f", m_flValue);

		return pszBuffer;
	}

	std::string CVar::GetDescription(void)
	{
		return m_strDescription;
	}

	std::vector< CVar::StrArg > CVar::GetAllArgs(void)
	{
		return m_vArgs;
	}

	void CVar::AddArg(std::string strArg, bool active)
	{
		AddArg(strArg, active ? 1.f : 0.f);
	}

	void CVar::AddArg(std::string strArg, float flValue)
	{
		if (GetArgIndexByArg(strArg) != -1)
			return;

		m_vArgs.push_back({ strArg, flValue });
	}

	void CVar::AddArg(std::string strArg, int iValue)
	{
		AddArg(strArg, float(iValue));
	}

	void CVar::Setup(std::string strName, std::string strDescription, bool active, bool bCommand)
	{
		Setup(strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand);
	}

	void CVar::Setup(std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand)
	{
		SetName(strName);
		SetDescription(strDescription);
		m_flMaxValue = flMaxValue;
		m_flMinValue = flMinValue;
		Set(flValue);
		SetCommand(bCommand);
	}

	void CVar::Setup(std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand)
	{
		Setup(strName, strDescription, float(iValue), float(iMaxValue), float(iMinValue), bCommand);
	}

	void CVar::SetName(std::string strName)
	{
		m_strName = strName;
	}

	void CVar::SetDescription(std::string strDescription)
	{
		m_strDescription = strDescription;
	}

	void CVar::SetCommand(bool bCommand)
	{
		m_bCommand = bCommand;
	}

	void CVar::Set(bool active)
	{
		Set(active ? 1.f : 0.f);
	}

	void CVar::Set(float flValue)
	{
		if (flValue > m_flMaxValue)
			m_flValue = m_flMaxValue;
		else if (flValue < m_flMinValue)
			m_flValue = m_flMinValue;
		else m_flValue = flValue;
	}

	void CVar::Set(int iValue)
	{
		Set(float(iValue));
	}
	void CVar::Set(double iValue)
	{
		Set(float(iValue));
	}

	void CVar::Release(void)
	{
		m_vArgs.clear();
	}

	std::size_t CVarSystem::GetCVarIndexByName(std::string strName)
	{
		if (strName.empty())
			return -1;

		for (std::size_t i = 0; i < m_vpCVars.size(); i++)
			if (!m_vpCVars.at(i)->GetName().compare(strName))
				return i;

		return -1;
	}

	CVarSystem::CVarSystem(void)
	{

	}

	CVarSystem::~CVarSystem(void)
	{
		Release();
	}


	bool CVarSystem::IsCVar(std::string strName)
	{
		return(GetCVarIndexByName(strName) != -1);
	}

	CVar* CVarSystem::NewCVar(std::string strName, std::string strDescription, bool active, bool bCommand, bool push)
	{
		return NewCVar(strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand, push);
	}

	CVar* CVarSystem::NewCVar(std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand, bool push)
	{
		std::size_t i = GetCVarIndexByName(strName);
		if (i != -1)
			return m_vpCVars.at(i);

		CVar* pCVar = new CVar(strName, strDescription, flValue, flMaxValue, flMinValue, bCommand);
		if (push)
			PushCVar(pCVar);

		return pCVar;
	}

	CVar* CVarSystem::NewCVar(std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand, bool push)
	{
		return NewCVar(strName, strDescription, float(iValue), float(iMaxValue), float(iMinValue), bCommand, push);
	}

	CVar* CVarSystem::GetCVar(std::string strName)
	{
		std::size_t i = GetCVarIndexByName(strName);
		if (i == -1)
			return nullptr;

		return m_vpCVars.at(i);
	}

	std::vector< CVar* > CVarSystem::GetAllCVars(void)
	{
		return m_vpCVars;
	}

	void CVarSystem::PushCVar(CVar* pCVar)
	{
		if (!pCVar)
			return;

		m_vpCVars.push_back(pCVar);
	}

	void CVarSystem::Release(void)
	{
		for (std::size_t i = 0; i < m_vpCVars.size(); i++)
		{
			delete m_vpCVars.at(i);
			m_vpCVars.at(i) = nullptr;
		}
		m_vpCVars.clear();
	}

void InitCVars(void)
{
#pragma region "RageBot"
	g_CVars.NewCVar("rage_active", "Enable/disable the aimbot", false);
	g_CVars.NewCVar("rage_autoshoot", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_autostop", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("rage_autocrouch", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("rage_autowall", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_silent", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_norecoil", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_nospread", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_static", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_prediction", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_hitscan", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("rage_autowall_damage", "Adjust the minimal damage to shoot trough walls", 1.f, 100.f, 1.f);
	g_CVars.NewCVar("rage_fov", "Adjust the minimal damage to shoot trough walls", 39.f, 180.f, 0.f);
	g_CVars.NewCVar("rage_hitchance_val", "Adjust the minimal damage to shoot trough walls", 0.f, 100.f, 0.f);
	g_CVars.NewCVar("rage_pointscale", "Adjust the minimal damage to shoot trough walls", 0.0f, 1.0f, 0.0f);

	g_CVars.NewCVar("rage_awpbaim", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_smartaim", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("rage_aimstep", "Enable/disable autoshoot", false);
	
	auto pCVar = g_CVars.NewCVar("rage_hitscan", "Switch between enemy only/team only/all", 0, 2, 0, true, false);
	pCVar->AddArg("Low", 0);
	pCVar->AddArg("Medium", 1);
	pCVar->AddArg("High", 2);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("rage_multipoint", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Low", 1);
	pCVar->AddArg("Medium", 2);
	pCVar->AddArg("High", 3);
	pCVar->AddArg("Extreme", 4);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("rage_prediction_mode", "Switch between enemy only/team only/all", 0, 1, 0, true, false);
	pCVar->AddArg("Learning", 0);
	pCVar->AddArg("Vector-Based", 1);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("rage_hitbox", "custom aimbot hitbox", ValveSDK::HITBOX_HEAD, 8, 0, true, false);
	pCVar->AddArg("head", ValveSDK::HITBOX_HEAD);
	pCVar->AddArg("neck", ValveSDK::HITBOX_NECK);
	pCVar->AddArg("lower_neck", ValveSDK::HITBOX_LOWER_NECK);
	pCVar->AddArg("pelvis", ValveSDK::HITBOX_PELVIS);
	pCVar->AddArg("body", ValveSDK::HITBOX_BODY);
	pCVar->AddArg("thorax", ValveSDK::HITBOX_THORAX);
	pCVar->AddArg("chest", ValveSDK::HITBOX_CHEST);
	pCVar->AddArg("upper_chest", ValveSDK::HITBOX_UPPER_CHEST);
	g_CVars.PushCVar(pCVar);

#pragma endregion

#pragma region "LegitBot"

	g_CVars.NewCVar("legit_active", "Enable/disable the aimbot", false);
	g_CVars.NewCVar("legit_autoshoot", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("legit_silent", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("legit_rcs", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("legit_awpbaim", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("legit_randomsmoothing", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("legit_randomhitbox", "Enable/disable shooting trough penetrable walls", false);
	g_CVars.NewCVar("legit_fov", "Adjust the minimal damage to shoot trough walls", 5.f, 5.f, 0.f);
	g_CVars.NewCVar("legit_smoothing", "Adjust the minimal damage to shoot trough walls", 0.f, 15.f, 0.f);


	pCVar = g_CVars.NewCVar("legit_hitbox", "custom aimbot hitbox", ValveSDK::HITBOX_HEAD, 8, 0, true, false);
	pCVar->AddArg("head", ValveSDK::HITBOX_HEAD);
	pCVar->AddArg("neck", ValveSDK::HITBOX_NECK);
	pCVar->AddArg("lower_neck", ValveSDK::HITBOX_LOWER_NECK);
	pCVar->AddArg("pelvis", ValveSDK::HITBOX_PELVIS);
	pCVar->AddArg("body", ValveSDK::HITBOX_BODY);
	pCVar->AddArg("thorax", ValveSDK::HITBOX_THORAX);
	pCVar->AddArg("chest", ValveSDK::HITBOX_CHEST);
	pCVar->AddArg("upper_chest", ValveSDK::HITBOX_UPPER_CHEST);
	g_CVars.PushCVar(pCVar);
#pragma endregion

#pragma region "Visuals"
	g_CVars.NewCVar("vis_enabled", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_enemy", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_box", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_outlined", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_name", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_health", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_weapon", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_angles", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_glow", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_chams", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_handchams", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_weaponchams", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_watermark", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_snapline", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_enemyinfo", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_norec", "Enable/disable the aa", false);
	g_CVars.NewCVar("vis_fov", "ya", 0.f, 40.f, 0.f);
	g_CVars.NewCVar("vis_radarsize", "ya", 0.f, 100.f, 0.f);
	g_CVars.NewCVar("vis_noparticles", "Enable/disable the aa", false);
#pragma endregion

#pragma region "Misc"
	g_CVars.NewCVar("misc_antiaim", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_fakeduck", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_antiaimAT", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_antiaimFA", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_edge", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_antiuntrusted", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_fakelag", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_fakelagval", "Adjust the minimal damage to shoot trough walls", 0.f, 14.f, 0.f);
	g_CVars.NewCVar("misc_resolver", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_sbresolver", "Enable/disable the sbaa", false);
	g_CVars.NewCVar("misc_autohop", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_autostrafe", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_circlestrafer", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_circlestraferval", "Adjust the spin", 0.f, 20.f, 0.f);
	g_CVars.NewCVar("misc_fakeduck", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_namespam", "Enable/disable the aa", false);

	g_CVars.NewCVar("misc_speedhackval", "Adjust the minimal damage to shoot trough walls", 0.f, 10.f, 0.f);

	//new loser stuff
	g_CVars.NewCVar("misc_chatspam", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_namestealer", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_teleport", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_speedhack", "Enable/disable the aa", false);
	g_CVars.NewCVar("misc_airstuck", "Enable/disable the aa", false);

	pCVar = g_CVars.NewCVar("misc_chatspam_mode", "misc_chatspam_mode", 0, 2, 0, true, false);
	pCVar->AddArg("Slow", 0);
	pCVar->AddArg("Average", 1);
	pCVar->AddArg("Fast", 2);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_fakeduck_mode", "misc_fakeduck_mode", 0, 2, 0, true, false);
	pCVar->AddArg("Normal", 0);
	pCVar->AddArg("Maximum", 1);
	pCVar->AddArg("Switch", 2);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_fakelag_mode", "misc_fakelag_mode", 0, 5, 0, true, false);
	pCVar->AddArg("Normal", 0);
	pCVar->AddArg("Adaptive", 1);
	pCVar->AddArg("Switch", 2);
	pCVar->AddArg("Random", 3);
	pCVar->AddArg("Cycle", 4);
	pCVar->AddArg("Revolve", 5);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_aa", "Anti aim_x", 0, 6, 0, true, false);
	pCVar->AddArg("Down", 1);
	pCVar->AddArg("FakeDown", 2);
	pCVar->AddArg("AngelDown", 3);
	pCVar->AddArg("Angelup", 4);
	pCVar->AddArg("Overflow", 5);
	pCVar->AddArg("Custom", 6);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_yaw", "Anti aim_y", 0, 16, 0, true, false);
	pCVar->AddArg("Backwards", 1);
	pCVar->AddArg("Fake-Backwards", 2);
	pCVar->AddArg("Fake-Sideways", 3);
	pCVar->AddArg("Fake-Forwards", 4);
	pCVar->AddArg("Jitter", 5);
	pCVar->AddArg("Jitter2", 6);
	pCVar->AddArg("TJitter", 7);
	pCVar->AddArg("TJitter2", 8);
	pCVar->AddArg("Fake", 9);
	pCVar->AddArg("Fake2", 10);
	pCVar->AddArg("Eagle", 11);
	pCVar->AddArg("Lisp", 12);
	pCVar->AddArg("Lisp-Spin", 13);
	pCVar->AddArg("Lisp-Jitter", 14);
	pCVar->AddArg("Lisp-Fake", 15);
	pCVar->AddArg("Custom", 16);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_edge_pitch", "Anti aim_x", 0, 3, 0, true, false);
	pCVar->AddArg("Down", 1);
	pCVar->AddArg("FakeDown", 2);
	pCVar->AddArg("AngelDown", 3);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("misc_edge_yaw", "Anti aim_y", 0, 5, 0, true, false);
	pCVar->AddArg("In", 1);
	pCVar->AddArg("Out", 2);
	pCVar->AddArg("Jitter", 3);
	pCVar->AddArg("FakeOut", 4);
	pCVar->AddArg("Overflow", 5);
	g_CVars.PushCVar(pCVar);

#pragma endregion

#pragma region "Config"
	pCVar = g_CVars.NewCVar("config_config", "configs", 0, 4, 0, true, false);
	pCVar->AddArg("Legit", 0);
	pCVar->AddArg("League", 1);
	pCVar->AddArg("Rage", 2);
	pCVar->AddArg("HvH", 3);
	pCVar->AddArg("HvH2", 4);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("config_menu", "config_menu", 0, 5, 0, true, false);
	pCVar->AddArg("Blue", 0);
	pCVar->AddArg("Red", 1);
	pCVar->AddArg("Green", 2);
	pCVar->AddArg("Orange", 3);
	pCVar->AddArg("Black", 4);
	pCVar->AddArg("gay", 5);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("config_circlehotkey", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Mouse4", 0);
	pCVar->AddArg("Mouse5", 1);
	pCVar->AddArg("Shift", 2);
	pCVar->AddArg("Alt", 3);
	pCVar->AddArg("Ctrl", 4);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("config_teleporthotkey", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Mouse4", 0);
	pCVar->AddArg("Mouse5", 1);
	pCVar->AddArg("Shift", 2);
	pCVar->AddArg("Alt", 3);
	pCVar->AddArg("Ctrl", 4);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("config_speedhackhotkey", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Mouse4", 0);
	pCVar->AddArg("Mouse5", 1);
	pCVar->AddArg("Shift", 2);
	pCVar->AddArg("Alt", 3);
	pCVar->AddArg("Ctrl", 4);
	g_CVars.PushCVar(pCVar);

	pCVar = g_CVars.NewCVar("config_airstuckhotkey", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Mouse4", 0);
	pCVar->AddArg("Mouse5", 1);
	pCVar->AddArg("Shift", 2);
	pCVar->AddArg("Alt", 3);
	pCVar->AddArg("Ctrl", 4);
	g_CVars.PushCVar(pCVar);
#pragma endregion

#pragma region "CustomAA"

	g_CVars.NewCVar("customaa_attarget", "Enable/disable the aimbot", false);
	g_CVars.NewCVar("customaa_fakedangles", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("customaa_jitter", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("customaa_spin", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("customaa_add", "Enable/disable autoshoot", false);
	g_CVars.NewCVar("customaa_realanglex", "Adjust the minimal damage to shoot trough walls", 0.f, 181.f, 0.f);
	g_CVars.NewCVar("customaa_fakeanglex", "Adjust the minimal damage to shoot trough walls", 0.f, 181.f, 0.f);

	g_CVars.NewCVar("customaa_realangley", "Adjust the minimal damage to shoot trough walls", 0.f, 360.f, 0.f);
	g_CVars.NewCVar("customaa_fakeangley", "Adjust the minimal damage to shoot trough walls", 0.f, 360.f, 0.f);

	g_CVars.NewCVar("customaa_chokedticks", "Adjust the minimal damage to shoot trough walls", 0.f, 15.f, 0.f);
	pCVar = g_CVars.NewCVar("customaa_mode", "Switch between enemy only/team only/all", 0, 4, 0, true, false);
	pCVar->AddArg("Add", 0);
	pCVar->AddArg("Jitter", 1);
	pCVar->AddArg("Lisp", 2);
	pCVar->AddArg("Spin", 3);
	pCVar->AddArg("Static", 4);
	g_CVars.PushCVar(pCVar);
#pragma endregion
}

CVarSystem g_CVars = CVarSystem();