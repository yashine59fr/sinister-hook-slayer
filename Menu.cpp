#include "Menu.h"
#include "xor.h"
ValveSDK::Color MenuTop = ValveSDK::Color(42, 42, 42, 255);
ValveSDK::Color MenuBG = ValveSDK::Color(25, 25, 25, 255);
ValveSDK::Color Font = ValveSDK::Color(255, 255, 255);
ValveSDK::Color Selected = ValveSDK::Color(130, 30, 49, 255);
int Ragebot[2] = { 5,30 };
int Legitbot[2] = { 510,30 };
int Visuals[2] = { 1015,30 };
int Misc[2] = { 5,433 };
int Configs[2] = { 510,433 };
int CustomAA[2] = { 1015,433 };
#pragma region "Virtual Keys"
typedef struct
{
	char m_def[16];
	char m_alt[16];
}KeyStroke_t;

static KeyStroke_t g_KeyStrokes[ValveSDK::MOUSE_COUNT + ValveSDK::KEY_COUNT] =
{
	{ "", "" },
	{ "0", ")" },		//KEY_0,
	{ "1", "!" },		//KEY_1,
	{ "2", "\"" },		//KEY_2,
	{ "3", "£" },		//KEY_3,
	{ "4", "$" },		//KEY_4,
	{ "5", "%" },		//KEY_5,
	{ "6", "^" },		//KEY_6,
	{ "7", "&" },		//KEY_7,
	{ "8", "*" },		//KEY_8,
	{ "9", "(" },		//KEY_9,
	{ "a", "A" },		//KEY_A,
	{ "b", "B" },		//KEY_B,
	{ "c", "C" },		//KEY_C,
	{ "d", "D" },		//KEY_D,
	{ "e", "E" },		//KEY_E,
	{ "f", "F" },		//KEY_F,
	{ "g", "G" },		//KEY_G,
	{ "h", "H" },		//KEY_H,
	{ "i", "I" },		//KEY_I,
	{ "j", "J" },		//KEY_J,
	{ "k", "K" },		//KEY_K,
	{ "l", "L" },		//KEY_L,
	{ "m", "M" },		//KEY_M,
	{ "n", "N" },		//KEY_N,
	{ "o", "O" },		//KEY_O,
	{ "p", "P" },		//KEY_P,
	{ "q", "Q" },		//KEY_Q,
	{ "r", "R" },		//KEY_R,
	{ "s", "S" },		//KEY_S,
	{ "t", "T" },		//KEY_T,
	{ "u", "U" },		//KEY_U,
	{ "v", "V" },		//KEY_V,
	{ "w", "W" },		//KEY_W,
	{ "x", "X" },		//KEY_X,
	{ "y", "Y" },		//KEY_Y,
	{ "z", "|" },		//KEY_Z,
	{ "0", "0" },		//KEY_PAD_0,
	{ "1", "1" },		//KEY_PAD_1,
	{ "2", "2" },		//KEY_PAD_2,
	{ "3", "3" },		//KEY_PAD_3,
	{ "4", "4" },		//KEY_PAD_4,
	{ "5", "5" },		//KEY_PAD_5,
	{ "6", "6" },		//KEY_PAD_6,
	{ "7", "7" },		//KEY_PAD_7,
	{ "8", "8" },		//KEY_PAD_8,
	{ "9", "9" },		//KEY_PAD_9,
	{ "/", "/" },		//KEY_PAD_DIVIDE,
	{ "*", "*" },		//KEY_PAD_MULTIPLY,
	{ "-", "-" },		//KEY_PAD_MINUS,
	{ "+", "+" },		//KEY_PAD_PLUS,
	{ "", "" },			//KEY_PAD_ENTER,
	{ ".", ">" },		//KEY_PAD_DECIMAL,
	{ "[", "{" },		//KEY_LBRACKET,
	{ "]", "}" },		//KEY_RBRACKET,
	{ ";", ":" },		//KEY_SEMICOLON,
	{ "'", "@" },		//KEY_APOSTROPHE,
	{ "`", "¬" },		//KEY_BACKQUOTE,
	{ ",", "<" },		//KEY_COMMA,
	{ ".", ">" },		//KEY_PERIOD,
	{ "/", "?" },		//KEY_SLASH,
	{ "\\", "|" },		//KEY_BACKSLASH,
	{ "-", "_" },		//KEY_MINUS,
	{ "=", "+" },		//KEY_EQUAL,
	{ "", "" },			//KEY_ENTER,
	{ "", "" },			//KEY_SPACE,
	{ "", "" },			//KEY_BACKSPACE,
	{ "", "" },			//KEY_TAB,
	{ "", "" },			//KEY_CAPSLOCK,
	{ "", "" },			//KEY_NUMLOCK,
	{ "", "" },			//KEY_ESCAPE,
	{ "", "" },			//KEY_SCROLLLOCK,
	{ "", "" },			//KEY_INSERT,
	{ "", "" },			//KEY_DELETE,
	{ "", "" },			//KEY_HOME,
	{ "", "" },			//KEY_END,
	{ "", "" },			//KEY_PAGEUP,
	{ "", "" },			//KEY_PAGEDOWN,
	{ "", "" },			//KEY_BREAK,
	{ "", "" },			//KEY_LSHIFT,
	{ "", "" },			//KEY_RSHIFT,
	{ "", "" },			//KEY_LALT,
	{ "", "" },			//KEY_RALT,
	{ "", "" },			//KEY_LCONTROL,
	{ "", "" },			//KEY_RCONTROL,
	{ "", "" },			//KEY_LWIN,
	{ "", "" },			//KEY_RWIN,
	{ "", "" },			//KEY_APP,
	{ "", "" },			//KEY_UP,
	{ "", "" },			//KEY_LEFT,
	{ "", "" },			//KEY_DOWN,
	{ "", "" },			//KEY_RIGHT,
	{ "", "" },			//KEY_F1,
	{ "", "" },			//KEY_F2,
	{ "", "" },			//KEY_F3,
	{ "", "" },			//KEY_F4,
	{ "", "" },			//KEY_F5,
	{ "", "" },			//KEY_F6,
	{ "", "" },			//KEY_F7,
	{ "", "" },			//KEY_F8,
	{ "", "" },			//KEY_F9,
	{ "", "" },			//KEY_F10,
	{ "", "" },			//KEY_F11,
	{ "", ")" },		//KEY_F12,
	{ "", "" },			//KEY_CAPSLOCKTOGGLE,
	{ "", "" },			//KEY_NUMLOCKTOGGLE,
	{ "", "" },			//KEY_SCROLLLOCKTOGGLE,
	{ "", "" },			//MOUSE_LEFT = MOUSE_FIRST,
	{ "", "" },			//MOUSE_RIGHT,
	{ "", "" },			//MOUSE_MIDDLE,
	{ "", "" },			//MOUSE_4,
	{ "", "" },			//MOUSE_5,
	{ "", "" },			//MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	{ "", "" },			//MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down
};
#pragma endregion

CKeyInput::CKeyInput(void)
{

}

CKeyInput::~CKeyInput(void)
{
	m_strChar.clear();
}

void CKeyInput::Handle(int iKey)
{
	m_strChar.clear();

	if ((GetKeyState(VK_SHIFT) & 0x8000))
		m_strChar = g_KeyStrokes[iKey].m_alt;
	else m_strChar = g_KeyStrokes[iKey].m_def;
}

bool CMouseInput::ValidFlags(int flags)
{
	if (flags <= KEY_FLAG_NONE || flags == 3 || flags > KEY_FLAG_MOUSE5)
		return false;

	return true;
}

CMouseInput::CMouseInput(void)
{
	SetKey(KEY_FLAG_MOUSE1);
}

CMouseInput::CMouseInput(int flags)
{
	SetKey(flags);
}

bool CMouseInput::InEvent(int flags)
{
	auto bRetVal = false;
	auto iCurFlags = ValidFlags(flags) ? flags : m_iVirtualKey;

	static short last[10];
	for (int i = 0; i < KEY_FLAG_MOUSE5 + 1; i++)
	{
		short res = GetKeyState(i);
		if (!(res & 0x8000) && last[i] & 0x8000 && i == iCurFlags)
			bRetVal = true;
		last[i] = res;
	}

	return bRetVal;
}
bool CMouseInput::LeftClick(int x, int y, int w, int h)
{
	if (this->IsOver(x, y, w, h) && GetAsyncKeyState(VK_LBUTTON))
		return true;
	else
		return false;
}


bool CMouseInput::IsHover(int x, int y, int w, int h)
{
	Update();
	return((m_iXPosition > x && m_iXPosition < x + w) && (m_iYPosition > y && y + h > m_iYPosition));
}
bool CMouseInput::IsOver(int x, int y, int w, int h)
{
	if (m_iXPosition > x &&
		m_iXPosition < x + w &&
		m_iYPosition > y &&
		m_iYPosition < y + h)
		return true;
	else
		return false;
}


bool CMouseInput::IsPressed(int flags)
{
	int iCurFlags = ValidFlags(flags) ? flags : m_iVirtualKey;
	return (GetKeyState(iCurFlags) & 0x8000) ? true : false;
}

int CMouseInput::x(void)
{
	Update();
	return m_iXPosition;
}

int CMouseInput::y(void)
{
	Update();
	return m_iYPosition;
}

void CMouseInput::GetMousePosition(int& x, int& y)
{
	x = m_iXPosition;
	y = m_iYPosition;
}

void CMouseInput::SetKey(int flags)
{
	if (!ValidFlags(flags))
		return;

	m_iVirtualKey = flags;
}

void CMouseInput::Update(void)
{
	g_pSurface->GetCursorPos(m_iXPosition, m_iYPosition);
}

void CMenu::Echo(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char pszBuffer[0x400];
	vsprintf_s(pszBuffer, fmt, args);
	va_end(args);
	m_strHistory.push_back(pszBuffer);
}

void CMenu::FilterArgs(std::string strInput, std::vector< std::string >& strArgs)
{
	std::size_t nPos = 0;
	while (true)
	{
		nPos = strInput.find_first_of(" \n\0");
		if (nPos != std::string::npos)
		{
			strArgs.push_back(strInput.substr(0, nPos));
			strInput.erase(0, nPos + 1);
		}
		else
		{
			if (!strInput.empty())
				strArgs.push_back(strInput);

			break;
		}
	}
}

