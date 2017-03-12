#include "Visuals.h"
#include "Menu.h"
CVisuals::CVisuals(void)
{

}
void Outline(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pRenderSurface->Rect2(x, y, w, 1, r, g, b, a);
	g_pRenderSurface->Rect2(x, y, 1, h, r, g, b, a);
	g_pRenderSurface->Rect2(x + w, y, 1, h + 1, r, g, b, a);
	g_pRenderSurface->Rect2(x, y + h, w, 1, r, g, b, a);
}
// Vars
bool PTRadar = false; // If the radar is on or not
float PTRadarX = 156.f; // The center of the radar X
float PTRadarY = 206.f; // The center of the radar Y
float PTRadarSize = 100.f; // Size of half of the radar in pixels
float PTRadarScale = 22.f; // Adjust this for zoom
bool PTRadarShowTeam = true; // Show Teammeates
bool PTRadarShowEnemies = true; // Show Enemies
bool PTRadarShowBomb = false; // Show Dropped / Planted Bomb
bool PTRadarShowWeapons = false; // Show Dropped Weapons

ValveSDK::Color PTRadarColor = ValveSDK::Color(23, 23, 23, 255);
ValveSDK::Color PTLineColor = ValveSDK::Color(115, 164, 255,185);
ValveSDK::Color PTLocalPlayerColor = ValveSDK::Color(255, 255, 51, 255);
ValveSDK::Color PTTeamColor = ValveSDK::Color(0, 0, 255, 255);
ValveSDK::Color PTEnemyColor = ValveSDK::Color(255, 0, 0, 255);
ValveSDK::Color PTBombColor = ValveSDK::Color(255, 0, 255, 255);
ValveSDK::Color PTWeaponColor = ValveSDK::Color(255, 255, 255, 255);

ValveSDK::Vector getMapPos(ValveSDK::Vector localPos, ValveSDK::Vector entityPos, float yawRad) // Put this anywhere
{
	ValveSDK::Vector temp = ((entityPos - localPos) / PTRadarScale);

	float EntityMapX = (temp.x * std::cos(yawRad)) + (temp.y * std::sin(yawRad));
	float EntityMapY = -(temp.x * std::sin(yawRad)) + (temp.y * std::cos(yawRad));

	if ((EntityMapX > PTRadarSize) || (EntityMapX < -PTRadarSize) || (EntityMapY > PTRadarSize) || (EntityMapY < -PTRadarSize))
	{
		float ang;

		if (EntityMapX >= 0.f)
			ang = (std::atan(EntityMapY / EntityMapX));
		else
			ang = (M_PI + std::atan(EntityMapY / EntityMapX));

		float radius;

		if ((ang > -(M_PI / 4.f) && ang < (M_PI / 4.f)) || (ang >(3.f * (M_PI / 4.f)) && ang < (5.f * (M_PI / 4.f))))
			radius = PTRadarSize / std::abs(std::cos(ang));
		else
			radius = PTRadarSize / std::abs(std::sin(ang));

		EntityMapX = radius * std::cos(ang);
		EntityMapY = radius * std::sin(ang);
	};

	return ValveSDK::Vector(EntityMapX, EntityMapY,0);
};
static bool draggingR = false;
CMouseInput*	m_pMouseInput;
void DragRadar(int w, int h)
{
	
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { PTRadarX, PTRadarY };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingR = true;
	else if (!m_pMouseInput->IsPressed())
		draggingR = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingR)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - PTRadarX;
			iYDif = iMousePosition[1] - PTRadarY;
		}
		PTRadarX += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		PTRadarY += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
