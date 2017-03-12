#ifndef __MENU_H__
#define __MENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"
#include "simpleini.h"
enum eKeyFlags
{
	KEY_FLAG_NONE = 0,
	KEY_FLAG_MOUSE1,
	KEY_FLAG_MOUSE2,
	KEY_FLAG_MOUSE3 = 4,
	KEY_FLAG_MOUSE4,
	KEY_FLAG_MOUSE5,
};

class CKeyInput
{
public:
	std::string	m_strChar;

public:
	CKeyInput(void);
	~CKeyInput(void);
	void Handle(int iKey);
};

class CMouseInput
{
public:
	int		m_iVirtualKey;
	int		m_iXPosition;
	int		m_iYPosition;

private:
	bool	ValidFlags(int flags);

public:
	CMouseInput(void);
	CMouseInput(int flags);
	bool	InEvent(int flags = KEY_FLAG_NONE);
	bool	IsHover(int x, int y, int w, int h);
	bool	IsPressed(int flags = KEY_FLAG_NONE);
	int		x(void);
	int		y(void);
	void	GetMousePosition(int& x, int& y);
	void	SetKey(int flags);
	void	Update(void);
	bool LeftClick(int x, int y, int w, int h);
	bool IsOver(int x, int y, int w, int h);
};

class CMenu
{
private:
	bool			m_bActive;
	bool			m_bAimHitboxCombo;
	bool			m_bAimMultipointCombo;
	bool			m_bAimLHitboxCombo;
	bool			m_bSmartHitboxCombo;
	bool			m_bAimAtCombo;
	bool			m_bAimHitscanCombo;
	bool			m_bKnifeChangerCombo;
	bool			m_bPitchAACombo;
	bool			m_bCustomAACombo;
	bool			m_bConfigs;
	bool			m_bYawAACombo;
	bool			m_bEYawAACombo;
	bool			m_bEPitchAACombo;
	bool			m_bMenuCombo;
	bool			m_bEdgeCombo;
	bool			m_bfakelagmodeCombo;
	//
	bool			m_bTeleportCombo;
	bool			m_bCircleCombo;
	bool			m_bAirstuckCombo;
	//
	bool			m_baaamodeCombo;
	bool			m_bAimSilentCombo;
	bool			m_bAimBonefixCombo;
	bool			m_bVisBoxCombo;
	bool			m_bVisWeaponsCombo;
	bool			m_bVisHandsCombo;
	bool			m_bVisChamsCombo;
	bool			m_bPlayersCombo;
	int				m_iX;
	int				m_iY;
	int				m_iW;
	int				m_iH;
	CKeyInput*		m_pKeyInput;
	CMouseInput*	m_pMouseInput;
	std::vector< std::string >	m_strAimMultipointCombo;
	std::vector< std::string >	m_strKnifeChanger;
	std::vector< std::string >	m_strPitchAA;
	std::vector< std::string >	m_strYawAA;
	std::vector< std::string >	m_strCustomAA;
	std::vector< std::string >	m_strEYawAA;
	std::vector< std::string >	m_strEPitchAA;
	std::vector< std::string >	m_strMenuCombo;
	std::vector< std::string >	m_strEdgeAA;

	//
	std::vector< std::string >	m_strTeleportKey;
	std::vector< std::string >	m_strAirstuckKey;
	std::vector< std::string >	m_strCircleKey;
	//
	std::vector< std::string >	m_strfakelagmode;
	std::vector< std::string >	m_straaamode;
	std::vector< std::string >	m_strHitboxes;
	std::vector< std::string >	m_strLHitboxes;
	std::vector< std::string >	m_strAimAt;
	std::vector< std::string >	m_strHitscans;
	std::vector< std::string >	m_strSilent;
	std::vector< std::string >	m_strBonefix;
	std::string					m_strCurrentInput;
	std::vector< std::string >	m_strHistory;
	std::vector< std::string >	m_strVisBoxes;
	std::vector< std::string >	m_strVisWeapons;
	std::vector< std::string >	m_strVisHands;
	std::vector< std::string >	m_strVisChams;
	std::vector< std::string >	m_strConfigs;
	std::vector< std::string >	m_strPlayers[128];
	int				m_iCurrentTap;
	int				m_iCurrentButtonTap;
private:
	void Echo(const char* fmt, ...);
	void FilterArgs(std::string strInput, std::vector< std::string >& strArgs);
	void HandleInput(std::string strInput);
	void RenderTab(int x, int y, float w, float h, std::string strText, int iIndex, int& iStatus);
	void RenderButton(int x, int y, std::string strText, int iIndex, int & iClicked, bool untrusted = false);
	void RenderCheckbox(int x, int y, std::string strText, std::string strCVar, bool untrusted);
	void RenderSlider(int x, int y, int w, int h, std::string strText, std::string strCVar, int isfloat);
	void RenderComboBox(int x, int y, int w, int h, std::vector< std::string > strNotes, std::string strCVar, bool& bState, std::string strName);
	void RenderPlayerBox(int x, int y, int w, int h, std::vector< std::string > strNotes, std::string strCVar, bool& bState, std::string strName);
	void Draw(int x, int y, int w, int h, const char *Text);
	void DragRagebot(int w, int h);
	void DragLegitbot(int w, int h);
	void DragVisuals(int w, int h);
	void DragMisc(int w, int h);
	void DragConfig(int w, int h);
	void DrawPlayerList(int x, int y, int w, int h);
	void RenderRageBotTab(int x, int y, int w, int h);
	void RenderLegitBotTab(int x, int y, int w, int h);
	void RenderVisualsTab(int x, int y, int w, int);
	void RenderMiscTab(int x, int y, int w, int h);
	void RenderConsole(int x, int y, int w, int h);
	void RenderConfigTab(int x, int y, int w, int h);
	void RenderCustomAntiAimTab(int x, int y, int w, int h);
	void RenderCheckbox2(int x, int y, std::string strText, int strCVar);
	void DragCustomAA(int w, int h);
public:
	CMenu(void);
	~CMenu(void);
	void SetActive(bool active);
	void HandleInputChar(int iKey);
	void Render(void);
	void SetPosition(int x, int y);
};

extern CMenu* g_pMenu;

#endif