void CMenu::HandleInput(std::string strInput)
{
	if (strInput.empty())
		return;

	std::vector< std::string > strArgs;
	FilterArgs(strInput, strArgs);

	if (strArgs.empty())
		return;

	if (!strArgs[0].compare("clear"))
	{
		m_strHistory.clear();
		return;
	}

	Echo("] %s", strInput.c_str());
	if (!strArgs[0].compare("help"))
	{
		for (std::size_t i = 0; i < g_CVars.GetAllCVars().size(); i++)
		{
			CVar* pCVar = g_CVars.GetAllCVars()[i];
			if (!pCVar)
				continue;

			if (!pCVar->IsCommand()) {
				continue;
			}

			if (pCVar->HasArgs())
			{
				for (std::size_t j = 0; j < pCVar->GetAllArgs().size(); j++)
				{
					if (pCVar->GetFloat() == pCVar->GetAllArgs()[j].m_flValue)
						Echo("%s = %s(%s) // %s", pCVar->GetName().c_str(), pCVar->GetAllArgs()[j].m_strName.c_str(), pCVar->GetInfoString().c_str(), pCVar->GetDescription().c_str());
				}
			}
			else Echo("%s = %s // %s", pCVar->GetName().c_str(), pCVar->GetInfoString().c_str(), pCVar->GetDescription().c_str());
		}

		return;
	}

	if (g_CVars.IsCVar(strArgs[0]))
	{
		CVar* pCVar = g_CVars.GetCVar(strArgs[0]);
		if (strArgs.size() == 1)
		{
			if (pCVar->HasArgs())
			{
				for (std::size_t i = 0; i < pCVar->GetAllArgs().size(); i++)
				{
					if (pCVar->GetFloat() == pCVar->GetAllArgs()[i].m_flValue)
						Echo("%s = %s(%s) // %s", pCVar->GetName().c_str(), pCVar->GetAllArgs()[i].m_strName.c_str(), pCVar->GetInfoString().c_str(), pCVar->GetDescription().c_str());
				}
			}
			else Echo("%s = %s // %s", pCVar->GetName().c_str(), pCVar->GetInfoString().c_str(), pCVar->GetDescription().c_str());

			return;
		}

		if (isdigit(strArgs[1].c_str()[0]))
		{
			float flValue = std::strtof(strArgs[1].c_str(), NULL);
			pCVar->Set(flValue);

			if (pCVar->HasArgs())
			{
				for (std::size_t i = 0; i < pCVar->GetAllArgs().size(); i++)
				{
					if (pCVar->GetAllArgs()[i].m_flValue == pCVar->GetFloat())
					{
						Echo("set %s to %s(%s)", pCVar->GetName().c_str(), pCVar->GetAllArgs()[i].m_strName.c_str(), pCVar->GetInfoString().c_str());
						return;
					}
				}
			}

			Echo("set %s to %s", pCVar->GetName().c_str(), pCVar->GetInfoString().c_str());
			return;
		}
		else
		{
			std::transform(strArgs[1].begin(), strArgs[1].end(), strArgs[1].begin(), ::tolower);
			bool bTrue = (strArgs[1].compare("true") == 0) ? true : false;
			bool bFalse = (strArgs[1].compare("false") == 0) ? true : false;

			if (bTrue || bFalse)
			{
				pCVar->Set(bTrue);

				if (bTrue)
				{
					if (pCVar->HasArgs())
					{
						for (std::size_t i = 0; i < pCVar->GetAllArgs().size(); i++)
						{
							if (pCVar->GetAllArgs()[i].m_flValue == pCVar->GetFloat())
							{
								Echo("set %s to %s(%s)", pCVar->GetName().c_str(), pCVar->GetAllArgs()[i].m_strName.c_str(), pCVar->GetInfoString().c_str());
								return;
							}
						}
					}
				}

				Echo("set %s to %s", pCVar->GetName().c_str(), pCVar->GetBool() ? "true" : "false");
				return;
			}

			if (pCVar->HasArgs())
			{
				for (std::size_t i = 0; i < pCVar->GetAllArgs().size(); i++)
				{
					if (!pCVar->GetAllArgs()[i].m_strName.compare(strArgs[1]))
					{
						pCVar->SetByArg(strArgs[1]);
						Echo("set %s to %s(%s)", pCVar->GetName().c_str(), strArgs[1].c_str(), pCVar->GetInfoString().c_str());
						return;
					}
				}
			}
		}
	}
	Echo("Unknown command \"%s\" ", strInput.c_str());
}
bool tab[6] = {false,false,false,false,false,false};
void CMenu::RenderTab(int x, int y, float w, float h, std::string strText, int iIndex, int& iStatus)
{
	auto bActive = tab[iIndex];
	auto bHover = m_pMouseInput->IsHover(x, y, w, h);

	if (bHover && m_pMouseInput->InEvent())
	{
		iStatus = iIndex;
		tab[iIndex] = !tab[iIndex];
	}

	if (bActive)
	{ 
		//g_pRenderSurface->Rect(x, y, w, h, Color2);
		g_pRenderSurface->GardientRect(x, y, w, h, Selected, ValveSDK::Color(Selected.r() - 15, Selected.g() - 15, Selected.b() - 15, 255), 45);
		//g_pRenderSurface->GardientRect(x, y + h, w, 5, Color1, ValveSDK::Color(Color1.r() - 15, Color1.g() - 15, Color1.b() - 15, 255), 45);
	}
	else
		g_pRenderSurface->GardientRect(x, y, w, h, MenuTop, ValveSDK::Color(MenuTop.r() - 15, MenuTop.g() - 15, MenuTop.b() - 15, 255), 45);


	int iFontSize[2] = { 0 };
	g_pRenderSurface->GetTextSize("FONT_MENU", strText.c_str(), iFontSize);


	g_pRenderSurface->String(x + (w / 2) - (iFontSize[0] / 2), y + (h / 2) - (iFontSize[1] / 2), Font, "FONT_MENU", strText.c_str());
}

void CMenu::RenderButton(int x, int y, std::string strText, int iIndex, int& iClicked, bool untrusted)
{
	int m_iWidth = 128;
	int m_iHeight = 26;
	auto bHover = m_pMouseInput->IsHover(x, y, m_iWidth, m_iHeight);

	if (bHover && m_pMouseInput->InEvent())
		iClicked = iIndex;
	//skeet
	//gVars::dxRenderer->rect(Color(0, 0, 0).code(), real.x, real.y, size.x, size.y);
	//gVars::dxRenderer->rect(Color(48, 48, 48, 30).code(), real.x + 1, real.y + 1, size.x - 2, size.y - 2);

	g_pRenderSurface->RectOutlined2(x , y, m_iWidth, m_iHeight, 1, ValveSDK::Color(0, 0, 0, 255));
	if (bHover)
		g_pRenderSurface->GardientRect(x , y, m_iWidth, m_iHeight, ValveSDK::Color(31, 31, 31, 255), ValveSDK::Color(31, 31, 31, 255),45);
	else
		g_pRenderSurface->GardientRect(x, y, m_iWidth , m_iHeight , ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255),45);

	RECT TextSize =	g_pRenderSurface->GetTextSizeREC("FONT_MENU", strText.c_str());
	int TextX = x + (m_iWidth / 2) - (TextSize.left / 2);
	int TextY = y + (m_iHeight / 2) - (TextSize.bottom / 2);
	if (untrusted)
		g_pRenderSurface->String(TextX, TextY, Selected, "FONT_MENU", strText.c_str());
	else
		g_pRenderSurface->String(TextX, TextY, Font, "FONT_MENU", strText.c_str());

}

void CMenu::RenderCheckbox(int x, int y, std::string strText, std::string strCVar, bool untrusted)
{
	auto pCVar = g_CVars.GetCVar(strCVar);
	if (!pCVar)
		return;

	auto bActive = pCVar->GetBool();
	auto bHover = m_pMouseInput->IsHover(x, y, 8, 8);

	static auto size = 12;

	if (bHover)
		g_pRenderSurface->GardientRect(x, y , 8 , 8 , ValveSDK::Color(31, 31, 31, 255), ValveSDK::Color(31, 31, 31, 255), 45);
	else
		g_pRenderSurface->GardientRect(x , y, 8 , 8 , ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);

	if (bActive)
		g_pRenderSurface->GardientRect(x, y, 8, 8, Selected, ValveSDK::Color(Selected.r() - 15, Selected.g() - 15, Selected.b() - 15, 255), 45);
	g_pRenderSurface->RectOutlined2(x , y , 8 , 8 , 1, ValveSDK::Color(0, 0, 0, 255));
	int iFontSize[2] = { 0 };
	g_pRenderSurface->GetTextSize("FONT_MENU", strText, iFontSize);
	if (untrusted)
		g_pRenderSurface->String(x + size + 5, y + (size / 2) - (iFontSize[1] / 2) - 2, Selected, "FONT_MENU", strText.c_str());
	else
		g_pRenderSurface->String(x + size + 5, y + (size / 2) - (iFontSize[1] / 2) - 2, Font, "FONT_MENU", strText.c_str());

	if (pCVar && bHover && m_pMouseInput->InEvent())
	{
		pCVar->Set(!bActive);
	}
}
void CMenu::RenderCheckbox2(int x, int y, std::string strText, int player)
{


	auto bActive = Global::SelectedPlayerIgnore[player];
	auto bHover = m_pMouseInput->IsHover(x, y, 8, 8);

	static auto size = 12;

	if (bHover)
		g_pRenderSurface->GardientRect(x, y, 8, 8, ValveSDK::Color(31, 31, 31, 255), ValveSDK::Color(31, 31, 31, 255), 45);
	else
		g_pRenderSurface->GardientRect(x, y, 8, 8, ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);

	if (bActive)
		g_pRenderSurface->GardientRect(x, y, 8, 8, Selected, ValveSDK::Color(Selected.r() - 15, Selected.g() - 15, Selected.b() - 15, 255), 45);
	g_pRenderSurface->RectOutlined2(x, y, 8, 8, 1, ValveSDK::Color(0, 0, 0, 255));
	int iFontSize[2] = { 0 };
	g_pRenderSurface->GetTextSize("FONT_MENU", strText, iFontSize);

	g_pRenderSurface->String(x + size + 5, y + (size / 2) - (iFontSize[1] / 2) - 2, Font, "FONT_MENU", strText.c_str());

	if (bHover)
	{
		bActive = true;
	}
	else
	{
		bActive = false;
	}
}