void CVisuals::Main(ValveSDK::CBaseEntity* pLocalEntity)
{
	m_pLocal = pLocalEntity;
	int mem = g_CVars.GetCVar("config_menu")->GetInt();
	if (mem == 0) PTLineColor = ValveSDK::Color(115, 164, 255, 255);
	if (mem == 1) PTLineColor = ValveSDK::Color(193, 70, 62, 255);
	if (mem == 2) PTLineColor = ValveSDK::Color(55, 163, 69, 255);
	if (mem == 3) PTLineColor = ValveSDK::Color(234, 145, 21, 255);
	if (mem == 4) PTLineColor = ValveSDK::Color(97, 26, 178, 255);
	if (mem == 5) PTLineColor.Rainbowize();
	if (g_CVars.GetCVar("vis_glow")->GetBool() && g_CVars.GetCVar("vis_enabled")->GetBool())
	{
		PTRadarSize = 100.f + g_CVars.GetCVar("vis_radarsize")->GetFloat();
		g_pRenderSurface->RectOutlined(PTRadarX - PTRadarSize, PTRadarY - PTRadarSize, PTRadarSize, PTRadarSize, 1, PTRadarColor, PTLineColor);
		g_pRenderSurface->Line(PTRadarX - PTRadarSize, PTRadarY, PTRadarX + PTRadarSize, PTRadarY, PTLineColor);
		g_pRenderSurface->Line(PTRadarX, PTRadarY - PTRadarSize, PTRadarX, PTRadarY + PTRadarSize, PTLineColor);

		g_pRenderSurface->Rect(PTRadarX - 0.75, PTRadarY - 0.75, 3.f, 3.f, PTLocalPlayerColor); // Circle with radius of 3
		DragRadar(PTRadarSize, PTRadarSize);
	}
	int ayy = 1;
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		ValveSDK::CBaseEntity* pBaseEntity = g_pEntityList->GetBaseEntity(i);
		if (!pBaseEntity)
			continue;
		if (!pBaseEntity->IsValid2())
			continue;

		m_vecFoot = pBaseEntity->GetAbsOrigin();
		if ((pBaseEntity->GetFlags() & FL_DUCKING))
			m_vecHead = m_vecFoot + ValveSDK::Vector(0.f, 0.f, 52.f);
		else m_vecHead = m_vecFoot + ValveSDK::Vector(0.f, 0.f, 72.f);
		if (g_CVars.GetCVar("vis_enabled")->GetBool())
		{
			if (g_CVars.GetCVar("vis_enemy")->GetBool() && pBaseEntity->GetTeam() == pLocalEntity->GetTeam())
				continue;

			ValveSDK::Vector localPos = pLocalEntity->GetAbsOrigin();
			ValveSDK::QAngle localAngles;
			g_pEngine->GetViewAngles(localAngles);
			float localYaw = localAngles.y + 90.f;
			float yawRad = DEG2RAD(localYaw);
			static int player;

			if (PTRadarShowTeam && pBaseEntity->GetTeam() == pLocalEntity->GetTeam() && g_CVars.GetCVar("vis_glow")->GetBool())
			{
				if (i != pLocalEntity->GetIndex())
				{
					ValveSDK::Vector mapPos = getMapPos(localPos, pBaseEntity->GetAbsOrigin(), yawRad);
					g_pRenderSurface->Rect(PTRadarX - mapPos.x - 0.75, PTRadarY + mapPos.y - 0.75, 3.f, 3.f, PTTeamColor); // Circle with radius of 3
				}
			};

			if (pBaseEntity->GetTeam() != pLocalEntity->GetTeam() && g_CVars.GetCVar("vis_enemyinfo")->GetBool())
			{
				ValveSDK::IEngineClient::player_info_t pTemp;
				if (g_pEngine->GetPlayerInfo(pBaseEntity->GetIndex(), &pTemp))
				{
					int iX = pBaseEntity->GetEyeAngles().x;
					int iY = pBaseEntity->GetEyeAngles().y;
					int cash = pBaseEntity->GetCash();
					int health = pBaseEntity->GetHealth();
					bool defusing = pBaseEntity->IsDefusing();
					bool scoped = pBaseEntity->IsScoped();
					bool retargetedplayer = false;
					ValveSDK::Color text = ValveSDK::Color(255, 255, 255, 255);
					if (pTemp.name == "Ayyylmao")
						text = ValveSDK::Color(255, 0, 0, 255);

						if (Global::retargetplayer[i] == true)
						{
							retargetedplayer = true;
						}

					g_pRenderSurface->String(15 , 15 * ayy, ValveSDK::Color(255, 255, 255, 255), "FONT_WATERMARK", "%s X: %i Y: %i Cash: %i$ Network Difference: %i Retargeted: %i", pTemp.name, iX, iY, cash, pBaseEntity->GetChockedPackets(), retargetedplayer); // Circle with radius of 3
					ayy++;
				}
			};
			// If the current entity is a valid teammate do:

			if (PTRadarShowEnemies && pBaseEntity->GetTeam() != pLocalEntity->GetTeam() && g_CVars.GetCVar("vis_glow")->GetBool())
			{
				if (i != pLocalEntity->GetIndex())
				{
					ValveSDK::Vector mapPos = getMapPos(localPos, pBaseEntity->GetAbsOrigin(), yawRad);
					g_pRenderSurface->Rect(PTRadarX - mapPos.x - 0.75, PTRadarY + mapPos.y - 0.75, 3.f, 3.f, PTEnemyColor); // Circle with radius of 3
				};
			};
			if (g_pTools->WorldToScreen(m_vecFoot, m_vecFootScreen) && g_pTools->WorldToScreen(m_vecHead, m_vecHeadScreen))
			{
				RenderPlayer(pBaseEntity, pLocalEntity);
			}

		}
	}
}