void CMenu::RenderSlider(int x, int y, int w, int h, std::string strText, std::string strCVar, int isfloat)
{
	auto pCVar = g_CVars.GetCVar(strCVar);
	if (!pCVar)
		return;

	g_pRenderSurface->RectOutlined(x, y, w, h,1, ValveSDK::Color(35, 35, 35, 255), ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x , y ,w, h, ValveSDK::Color(31, 31, 31, 255), ValveSDK::Color(31, 31, 31, 255), 45);

	auto bHover = m_pMouseInput->IsHover(x, y, w, h);
	auto flValue = pCVar->GetFloat();
	if (flValue > pCVar->GetMax())
		flValue = pCVar->GetMax();

	if (flValue < pCVar->GetMin())
		flValue = pCVar->GetMin();
	auto flStep = float((w / pCVar->GetMax()) * flValue);

	int iCursorPos[2] = { 0 };
	m_pMouseInput->GetMousePosition(iCursorPos[0], iCursorPos[1]);

	float flDelta[2] = { 0.f };
	flDelta[0] = float(iCursorPos[0] - x);
	flDelta[1] = float(iCursorPos[1]);

	bHover = m_pMouseInput->IsHover(x - 3, y, w + 5, h);
	if (m_pMouseInput->IsPressed() && bHover)
	{
		if (!(flDelta[0] >= 0.f) || !(flDelta[0] <= w + 5))
			return;
		if (isfloat == 1)
		{
			flValue = (float)(pCVar->GetMin() + ((pCVar->GetMax() + pCVar->GetMin()) * (float)(flDelta[0] / w)));
			flValue += pCVar->GetMin();
		}
		else
		{
			flValue = ceil(pCVar->GetMin() + ((pCVar->GetMax() + pCVar->GetMin()) * (flDelta[0] / w)));
	
		}
		pCVar->Set(flValue);
		if (flValue > pCVar->GetMax())
			flValue = pCVar->GetMax();

		if (flValue < pCVar->GetMin())
			flValue = pCVar->GetMin();
		flStep = flDelta[0];

	}
	if (!flValue)
		flValue = pCVar->GetMin();
	char pszBuffer[12];

	if (isfloat == 1)
		sprintf_s(pszBuffer, "%.2f", flValue);
	else
		sprintf_s(pszBuffer, "%d", (int)flValue);
	auto strInfo = strText + std::string(" - ") + pszBuffer;
	int iFontSize[2] = { 0 };


	g_pRenderSurface->GetTextSize("FONT_MENU", strInfo, iFontSize);
	g_pRenderSurface->GardientRect(x, y, flStep, h, Selected, ValveSDK::Color(Selected.r() - 15, Selected.g() - 15, Selected.b() - 15, 255), 45);


	g_pRenderSurface->String(x + 2, y - h*2, Font, "FONT_MENU", strInfo.c_str());
}
void CMenu::RenderPlayerBox(int x, int y, int w, int h, std::vector< std::string > strNodes, std::string strCVar, bool& bState, std::string strName)
{
	auto pCVar = g_CVars.GetCVar(strCVar);
	if (!pCVar)
		return;

	auto iIndex = pCVar->GetInt();
	auto nSize = strNodes.size();

	if (iIndex >= (int)nSize)
		iIndex = (int)nSize - 1;

	int iFontSize[2] = { 0 };
	auto strCurrentString = strNodes[iIndex];

	g_pRenderSurface->GetTextSize("FONT_MENU", strCurrentString, iFontSize);
	//g_pRenderSurface->Rect( x, y, w, h, ValveSDK::Color( 50, 50, 50, 230 ) );
	g_pRenderSurface->String(x, y - 12.5, ValveSDK::Color(75, 75, 75, 255), "FONT_MENU", strName.c_str());
	g_pRenderSurface->RectOutlined(x, y, w, h, 1, ValveSDK::Color(35, 35, 35, 255), ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x, y, w, h, ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);
	g_pRenderSurface->String(x + 5, y + (h / 2) - (iFontSize[1] / 2), Font, "FONT_MENU", strCurrentString.c_str());

	if (m_pMouseInput->IsHover(x, y, w, h) && m_pMouseInput->InEvent())
		bState = !bState;

	if (bState)
	{
		auto Y = y + h;
		for (int i = 0; i < (int)nSize; i++)
		{
			auto bHover = m_pMouseInput->IsHover(x, Y + (i * iFontSize[1]), w, iFontSize[1]);


			g_pRenderSurface->Rect(x, Y + (i * iFontSize[1]), w, iFontSize[1], bHover ? ValveSDK::Color(53, 53, 53, 255) : ValveSDK::Color(31, 31, 31, 255));
			//g_pRenderSurface->GardientRect(x, Y + (i * iFontSize[1]), w, iFontSize[1], bHover ? ValveSDK::Color(31, 31, 31, 255) : ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);
			g_pRenderSurface->String(x + 5, Y + (i * iFontSize[1]), Font, "FONT_MENU", strNodes[i].c_str());

			if (bHover && m_pMouseInput->InEvent())
			{
				pCVar->Set(i);
				bState = false;
			}
		}

		if (m_pMouseInput->InEvent() && !m_pMouseInput->IsHover(x, Y, w, iFontSize[1] * nSize))
			bState = false;
	}
}
void CMenu::RenderComboBox(int x, int y, int w, int h, std::vector< std::string > strNodes, std::string strCVar, bool& bState, std::string strName)
{
	auto pCVar = g_CVars.GetCVar(strCVar);
	if (!pCVar)
		return;

	auto iIndex = pCVar->GetInt();
	auto nSize = strNodes.size();

	if (iIndex >= (int)nSize)
		iIndex = (int)nSize - 1;

	int iFontSize[2] = { 0 };
	auto strCurrentString = strNodes[iIndex];

	g_pRenderSurface->GetTextSize("FONT_MENU", strCurrentString, iFontSize);
	//g_pRenderSurface->Rect( x, y, w, h, ValveSDK::Color( 50, 50, 50, 230 ) );
	g_pRenderSurface->String(x, y - 12.5, ValveSDK::Color(75, 75, 75, 255), "FONT_MENU", strName.c_str());
	g_pRenderSurface->RectOutlined(x, y, w, h, 1, ValveSDK::Color(35, 35, 35, 255), ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x, y, w, h, ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);
	g_pRenderSurface->String(x + 5, y + (h / 2) - (iFontSize[1] / 2), Font, "FONT_MENU", strCurrentString.c_str());

	if (m_pMouseInput->IsHover(x, y, w, h) && m_pMouseInput->InEvent())
		bState = !bState;

	if (bState)
	{
		auto Y = y + h;
		for (int i = 0; i < (int)nSize; i++)
		{
			auto bHover = m_pMouseInput->IsHover(x, Y + (i * iFontSize[1]), w, iFontSize[1]);


			g_pRenderSurface->Rect(x, Y + (i * iFontSize[1]), w, iFontSize[1], bHover ? ValveSDK::Color(53, 53, 53, 255) : ValveSDK::Color(31, 31, 31, 255));
			//g_pRenderSurface->GardientRect(x, Y + (i * iFontSize[1]), w, iFontSize[1], bHover ? ValveSDK::Color(31, 31, 31, 255) : ValveSDK::Color(53, 53, 53, 255), ValveSDK::Color(31, 31, 31, 255), 45);
			g_pRenderSurface->String(x + 5, Y + (i * iFontSize[1]), Font, "FONT_MENU", strNodes[i].c_str());

			if (bHover && m_pMouseInput->InEvent())
			{
				pCVar->Set(i);
				bState = false;
			}
		}

		if (m_pMouseInput->InEvent() && !m_pMouseInput->IsHover(x, Y, w, iFontSize[1] * nSize))
			bState = false;
	}
}
void Save(int Config, const char *ConfigName)
{
	CSimpleIniA ini;
	ini.SetUnicode(true);
	if (Config == 0) return;
	if (Config == 1) ConfigName = "SINHOOKLEAGUE.ini";
	if (Config == 2) ConfigName = "SINHOOKRAGE.ini";
	if (Config == 3) ConfigName = "SINHOOKHVH.ini";
	if (Config == 4) ConfigName = "SINHOOKHVH2.ini";

	ini.SetDoubleValue("RAGEBOT", "rage_active", g_CVars.GetCVar("rage_active")->GetFloat(), "#rage_active");
	ini.SetDoubleValue("RAGEBOT", "rage_autoshoot", g_CVars.GetCVar("rage_autoshoot")->GetFloat(), "#rage_autoshoot");
	ini.SetDoubleValue("RAGEBOT", "rage_autowall", g_CVars.GetCVar("rage_autowall")->GetFloat(), "#rage_autowall");
	ini.SetDoubleValue("RAGEBOT", "rage_silent", g_CVars.GetCVar("rage_silent")->GetFloat(), "#rage_silent");
	ini.SetDoubleValue("RAGEBOT", "rage_norecoil", g_CVars.GetCVar("rage_norecoil")->GetFloat(), "#rage_norecoil");
	ini.SetDoubleValue("RAGEBOT", "rage_nospread", g_CVars.GetCVar("rage_nospread")->GetFloat(), "#rage_nospread");
	ini.SetDoubleValue("RAGEBOT", "rage_prediction", g_CVars.GetCVar("rage_prediction")->GetFloat(), "#rage_prediction");
	ini.SetDoubleValue("RAGEBOT", "rage_hitscan", g_CVars.GetCVar("rage_hitscan")->GetFloat(), "#rage_hitscan");
	ini.SetDoubleValue("RAGEBOT", "rage_autowall_damage", g_CVars.GetCVar("rage_autowall_damage")->GetFloat(), "#rage_autowall_damage");
	ini.SetDoubleValue("RAGEBOT", "rage_fov", g_CVars.GetCVar("rage_fov")->GetFloat(), "#rage_fov");
	ini.SetDoubleValue("RAGEBOT", "rage_hitchance_val", g_CVars.GetCVar("rage_hitchance_val")->GetFloat(), "#rage_hitchance_val");
	ini.SetDoubleValue("RAGEBOT", "rage_pointscale", g_CVars.GetCVar("rage_pointscale")->GetFloat(), "#rage_pointscale");
	ini.SetDoubleValue("RAGEBOT", "rage_prediction_mode", g_CVars.GetCVar("rage_prediction_mode")->GetFloat(), "#rage_prediction_mode");
	ini.SetDoubleValue("RAGEBOT", "rage_hitbox", g_CVars.GetCVar("rage_hitbox")->GetFloat(), "#rage_hitbox");
	ini.SetDoubleValue("RAGEBOT", "rage_multipoint", g_CVars.GetCVar("rage_multipoint")->GetFloat(), "#rage_multipoint");
	
	//=======================================================================================================================================

	ini.SetDoubleValue("LEGITBOT", "legit_active", g_CVars.GetCVar("legit_active")->GetFloat(), "#legit_active");
	ini.SetDoubleValue("LEGITBOT", "legit_autoshoot", g_CVars.GetCVar("legit_autoshoot")->GetFloat(), "#legit_autoshoot");
	ini.SetDoubleValue("LEGITBOT", "legit_silent", g_CVars.GetCVar("legit_silent")->GetFloat(), "#legit_silent");
	ini.SetDoubleValue("LEGITBOT", "legit_rcs", g_CVars.GetCVar("legit_rcs")->GetFloat(), "#legit_rcs");
	ini.SetDoubleValue("LEGITBOT", "legit_awpbaim", g_CVars.GetCVar("legit_awpbaim")->GetFloat(), "#legit_awpbaim");
	ini.SetDoubleValue("LEGITBOT", "legit_fov", g_CVars.GetCVar("legit_fov")->GetFloat(), "#legit_fov");
	ini.SetDoubleValue("LEGITBOT", "legit_smoothing", g_CVars.GetCVar("legit_smoothing")->GetFloat(), "#legit_smoothing");
	ini.SetDoubleValue("LEGITBOT", "legit_hitbox", g_CVars.GetCVar("legit_hitbox")->GetFloat(), "#legit_hitbox");

	//=======================================================================================================================================

	ini.SetDoubleValue("VISUALS", "vis_enabled", g_CVars.GetCVar("vis_enabled")->GetFloat(), "#vis_enabled");
	ini.SetDoubleValue("VISUALS", "vis_enemy", g_CVars.GetCVar("vis_enemy")->GetFloat(), "#vis_enemy");
	ini.SetDoubleValue("VISUALS", "vis_box", g_CVars.GetCVar("vis_box")->GetFloat(), "#vis_box");
	ini.SetDoubleValue("VISUALS", "vis_outlined", g_CVars.GetCVar("vis_outlined")->GetFloat(), "#vis_outlined");
	ini.SetDoubleValue("VISUALS", "vis_name", g_CVars.GetCVar("vis_name")->GetFloat(), "#vis_name");
	ini.SetDoubleValue("VISUALS", "vis_health", g_CVars.GetCVar("vis_health")->GetFloat(), "#vis_health");
	ini.SetDoubleValue("VISUALS", "vis_weapon", g_CVars.GetCVar("vis_weapon")->GetFloat(), "#vis_weapon");
	ini.SetDoubleValue("VISUALS", "vis_angles", g_CVars.GetCVar("vis_angles")->GetFloat(), "#vis_angles");
	ini.SetDoubleValue("VISUALS", "vis_glow", g_CVars.GetCVar("vis_glow")->GetFloat(), "#vis_glow");
	ini.SetDoubleValue("VISUALS", "vis_chams", g_CVars.GetCVar("vis_chams")->GetFloat(), "#vis_chams");
	ini.SetDoubleValue("VISUALS", "vis_handchams", g_CVars.GetCVar("vis_handchams")->GetFloat(), "#vis_handchams");
	ini.SetDoubleValue("VISUALS", "vis_weaponchams", g_CVars.GetCVar("vis_weaponchams")->GetFloat(), "#vis_weaponchams");
	ini.SetDoubleValue("VISUALS", "vis_norec", g_CVars.GetCVar("vis_norec")->GetFloat(), "#vis_norec");
	ini.SetDoubleValue("VISUALS", "vis_fov", g_CVars.GetCVar("vis_fov")->GetFloat(), "#vis_fov");
	ini.SetDoubleValue("VISUALS", "vis_radarsize", g_CVars.GetCVar("vis_radarsize")->GetFloat(), "#vis_radarsize");
	ini.SetDoubleValue("VISUALS", "vis_enemyinfo", g_CVars.GetCVar("vis_enemyinfo")->GetFloat(), "#vis_enemyinfo");
	ini.SetDoubleValue("VISUALS", "vis_noparticles", g_CVars.GetCVar("vis_noparticles")->GetFloat(), "#vis_noparticles");
	//=======================================================================================================================================

	ini.SetDoubleValue("MISC", "misc_antiaim", g_CVars.GetCVar("misc_antiaim")->GetFloat(), "#misc_antiaim");
	ini.SetDoubleValue("MISC", "misc_antiaimAT", g_CVars.GetCVar("misc_antiaimAT")->GetFloat(), "#misc_antiaimAT");
	ini.SetDoubleValue("MISC", "misc_edge", g_CVars.GetCVar("misc_edge")->GetFloat(), "#misc_edge");
	ini.SetDoubleValue("MISC", "misc_antiuntrusted", g_CVars.GetCVar("misc_antiuntrusted")->GetFloat(), "#misc_antiuntrusted");
	ini.SetDoubleValue("MISC", "misc_fakelag", g_CVars.GetCVar("misc_fakelag")->GetFloat(), "#misc_fakelag");
	ini.SetDoubleValue("MISC", "misc_fakelagval", g_CVars.GetCVar("misc_fakelagval")->GetFloat(), "#misc_fakelagval");
	ini.SetDoubleValue("MISC", "misc_resolver", g_CVars.GetCVar("misc_resolver")->GetFloat(), "#misc_resolver");
	ini.SetDoubleValue("MISC", "misc_autohop", g_CVars.GetCVar("misc_autohop")->GetFloat(), "#misc_autohop");
	ini.SetDoubleValue("MISC", "misc_autostrafe", g_CVars.GetCVar("misc_autostrafe")->GetFloat(), "#misc_autostrafe");
	ini.SetDoubleValue("MISC", "misc_circlestrafer", g_CVars.GetCVar("misc_circlestrafer")->GetFloat(), "#misc_circlestrafer");
	ini.SetDoubleValue("MISC", "misc_circlestraferval", g_CVars.GetCVar("misc_circlestraferval")->GetFloat(), "#misc_circlestraferval");
	ini.SetDoubleValue("MISC", "misc_fakelag_mode", g_CVars.GetCVar("misc_fakelag_mode")->GetFloat(), "#misc_fakelag_mode");
	ini.SetDoubleValue("MISC", "misc_aa", g_CVars.GetCVar("misc_aa")->GetFloat(), "#misc_aa");
	ini.SetDoubleValue("MISC", "misc_yaw", g_CVars.GetCVar("misc_yaw")->GetFloat(), "#misc_yaw");
	ini.SetDoubleValue("MISC", "misc_namespam", g_CVars.GetCVar("misc_namespam")->GetFloat(), "#misc_namespam");
	ini.SetDoubleValue("MISC", "misc_edge_yaw", g_CVars.GetCVar("misc_edge_yaw")->GetFloat(), "#misc_edge_yaw");
	ini.SetDoubleValue("MISC", "misc_edge_pitch", g_CVars.GetCVar("misc_edge_pitch")->GetFloat(), "#misc_edge_pitch");
	ini.SetDoubleValue("MISC", "misc_fakeduck", g_CVars.GetCVar("misc_fakeduck")->GetFloat(), "#misc_fakeduck");

	ini.SetDoubleValue("CONFIG", "config_menu", g_CVars.GetCVar("config_menu")->GetFloat(), "#config_menu");
	ini.SetDoubleValue("CONFIG", "ragebotx", Ragebot[0], "#ragebotx");
	ini.SetDoubleValue("CONFIG", "rageboty", Ragebot[1], "#rageboty");
	ini.SetDoubleValue("CONFIG", "legitbotx", Legitbot[0], "#legitbotx");
	ini.SetDoubleValue("CONFIG", "legitboty", Legitbot[1], "#legitboty");
	ini.SetDoubleValue("CONFIG", "visualsx", Visuals[0], "#visualsx");
	ini.SetDoubleValue("CONFIG", "visualsy", Visuals[1], "#visualsy");
	ini.SetDoubleValue("CONFIG", "miscx", Misc[0], "#miscx");
	ini.SetDoubleValue("CONFIG", "miscy", Misc[1], "#miscy");
	ini.SetDoubleValue("CONFIG", "configsx", Configs[0], "#configsx");
	ini.SetDoubleValue("CONFIG", "configsy", Configs[1], "#configsy");

	ini.SetDoubleValue("CUSTOMAA", "customaa_attarget", g_CVars.GetCVar("customaa_attarget")->GetFloat(), "#customaa_attarget");
	ini.SetDoubleValue("CUSTOMAA", "customaa_realanglex", g_CVars.GetCVar("customaa_realanglex")->GetFloat(), "#customaa_realanglex");
	ini.SetDoubleValue("CUSTOMAA", "customaa_fakeanglex", g_CVars.GetCVar("customaa_fakeanglex")->GetFloat(), "#customaa_fakeanglex");
	ini.SetDoubleValue("CUSTOMAA", "customaa_realangley", g_CVars.GetCVar("customaa_realangley")->GetFloat(), "#customaa_realangley");
	ini.SetDoubleValue("CUSTOMAA", "customaa_fakeangley", g_CVars.GetCVar("customaa_fakeangley")->GetFloat(), "#customaa_fakeangley");
	ini.SetDoubleValue("CUSTOMAA", "customaa_chokedticks", g_CVars.GetCVar("customaa_chokedticks")->GetFloat(), "#customaa_chokedticks");
	ini.SetDoubleValue("CUSTOMAA", "customaa_mode", g_CVars.GetCVar("customaa_mode")->GetFloat(), "#customaa_mode");
	ini.SaveFile(ConfigName);
}

void Load(int Config, const char *ConfigName)
{
	if (Config == 0) return;
	if (Config == 1) ConfigName = "SINHOOKLEAGUE.ini";
	if (Config == 2) ConfigName = "SINHOOKRAGE.ini";
	if (Config == 3) ConfigName = "SINHOOKHVH.ini";
	if (Config == 4) ConfigName = "SINHOOKHVH2.ini";
	CSimpleIniA ini;
	ini.SetUnicode(true);
	ini.LoadFile(ConfigName);

	g_CVars.GetCVar("rage_active")->Set(ini.GetDoubleValue("RAGEBOT", "rage_active", 0.0f));
	g_CVars.GetCVar("rage_autoshoot")->Set(ini.GetDoubleValue("RAGEBOT", "rage_autoshoot", 0.0f));
	g_CVars.GetCVar("rage_autowall")->Set(ini.GetDoubleValue("RAGEBOT", "rage_autowall", 0.0f));
	g_CVars.GetCVar("rage_silent")->Set(ini.GetDoubleValue("RAGEBOT", "rage_silent", 0.0f));
	g_CVars.GetCVar("rage_norecoil")->Set(ini.GetDoubleValue("RAGEBOT", "rage_norecoil", 0.0f));
	g_CVars.GetCVar("rage_nospread")->Set(ini.GetDoubleValue("RAGEBOT", "rage_nospread", 0.0f));
	g_CVars.GetCVar("rage_prediction")->Set(ini.GetDoubleValue("RAGEBOT", "rage_prediction", 0.0f));
	g_CVars.GetCVar("rage_hitscan")->Set(ini.GetDoubleValue("RAGEBOT", "rage_hitscan", 0.0f));
	g_CVars.GetCVar("rage_autowall_damage")->Set(ini.GetDoubleValue("RAGEBOT", "rage_autowall_damage", 0.0f));
	g_CVars.GetCVar("rage_fov")->Set(ini.GetDoubleValue("RAGEBOT", "rage_fov", 0.0f));
	g_CVars.GetCVar("rage_hitchance_val")->Set(ini.GetDoubleValue("RAGEBOT", "rage_hitchance_val", 0.0f));
	g_CVars.GetCVar("rage_pointscale")->Set(ini.GetDoubleValue("RAGEBOT", "rage_pointscale", 0.0f));
	g_CVars.GetCVar("rage_prediction_mode")->Set(ini.GetDoubleValue("RAGEBOT", "rage_prediction_mode", 0.0f));
	g_CVars.GetCVar("rage_hitbox")->Set(ini.GetDoubleValue("RAGEBOT", "rage_hitbox", 0.0f));
	g_CVars.GetCVar("rage_multipoint")->Set(ini.GetDoubleValue("RAGEBOT", "rage_multipoint", 0.0f));
	
	//=======================================================================================================================================

	g_CVars.GetCVar("legit_active")->Set(ini.GetDoubleValue("LEGITBOT", "legit_active", 0.0f));
	g_CVars.GetCVar("legit_autoshoot")->Set(ini.GetDoubleValue("LEGITBOT", "legit_autoshoot", 0.0f));
	g_CVars.GetCVar("legit_silent")->Set(ini.GetDoubleValue("LEGITBOT", "legit_silent", 0.0f));
	g_CVars.GetCVar("legit_rcs")->Set(ini.GetDoubleValue("LEGITBOT", "legit_rcs", 0.0f));
	g_CVars.GetCVar("legit_awpbaim")->Set(ini.GetDoubleValue("LEGITBOT", "legit_awpbaim", 0.0f));
	g_CVars.GetCVar("legit_fov")->Set(ini.GetDoubleValue("LEGITBOT", "legit_fov", 0.0f));
	g_CVars.GetCVar("legit_smoothing")->Set(ini.GetDoubleValue("LEGITBOT", "legit_smoothing", 0.0f));
	g_CVars.GetCVar("legit_hitbox")->Set(ini.GetDoubleValue("LEGITBOT", "legit_hitbox", 0.0f));

	//=======================================================================================================================================

	g_CVars.GetCVar("vis_enabled")->Set(ini.GetDoubleValue("VISUALS", "vis_enabled", 0.0f));
	g_CVars.GetCVar("vis_enemy")->Set(ini.GetDoubleValue("VISUALS", "vis_enemy", 0.0f));
	g_CVars.GetCVar("vis_box")->Set(ini.GetDoubleValue("VISUALS", "vis_box", 0.0f));
	g_CVars.GetCVar("vis_outlined")->Set(ini.GetDoubleValue("VISUALS", "vis_outlined", 0.0f));
	g_CVars.GetCVar("vis_name")->Set(ini.GetDoubleValue("VISUALS", "vis_name", 0.0f));
	g_CVars.GetCVar("vis_health")->Set(ini.GetDoubleValue("VISUALS", "vis_health", 0.0f));
	g_CVars.GetCVar("vis_weapon")->Set(ini.GetDoubleValue("VISUALS", "vis_weapon", 0.0f));
	g_CVars.GetCVar("vis_angles")->Set(ini.GetDoubleValue("VISUALS", "vis_angles", 0.0f));
	g_CVars.GetCVar("vis_glow")->Set(ini.GetDoubleValue("VISUALS", "vis_glow", 0.0f));
	g_CVars.GetCVar("vis_chams")->Set(ini.GetDoubleValue("VISUALS", "vis_chams", 0.0f));
	g_CVars.GetCVar("vis_handchams")->Set(ini.GetDoubleValue("VISUALS", "vis_handchams", 0.0f));
	g_CVars.GetCVar("vis_weaponchams")->Set(ini.GetDoubleValue("VISUALS", "vis_weaponchams", 0.0f));
	g_CVars.GetCVar("vis_norec")->Set(ini.GetDoubleValue("VISUALS", "vis_norec", 0.0f));
	g_CVars.GetCVar("vis_fov")->Set(ini.GetDoubleValue("VISUALS", "vis_fov", 0.0f));
	g_CVars.GetCVar("vis_radarsize")->Set(ini.GetDoubleValue("VISUALS", "vis_radarsize", 0.0f));
	g_CVars.GetCVar("vis_enemyinfo")->Set(ini.GetDoubleValue("VISUALS", "vis_enemyinfo", 0.0f));
	g_CVars.GetCVar("vis_noparticles")->Set(ini.GetDoubleValue("VISUALS", "vis_noparticles", 0.0f));

	//=======================================================================================================================================

	g_CVars.GetCVar("misc_antiaim")->Set(ini.GetDoubleValue("MISC", "misc_antiaim", 0.0f));
	g_CVars.GetCVar("misc_antiaimAT")->Set(ini.GetDoubleValue("MISC", "misc_antiaimAT", 0.0f));
	g_CVars.GetCVar("misc_edge")->Set(ini.GetDoubleValue("MISC", "misc_edge", 0.0f));
	g_CVars.GetCVar("misc_antiuntrusted")->Set(ini.GetDoubleValue("MISC", "misc_antiuntrusted", 0.0f));
	g_CVars.GetCVar("misc_fakelag")->Set(ini.GetDoubleValue("MISC", "misc_fakelag", 0.0f));
	g_CVars.GetCVar("misc_fakelagval")->Set(ini.GetDoubleValue("MISC", "misc_fakelagval", 0.0f));
	g_CVars.GetCVar("misc_resolver")->Set(ini.GetDoubleValue("MISC", "misc_resolver", 0.0f));
	g_CVars.GetCVar("misc_autohop")->Set(ini.GetDoubleValue("MISC", "misc_autohop", 0.0f));
	g_CVars.GetCVar("misc_autostrafe")->Set(ini.GetDoubleValue("MISC", "misc_autostrafe", 0.0f));
	g_CVars.GetCVar("misc_circlestrafer")->Set(ini.GetDoubleValue("MISC", "misc_circlestrafer", 0.0f));
	g_CVars.GetCVar("misc_circlestraferval")->Set(ini.GetDoubleValue("MISC", "misc_circlestraferval", 0.0f));
	g_CVars.GetCVar("misc_fakelag_mode")->Set(ini.GetDoubleValue("MISC", "misc_fakelag_mode", 0.0f));
	g_CVars.GetCVar("misc_aa")->Set(ini.GetDoubleValue("MISC", "misc_aa", 0.0f));
	g_CVars.GetCVar("misc_yaw")->Set(ini.GetDoubleValue("MISC", "misc_yaw", 0.0f));
	g_CVars.GetCVar("misc_namespam")->Set(ini.GetDoubleValue("MISC", "misc_namespam", 0.0f));
	g_CVars.GetCVar("misc_edge_yaw")->Set(ini.GetDoubleValue("MISC", "misc_edge_yaw", 0.0f));
	g_CVars.GetCVar("misc_edge_pitch")->Set(ini.GetDoubleValue("MISC", "misc_edge_pitch", 0.0f));
	g_CVars.GetCVar("misc_fakeduck")->Set(ini.GetDoubleValue("MISC", "misc_fakeduck", 0.0f));

	g_CVars.GetCVar("config_menu")->Set(ini.GetDoubleValue("CONFIG", "config_menu", 0.0f));

	Ragebot[0] = (ini.GetDoubleValue("CONFIG", "ragebotx", 0.0f));
	Ragebot[1] = (ini.GetDoubleValue("CONFIG", "rageboty", 0.0f));

	Legitbot[0] = (ini.GetDoubleValue("CONFIG", "legitbotx", 0.0f));
	Legitbot[1] = (ini.GetDoubleValue("CONFIG", "legitboty", 0.0f));

	Visuals[0] = (ini.GetDoubleValue("CONFIG", "visualsx", 0.0f));
	Visuals[1] = (ini.GetDoubleValue("CONFIG", "visualsy", 0.0f));

	Misc[0] = (ini.GetDoubleValue("CONFIG", "miscx", 0.0f));
	Misc[1] = (ini.GetDoubleValue("CONFIG", "miscy", 0.0f));

	Configs[0] = (ini.GetDoubleValue("CONFIG", "configsx", 0.0f));
	Configs[1] = (ini.GetDoubleValue("CONFIG", "configsy", 0.0f));

	//
	g_CVars.GetCVar("customaa_attarget")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_attarget", 0.0f));
	g_CVars.GetCVar("customaa_realanglex")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_realanglex", 0.0f));
	g_CVars.GetCVar("customaa_fakeanglex")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_fakeanglex", 0.0f));
	g_CVars.GetCVar("customaa_realangley")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_realangley", 0.0f));
	g_CVars.GetCVar("customaa_fakeangley")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_fakeangley", 0.0f));
	g_CVars.GetCVar("customaa_chokedticks")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_chokedticks", 0.0f));
	g_CVars.GetCVar("customaa_mode")->Set(ini.GetDoubleValue("CUSTOMAA", "customaa_mode", 0.0f));
}
void CMenu::Draw(int x, int y, int w, int h, const char *Text)
{

	g_pRenderSurface->Rect(x, y, w, h, ValveSDK::Color(28, 28, 28));
	//g_pRenderSurface->String(x, y, ValveSDK::Color(75, 75, 75, 255), "FONT_TABNOTE", Text);
}
void CMenu::RenderRageBotTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Aimbot");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Accuracy");
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Target");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Movement");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x -10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Ragebot");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	//Drag(w, 20);
	RenderCheckbox(x, y , "Active", "rage_active",false);
	RenderCheckbox(x, y + 20, "Autoshoot", "rage_autoshoot", false);
	RenderCheckbox(x, y + 40, "Autowall", "rage_autowall", false);
	RenderCheckbox(x, y + 60, "Silent", "rage_silent", false);
	RenderCheckbox(x, y + 80, "Static Aim", "rage_static", true);
	RenderCheckbox(x, y + 100, "No Recoil", "rage_norecoil", false);
	RenderCheckbox(x, y + 120, "No Spread", "rage_nospread", true);
	RenderCheckbox(x, y + 140, "Fakelag Prediction", "rage_prediction", false);
	RenderCheckbox(x, y + 160, "Hitscan", "rage_hitscan", false);
	RenderCheckbox(x, y + 180, "Smart Aim", "rage_smartaim", false);
	RenderCheckbox(x, y + 200, "AWP Body Aim", "rage_awpbaim", false);
	//RenderCheckbox(x, y + 225, "Auto Stop", "rage_autostop");
	//RenderCheckbox(x, y + 250, "Auto Crouch", "rage_autocrouch");

	RenderSlider(x + 190, y + 180, 285, 8, "Field Of View", "rage_fov",0);
	RenderSlider(x + 190, y + 220, 285, 8, "Minimum Damage", "rage_autowall_damage",0);
	RenderSlider(x + 190, y + 260, 285, 8, "Hitchance", "rage_hitchance_val",0);
	RenderSlider(x + 190, y + 300, 285, 8, "Pointscale", "rage_pointscale",1);
	if(!m_bAimHitboxCombo)
		RenderComboBox(x + 190, y + 45, 140, 20, m_strAimMultipointCombo, "rage_multipoint", m_bAimMultipointCombo, "Multipoint");
	RenderComboBox(x + 190, y + 5, 140, 20, m_strHitboxes, "rage_hitbox", m_bAimHitboxCombo,"Hitbox");

}
void CMenu::RenderLegitBotTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Aimbot");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Accuracy");
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Target");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Movement");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x - 10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Legitbot");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	RenderCheckbox(x, y, "Active", "legit_active", false);
	RenderCheckbox(x, y + 20, "Autoshoot", "legit_autoshoot", false);
	RenderCheckbox(x, y + 40, "Silent", "legit_silent", false);
	RenderCheckbox(x, y + 60, "RCS", "legit_rcs", false);
	RenderCheckbox(x, y + 80, "Sniper Body Aim", "legit_awpbaim", false);

	RenderSlider(x + 190, y + 180, 285, 8, "Field Of View", "legit_fov",0);
	RenderSlider(x + 190, y + 220, 285, 8, "Smoothing", "legit_smoothing",0);

	RenderComboBox(x + 190, y + 5, 140, 20, m_strLHitboxes, "legit_hitbox", m_bAimLHitboxCombo, "Hitbox");
}