char* GetWeaponName(ValveSDK::CBaseCombatWeapon *pWeapon)
{
	int ID = pWeapon->GetWeaponId();

	switch (ID) {
		/*pistols*/
	case 4:
		return "glock";
	case 2:
		return "dual berretas";
	case 36:
		return "p250";
	case 30:
		return "tec9";
	case 1:
		return "deagle";
	case 32:
		return "p2000";
	case 3:
		return "fiveseven";
	case 64:
		return "revolver";
	case 63:
		return "cz75";
	case 61:
		return "usp";
		/*heavy*/
	case 35:
		return "nova";
	case 25:
		return "xm1014";
	case 29:
		return "sawed off";
	case 14:
		return "m249";
	case 28:
		return "negev";
	case 27:
		return "mag7";
		/*smgs*/
	case 17:
		return "mac10";
	case 33:
		return "mp7";
	case 24:
		return "ump45";
	case 19:
		return "p90";
	case 26:
		return "bizon";
	case 34:
		return "mp9";
		/*rifles*/
	case 10:
		return "famas";
	case 16:
		return "m4a1";
	case 40:
		return "scout";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 38:
		return "scar20";
	case 13:
		return "galil";
	case 7:
		return "ak47";
	case 39:
		return "sg553";
	case 11:
		return "g3sg1";
	case 60:
		return "m4a1-s";
		/*grenades*/
	case 46:
	case 48:
		return "molotov";
	case 44:
		return "grenade";
	case 43:
		return "flashbang";
	case 45:
		return "smoke";
	case 47:
		return "decoy";
		/*other*/
	case 31:
		return "zeus";
	default:
		return "knife";
	}
}

void CVisuals::RenderPlayer(ValveSDK::CBaseEntity* pBaseEntity, ValveSDK::CBaseEntity* pLocal)
{
	m_H = int(m_vecFootScreen.y - m_vecHeadScreen.y);
	m_W = int(m_H / 1.75);
	m_X = int(m_vecHeadScreen.x - m_W / 2);
	m_Y = int(m_vecHeadScreen.y);

	auto bVisible = g_pTools->IsVisibles(g_CVars.GetCVar("rage_hitbox")->GetInt(), pBaseEntity, pLocal);
	auto color = pBaseEntity->GetTeamColor(false);

	if (!g_CVars.GetCVar("vis_enabled")->GetBool())
		return;
	if (g_CVars.GetCVar("vis_enemy")->GetBool() && pBaseEntity->GetTeam() == pLocal->GetTeam())
		return;
	
	int textY = m_Y;
	int above = m_Y - 17;
	if (g_CVars.GetCVar("vis_name")->GetBool())
	{
		ValveSDK::IEngineClient::player_info_t pTemp;
		if (g_pEngine->GetPlayerInfo(pBaseEntity->GetIndex(), &pTemp))
		{
			g_pRenderSurface->DrawStringA("FONT_ESP", true, m_X + m_W / 2, m_Y - 17, ValveSDK::Color(color[0], color[1], color[2], 255), pTemp.name);
			above -= 12;
		}
	}
	if (g_CVars.GetCVar("vis_weapon")->GetBool())
	{
		ValveSDK::CBaseCombatWeapon* pWeapon = pBaseEntity->GetWeapon();
		if (pWeapon)
			g_pRenderSurface->DrawStringA("FONT_ESP", true, m_X + m_W / 2, m_Y + m_H - 2, ValveSDK::Color(color[0], color[1], color[2], 255), GetWeaponName(pWeapon));
	}

	//g_pRenderSurface->DrawStringA("FONT_ESP", false, m_X + m_W + 4, textY - 5, ValveSDK::Color(color[0], color[1], color[2], 255), "%i$", pBaseEntity->GetCash());
	//textY += 13;
	if (g_CVars.GetCVar("vis_angles")->GetBool())
	{
		int iX = pBaseEntity->GetEyeAngles().x;
		int iY = pBaseEntity->GetEyeAngles().y;
		g_pRenderSurface->DrawStringA("FONT_ESP", true, m_X + m_W / 2, above, ValveSDK::Color(color[0], color[1], color[2], 255), "X: %i Y: %i", iX, iY);
	}
	if (g_CVars.GetCVar("vis_box")->GetBool())
	{
		Outline(m_X, m_Y, m_W, m_H, color[0], color[1], color[2], 255);
		if (g_CVars.GetCVar("vis_outlined")->GetBool())
		{
			Outline(m_X - 1, m_Y - 1, m_W + 2, m_H + 2, 0, 0, 0, 255);
			Outline(m_X + 1, m_Y + 1, m_W - 2, m_H - 2, 0, 0, 0, 255);
		}
	}
	if (g_CVars.GetCVar("vis_health")->GetBool())
	{

		int plyHp = pBaseEntity->GetHealth();
		plyHp = plyHp > 100 ? 100 : plyHp;
		int sPos = plyHp * m_H / 100;
		int hDelta = m_H - sPos;

		if (g_CVars.GetCVar("vis_outlined")->GetBool())
		{
			g_pRenderSurface->Rect2(m_vecFootScreen.x - m_W / 2 - 5, m_vecFootScreen.y - m_H - 1, 3, m_H + 2, 0, 0, 0, 255);
		}
		g_pRenderSurface->Rect2(m_vecFootScreen.x - m_W / 2 - 4, m_vecFootScreen.y - m_H + hDelta, 1, sPos, (100 - plyHp) * 2.55, plyHp * 2.55, 0,255);
	}

}
CVisuals* g_pVisuals = nullptr;