void CMenu::RenderVisualsTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 150, h - 15, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Toggles");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y - 10, 150, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Switches");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 300, y - 10, 280, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Switches");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y + 150, 435, 285, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Sliders");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x - 10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Visuals");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	RenderCheckbox(x, y, "Active", "vis_enabled", false);
	RenderCheckbox(x, y + 20, "Enemies Only", "vis_enemy", false);
	RenderCheckbox(x, y + 40, "Box", "vis_box", false);
	RenderCheckbox(x, y + 60, "Outlined", "vis_outlined", false);
	RenderCheckbox(x, y + 80, "Name", "vis_name", false);
	RenderCheckbox(x, y + 100, "Health", "vis_health", false);
	RenderCheckbox(x, y + 120, "Weapon", "vis_weapon", false);
	RenderCheckbox(x, y + 140, "Angles", "vis_angles", false);
	RenderCheckbox(x, y + 160, "Radar", "vis_glow", false);
	RenderCheckbox(x, y + 180, "Player Chams", "vis_chams", false);
	RenderCheckbox(x, y + 200, "Hand Chams", "vis_handchams", false);
	RenderCheckbox(x, y + 220, "Weapon Chams", "vis_weaponchams", false);
	RenderCheckbox(x, y + 240, "No Visual Recoil", "vis_norec", false);
	RenderCheckbox(x, y + 260, "Enemy Info List", "vis_enemyinfo", false);
	RenderCheckbox(x, y + 280, "Disable Particles", "vis_noparticles", false);
	
	//RenderCheckbox(x, y + 275, "Snapline", "vis_snapline");
	//RenderCheckbox(x, y + 300, "Watermark", "vis_watermark");

	RenderSlider(x + 190, y + 180, 285, 8, "Player FOV", "vis_fov",0);
	RenderSlider(x + 190, y + 220, 285, 8, "Radar Size", "vis_radarsize",0);

}

void CMenu::RenderCustomAntiAimTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 150, h - 15, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Toggles");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y - 10, 150, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Switches");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 300, y - 10, 280, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Switches");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y + 150, 435, 285, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Sliders");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x - 10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Custom Anti-Aim");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	RenderCheckbox(x, y, "At-Targets", "customaa_attarget", false);

	RenderSlider(x + 190, y + 180, 285, 8, "Real Yaw Angle", "customaa_realangley", 1);
	RenderSlider(x + 190, y + 220, 285, 8, "Faked Yaw Angle", "customaa_fakeangley", 1);
	RenderSlider(x + 190, y + 260, 285, 8, "Real Pitch Angle", "customaa_realanglex", 1);
	RenderSlider(x + 190, y + 300, 285, 8, "Faked Pitch Angle", "customaa_fakeanglex", 1);
	RenderSlider(x + 190, y + 340, 285, 8, "Choked Ticks", "customaa_chokedticks", 0);
	RenderComboBox(x + 190, y + 5, 140, 20, m_strCustomAA, "customaa_mode", m_bCustomAACombo, "Mode");



}
void CMenu::RenderMiscTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Anti-Aim");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y - 10, 290, 250, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Other");
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Manipulation");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 290, y + 250, 290, 185, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Movement");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x - 10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Misc");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	RenderCheckbox(x, y, "Anti Aim", "misc_antiaim", false);
	RenderCheckbox(x, y + 20, "At Target", "misc_antiaimAT", false);
	RenderCheckbox(x, y + 40, "Edge", "misc_edge", false);
	RenderCheckbox(x, y + 60, "Fake-Duck", "misc_fakeduck", false);
	RenderCheckbox(x, y + 80, "Auto-Hop", "misc_autohop", false);
	RenderCheckbox(x, y + 100, "Auto-Strafe", "misc_autostrafe", false);
	RenderCheckbox(x, y + 120, "Circle-Strafe", "misc_circlestrafer", false);
	RenderCheckbox(x, y + 140, "Fakelag", "misc_fakelag", false);
	RenderCheckbox(x, y + 160, "Resolver", "misc_resolver", false);
	RenderCheckbox(x, y + 180, "Name-Spam", "misc_namespam", false);
	RenderCheckbox(x, y + 200, "Teleport", "misc_teleport", true);
	RenderCheckbox(x, y + 220, "Airstuck", "misc_airstuck", false);
	RenderCheckbox(x, y + 240, "Speedhack", "misc_speedhack", true);
	RenderCheckbox(x, y + 260, "Anti Untrusted", "misc_antiuntrusted", false);


	RenderSlider(x + 190, y + 180, 285, 8, "Choke", "misc_fakelagval", 0);

	if (!m_bEPitchAACombo)
		RenderComboBox(x + 335, y + 45, 140, 20, m_strEYawAA, "misc_edge_yaw", m_bEYawAACombo, "Edge Yaw");
	RenderComboBox(x + 335, y + 5, 140, 20, m_strEPitchAA, "misc_edge_pitch", m_bEPitchAACombo, "Edge Pitch");

	if (!m_bPitchAACombo && !m_bYawAACombo)
	RenderComboBox(x + 190, y + 85, 140, 20, m_strfakelagmode, "misc_fakelag_mode", m_bfakelagmodeCombo, "Fakelag");
	if (!m_bPitchAACombo)
		RenderComboBox(x + 190, y + 45, 140, 20, m_strYawAA, "misc_yaw", m_bYawAACombo,"Yaw");
	RenderComboBox(x + 190, y + 5, 140, 20, m_strPitchAA, "misc_aa", m_bPitchAACombo, "Pitch");
}

void CMenu::DrawPlayerList(int x, int y, int w, int h)
{
	int iTotalPlayers = 0;
	bool bFoundPlayer = false;
	for (int i = 1; i < 65; i++) {
		auto local = g_pTools->GetLocalPlayer();
		if (!local) return;
		if (i == g_pTools->GetLocalPlayer()->GetIndex()) continue;
		ValveSDK::CBaseEntity* pEnt = g_pEntityList->GetBaseEntity(i);
		if (!pEnt) continue;
		ValveSDK::IEngineClient::player_info_t pInfo;
		if (!g_pEngine->GetPlayerInfo(i, &pInfo)) continue;

		bool inBox = m_pMouseInput->IsHover(x + 5, y + 30 + iTotalPlayers * 15 + 10, 140, 15);
		if (inBox || Global::iSelectedPlayer == i)
			g_pRenderSurface->Rect2(x + 5, y + 30 + iTotalPlayers * 15 + 10, 140, 15, 110, 110, 110, 255);
		else
			g_pRenderSurface->Rect2(x + 5, y + 30 + iTotalPlayers * 15 + 10, 140, 15, 90, 90, 90, 255);
		int iFontSize[2] = { 0 };
		g_pRenderSurface->GetTextSize("FONT_MENU", pInfo.name, iFontSize);
		g_pRenderSurface->DrawStringA("FONT_MENU", false, x + 5 + 140 / 2 - iFontSize[0] / 2, +10 + y + 30 + iTotalPlayers * 15 + 15 / 2 - iFontSize[1] / 2, ValveSDK::Color(220, 220, 220, 255), pInfo.name);
		g_pRenderSurface->Line(x + 5, y + 30 + iTotalPlayers * 15 + 10, x + 5 + 140, y + 30 + iTotalPlayers * 15 + 10, ValveSDK::Color(0, 0, 0, 255));

		if (inBox && m_pMouseInput->InEvent())
			Global::iSelectedPlayer = i;

		if (Global::iSelectedPlayer == i) bFoundPlayer = true;

		iTotalPlayers++;
	}
	if (!bFoundPlayer) { Global::iSelectedPlayer = 0; return; }
	RenderCheckbox2(x + 180, y + 220, "Ignore", Global::iSelectedPlayer);
}
void CMenu::RenderConfigTab(int x, int y, int w, int h)
{
	//g_pRenderSurface->BorderBoxOutlinedText(x - 10, y - 10, 150, h - 15, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Buttons");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y - 10, 150, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Switches");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 300, y - 10, 280, 150, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Extra");
	//g_pRenderSurface->BorderBoxOutlinedText(x + 145, y + 150, 435, 285, 1, ValveSDK::Color(75, 75, 75), ValveSDK::Color(51, 51, 51), "Sliders");
	g_pRenderSurface->RectOutlined(x - 10, y - 40, w, h, 1, MenuBG, ValveSDK::Color(0, 0, 0, 255));
	g_pRenderSurface->GardientRect(x - 10, y - 40, w, 25, MenuTop, ValveSDK::Color(MenuTop.r() - 5, MenuTop.g() - 5, MenuTop.b() - 5, 255), 45);
	g_pRenderSurface->String(x + 2.5, y - 32.5, Font, "FONT_MENU", "Config");
	g_pRenderSurface->RectOutlined2(x - 5, y - 10, 180, h - 35, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y - 10, w - 195, 140, 1, MenuTop);
	g_pRenderSurface->RectOutlined2(x + 180, y + 135, w - 195, h - 180, 1, MenuTop);
	static std::string strButtons[5] = { "Save", "Load","sv_cheats","Thirdperson","Blank Name" };
	for (int i = 0; i < 5; i++)
	{
		bool trusted = false;
		if (i == 2)
			trusted = true;
		RenderButton(x, y + (i * 35) + (i * 5), strButtons[i], i, m_iCurrentButtonTap, trusted);
	}
	static bool init = false;
	




	const char *meme = "SINHOOKBACKUP.ini";
	int configs = g_CVars.GetCVar("config_config")->GetInt();
	switch (m_iCurrentButtonTap) {
	case 0:
		Save(configs, meme);
		m_iCurrentButtonTap = -1;
		break;
	case 1:
		Load(configs, meme);
		m_iCurrentButtonTap = -1;
		break;
	case 2:
	{	
		//auto svcheats = g_pICvar->FindVar("sv_cheats");
		//auto svcheatsspoof = new ValveSDK::SpoofedConvar(svcheats);
		//svcheatsspoof->SetInt(1);
		if (!g_CVars.GetCVar("misc_antiuntrusted")->GetBool())
		{
			ValveSDK::ConVar* Cheats = g_pICvar->FindVar("sv_cheats");
			*(int*)((DWORD)&Cheats->fnChangeCallback + 0xC) = 0;
			Cheats->SetValue(1);
		}
		m_iCurrentButtonTap = -1;
	}
		break;
	case 3:
		g_pEngine->ExecuteClientCmd("thirdperson");
		m_iCurrentButtonTap = -1;
		break;
	case 4:
		ValveSDK::ConVar* Name = g_pICvar->FindVar("name");
		Name->SetValue("\n");

		m_iCurrentButtonTap = -1;
		break;
	}

	if (!m_bCircleCombo)
		RenderComboBox(x + 335, y + 45, 140, 20, m_strAirstuckKey, "config_airstuckhotkey", m_bAirstuckCombo, "Airstuck Key");
	RenderComboBox(x + 335, y + 5, 140, 20, m_strCircleKey, "config_circlehotkey", m_bCircleCombo, "Circle Strafe Key");

	if (!m_bConfigs && !m_bMenuCombo)
		RenderComboBox(x + 190, y + 85, 140, 20, m_strTeleportKey, "config_teleporthotkey", m_bTeleportCombo, "Teleport Key");
	if (!m_bConfigs)
		RenderComboBox(x + 190, y + 45, 140, 20, m_strMenuCombo, "config_menu", m_bMenuCombo, "Menu Color");
	RenderComboBox(x + 190, y + 5, 140, 20, m_strConfigs, "config_config", m_bConfigs, "Config");

	auto pLocalEntity = g_pTools->GetLocalPlayer();

	//DrawPlayerList(x, y + 120, w, h);
}

void _FixPos(int& x, int& y, int X, int Y)
{
	x += X;
	y += Y;
}
void _FixSize(int& w, int& h, int W, int H)
{
	w += W;
	h += H;
}

void CMenu::RenderConsole(int x, int y, int w, int h)
{
	int iFontSize[2] = { 0 };
	if (!m_strHistory.empty())
	{
		auto X = x + 5;
		if (m_strHistory.size() < 34)
		{
			for (std::size_t i = 0; i < m_strHistory.size(); i++)
			{
				g_pRenderSurface->GetTextSize("FONT_MENU", m_strHistory[i], iFontSize);
				auto Y = y + (i * iFontSize[1]) + 2;
				g_pRenderSurface->String(X, Y, ValveSDK::Color(40, 40, 40, 255), "FONT_MENU", m_strHistory[i].c_str());
			}
		}
		else
		{
			for (std::size_t i = 0; i < 34; i++)
			{
				g_pRenderSurface->GetTextSize("FONT_MENU", m_strHistory[i], iFontSize);
				auto Y = y + (i * iFontSize[1]) + 2;
				g_pRenderSurface->String(X, Y, ValveSDK::Color(40, 40, 40, 255), "FONT_MENU", m_strHistory[i + m_strHistory.size() - 34].c_str());
			}
		}
	}

	if (!m_strCurrentInput.empty())
	{
		g_pRenderSurface->GetTextSize("FONT_MENU", m_strCurrentInput, iFontSize);
		g_pRenderSurface->String(x - 10, y + h - 20 - (iFontSize[1] / 2), ValveSDK::Color(40, 40, 40, 255), "FONT_MENU", m_strCurrentInput.c_str());
	}


}


static bool draggingR = false;
void CMenu::DragRagebot(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { Ragebot[0], Ragebot[1] };
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
			iXDif = iMousePosition[0] - Ragebot[0];
			iYDif = iMousePosition[1] - Ragebot[1];
		}
		Ragebot[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		Ragebot[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
static bool draggingL = false;
void CMenu::DragLegitbot(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { Legitbot[0], Legitbot[1] };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingL = true;
	else if (!m_pMouseInput->IsPressed())
		draggingL = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingL)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - Legitbot[0];
			iYDif = iMousePosition[1] - Legitbot[1];
		}
		Legitbot[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		Legitbot[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
static bool draggingV = false;
void CMenu::DragVisuals(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { Visuals[0], Visuals[1] };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingV = true;
	else if (!m_pMouseInput->IsPressed())
		draggingV = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingV)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - Visuals[0];
			iYDif = iMousePosition[1] - Visuals[1];
		}
		Visuals[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		Visuals[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
static bool draggingM = false;
void CMenu::DragMisc(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { Misc[0], Misc[1] };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingM = true;
	else if (!m_pMouseInput->IsPressed())
		draggingM = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingM)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - Misc[0];
			iYDif = iMousePosition[1] - Misc[1];
		}
		Misc[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		Misc[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
static bool draggingC = false;
void CMenu::DragConfig(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { Configs[0], Configs[1] };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingC = true;
	else if (!m_pMouseInput->IsPressed())
		draggingC = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingC)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - Configs[0];
			iYDif = iMousePosition[1] - Configs[1];
		}
		Configs[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		Configs[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
static bool draggingCAA = false;
void CMenu::DragCustomAA(int w, int h)
{
	if (!m_pMouseInput)
		return;

	static int iXDif = 0;
	static int iYDif = 0;
	bool bDrag = false;
	int iMousePosition[2] = { 0 };
	m_pMouseInput->GetMousePosition(iMousePosition[0], iMousePosition[1]);

	int iCurrentPosition[2] = { CustomAA[0], CustomAA[1] };
	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h))
		draggingCAA = true;
	else if (!m_pMouseInput->IsPressed())
		draggingCAA = false;

	if (m_pMouseInput->LeftClick(iCurrentPosition[0], iCurrentPosition[1], w, h) || draggingCAA)
	{
		if (!bDrag)
			bDrag = true;
		if (iXDif == -1 || iYDif == -1)
		{
			iXDif = iMousePosition[0] - CustomAA[0];
			iYDif = iMousePosition[1] - CustomAA[1];
		}
		CustomAA[0] += iMousePosition[0] - (iXDif + iCurrentPosition[0]);
		CustomAA[1] += iMousePosition[1] - (iYDif + iCurrentPosition[1]);
	}
	else
	{
		if (bDrag)
			bDrag = false;
		iXDif = -1;
		iYDif = -1;
	}
}
CMenu::CMenu(void)
{
	m_bActive = false;
	m_bAimHitboxCombo = false;
	m_bSmartHitboxCombo = false;
	m_bAimAtCombo = false;
	m_bAimHitscanCombo = false;
	m_bVisBoxCombo = false;
	m_bVisWeaponsCombo = false;
	m_bPitchAACombo = false;
	m_bYawAACombo = false;
	m_bAimHitboxCombo = false;
	m_bAimHitscanCombo = false;
	m_bKnifeChangerCombo = false;
	m_bPitchAACombo = false;
	m_bYawAACombo = false;
	m_bEdgeCombo = false;
	m_bfakelagmodeCombo = false;
	m_bAimSilentCombo = false;
	m_bAimBonefixCombo = false;
	m_bVisBoxCombo = false;
	m_bVisWeaponsCombo = false;
	m_bVisHandsCombo = false;
	m_bVisChamsCombo = false;

	SetPosition(250, 250);
	m_iW = 500;
	m_iH = 400;
	m_iCurrentTap = 0;

	m_pMouseInput = new CMouseInput(1);
	m_pKeyInput = new CKeyInput();


	m_strHitboxes.push_back("Head");
	m_strHitboxes.push_back("Neck");
	m_strHitboxes.push_back("Lower Neck");
	m_strHitboxes.push_back("Pelvis");
	m_strHitboxes.push_back("Body");
	m_strHitboxes.push_back("Thorax");
	m_strHitboxes.push_back("Chest");
	m_strHitboxes.push_back("Upper Chest");

	m_strLHitboxes.push_back("Head");
	m_strLHitboxes.push_back("Neck");
	m_strLHitboxes.push_back("Lower Neck");
	m_strLHitboxes.push_back("Pelvis");
	m_strLHitboxes.push_back("Body");
	m_strLHitboxes.push_back("Thorax");
	m_strLHitboxes.push_back("Chest");
	m_strLHitboxes.push_back("Upper Chest");
	//misc
	m_strfakelagmode.push_back("Normal");
	m_strfakelagmode.push_back("Adaptive");
	m_strfakelagmode.push_back("Switch");
	m_strfakelagmode.push_back("Random");
	m_strfakelagmode.push_back("Cycle");
	m_strfakelagmode.push_back("Revolve");

	m_strBonefix.push_back("Learning");
	//m_strBonefix.push_back("Vector-Based");

	m_strConfigs.push_back("None");
	m_strConfigs.push_back("League");
	m_strConfigs.push_back("Rage");
	m_strConfigs.push_back("HvH");
	m_strConfigs.push_back("HvH2");

	m_strAimMultipointCombo.push_back("Disabled");
	m_strAimMultipointCombo.push_back("Low");
	m_strAimMultipointCombo.push_back("Medium");
	m_strAimMultipointCombo.push_back("High");
	m_strAimMultipointCombo.push_back("Extreme");

	m_strPitchAA.push_back("Disabled");
	m_strPitchAA.push_back("Down");
	m_strPitchAA.push_back("Fake-Down");
	m_strPitchAA.push_back("Lisp-Down");
	m_strPitchAA.push_back("Lisp-Up");
	m_strPitchAA.push_back("Zero");
	m_strPitchAA.push_back("Custom");

	m_strEPitchAA.push_back("Disabled");
	m_strEPitchAA.push_back("Down");
	m_strEPitchAA.push_back("Fake-Down");
	m_strEPitchAA.push_back("Lisp-Down");

	m_strEYawAA.push_back("Disabled");
	m_strEYawAA.push_back("In");
	m_strEYawAA.push_back("Out");
	m_strEYawAA.push_back("Jitter");
	m_strEYawAA.push_back("Fake-Out");
	m_strEYawAA.push_back("Lisp");

	m_strMenuCombo.push_back("Blue");
	m_strMenuCombo.push_back("Red");
	m_strMenuCombo.push_back("Green");
	m_strMenuCombo.push_back("Orange");
	m_strMenuCombo.push_back("Purple");
	m_strMenuCombo.push_back("Rainbow");

	m_strYawAA.push_back("Disabled");
	m_strYawAA.push_back("Backwards");
	m_strYawAA.push_back("Fake-Backwards");
	m_strYawAA.push_back("Fake-Sideways");
	m_strYawAA.push_back("Fake-Forwards");
	m_strYawAA.push_back("Jitter");
	m_strYawAA.push_back("Side-Jitter");
	m_strYawAA.push_back("Backwards-Jitter");
	m_strYawAA.push_back("Fast-Spin");
	m_strYawAA.push_back("Fake-Jitter");
	m_strYawAA.push_back("Rotate");
	m_strYawAA.push_back("Lisp");
	m_strYawAA.push_back("Lisp-Backwards");
	m_strYawAA.push_back("Lisp-Sideways");
	m_strYawAA.push_back("Lisp-Jitter");
	m_strYawAA.push_back("Lisp-Spin");
	m_strYawAA.push_back("Custom");
	//
	m_strTeleportKey.push_back("Mouse4");
	m_strTeleportKey.push_back("Mouse5");
	m_strTeleportKey.push_back("Shift");
	m_strTeleportKey.push_back("Alt");
	m_strTeleportKey.push_back("Ctrl");

	m_strCircleKey.push_back("Mouse4");
	m_strCircleKey.push_back("Mouse5");
	m_strCircleKey.push_back("Shift");
	m_strCircleKey.push_back("Alt");
	m_strCircleKey.push_back("Ctrl");

	m_strAirstuckKey.push_back("Mouse4");
	m_strAirstuckKey.push_back("Mouse5");
	m_strAirstuckKey.push_back("Shift");
	m_strAirstuckKey.push_back("Alt");
	m_strAirstuckKey.push_back("Ctrl");

	m_strCustomAA.push_back("Add");
	m_strCustomAA.push_back("Jitter");
	m_strCustomAA.push_back("Lisp");
	m_strCustomAA.push_back("Spin");
	m_strCustomAA.push_back("Fake-Angles");
}

CMenu::~CMenu(void)
{
	SafeDelete(&m_pMouseInput);
}

void CMenu::SetActive(bool active)
{
	m_bActive = active;
	
	if (g_pEngine->IsIngame())
	{
		char pszBuffer[0x200];
		sprintf_s(pszBuffer, "cl_mouseenable %d", !active);
		g_pEngine->ClientCmd(pszBuffer);
	}
}

void CMenu::HandleInputChar(int iKey)
{
	if (iKey == ValveSDK::KEY_INSERT)
		SetActive(!m_bActive);
	if(g_pIInput)
	g_pIInput->EnableInput(!m_bActive);
	if (!m_bActive)
		return;

	if (m_iCurrentTap != 4)
		return;

	if (!m_pKeyInput)
		return;

	m_pKeyInput->Handle(iKey);

	switch (iKey)
	{
	case ValveSDK::KEY_ENTER:
		HandleInput(m_strCurrentInput);
		m_strCurrentInput.clear();
		return;
	case ValveSDK::KEY_SPACE:
		m_strCurrentInput.append(" ");
		return;
	case ValveSDK::KEY_BACKSPACE:
		if (!m_strCurrentInput.empty())
			m_strCurrentInput.erase(m_strCurrentInput.length() - 1);
		return;
	}

	m_strCurrentInput.append(m_pKeyInput->m_strChar);
}
void CMenu::Render(void)
{


	auto x = m_iX;
	auto y = m_iY;
	auto w = m_iW;
	auto h = m_iH;
	auto mW = w;
	static float MenuTabSelection = -75.f;
	if (!m_bActive)
	{
		MenuTabSelection = -75.f;
	}
	if (!m_bActive)
		return;

	float iAddValue = ((fabs(MenuTabSelection) + 1.f) / 75.f) * 750.f;
	MenuTabSelection += (g_pGlobalVarsBase->frametime * iAddValue) * ((m_bActive) ? 1.f : -1.f);
	if (MenuTabSelection > 0)
		MenuTabSelection = 0.f;
	else if (MenuTabSelection <= -75.f)
		MenuTabSelection = -75.f;

	static std::string strTabs[6] = { "RageBot", "LegitBot", "Visuals", "Misc", "Configs","Custom Anti-Aim" };
	int iScreenWidth, iScreenHeight;
	g_pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
	int tabsize;
	if (iScreenWidth)
	{
		tabsize = iScreenWidth / 6;
	}
	for (int i = 0; i < 6; i++)
	{
		RenderTab(0 + (i) * (tabsize), MenuTabSelection, tabsize, 25, strTabs[i], i, m_iCurrentTap);
	}

	if (tab[0] == true)
	{
		RenderRageBotTab(Ragebot[0] + 10, Ragebot[1] + 40, w, h);
		DragRagebot(w, 20);
	}
	if (tab[1] == true)
	{
		RenderLegitBotTab(Legitbot[0] + 10, Legitbot[1] + 40, w, h);
		DragLegitbot(w, 20);
	}
	if (tab[2] == true)
	{
		RenderVisualsTab(Visuals[0] + 10, Visuals[1] + 40, w, h);
		DragVisuals(w, 20);
	}
	if (tab[3] == true)
	{
		RenderMiscTab(Misc[0] + 10, Misc[1] + 40, w, h);
		DragMisc(w, 20);
	}
	if (tab[4] == true)
	{
		RenderConfigTab(Configs[0] + 10, Configs[1] + 40, w, h);
		DragConfig(w, 20);
	}
	if (tab[5] == true)
	{
		RenderCustomAntiAimTab(CustomAA[0] + 10, CustomAA[1] + 40, w, h);
		DragCustomAA(w, 20);
	}


	int iCursorPos[2] = { 0 };
	m_pMouseInput->GetMousePosition(iCursorPos[0], iCursorPos[1]);
	g_pRenderSurface->Rect2(iCursorPos[0] + 1, iCursorPos[1], 1, 17, 3, 6, 26, 255);
	for (int i = 0; i < 11; i++)
		g_pRenderSurface->Rect2(iCursorPos[0] + 2 + i, iCursorPos[1] + 1 + i, 1, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 8, iCursorPos[1] + 12, 5, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 8, iCursorPos[1] + 13, 1, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 9, iCursorPos[1] + 14, 1, 2, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 10, iCursorPos[1] + 16, 1, 2, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 8, iCursorPos[1] + 18, 2, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 7, iCursorPos[1] + 16, 1, 2, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 6, iCursorPos[1] + 14, 1, 2, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 5, iCursorPos[1] + 13, 1, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 4, iCursorPos[1] + 14, 1, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 3, iCursorPos[1] + 15, 1, 1, 3, 6, 26, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 2, iCursorPos[1] + 16, 1, 1, 3, 6, 26, 255);
	for (int i = 0; i < 4; i++)
		g_pRenderSurface->Rect2(iCursorPos[0] + 2 + i, iCursorPos[1] + 2 + i, 1, 14 - (i * 2), 255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 6, iCursorPos[1] + 6, 1, 8, 235, 235, 235, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 7, iCursorPos[1] + 7, 1, 9, 231, 231, 231, 255);
	for (int i = 0; i < 4; i++)
		g_pRenderSurface->Rect2(iCursorPos[0] + 8 + i, iCursorPos[1] + 8 + i, 1, 4 - i, 227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 8, iCursorPos[1] + 14, 1, 4, 207, 207, 207, 255);
	g_pRenderSurface->Rect2(iCursorPos[0] + 9, iCursorPos[1] + 16, 1, 2, 203, 203, 203, 255);
	
}

void CMenu::SetPosition(int x, int y)
{
	m_iX = x;
	m_iY = y;

}

CMenu* g_pMenu = nullptr;