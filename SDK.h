#ifndef __SDK_H__
#define __SDK_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "checksum_crc.h"
#include "const.h"
#include "NetVars.h"
#include "Vector.h"
#include "Offsets.h"
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define hackname "slayer"
#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / g_pGlobalVarsBase->interval_per_tick ) )
#define TICKS_TO_TIME( t ) ( g_pGlobalVarsBase->interval_per_tick *( t ) )

namespace Global
{
	extern ValveSDK::QAngle VisualAngle;
	extern ValveSDK::QAngle pLocalAngles;
	extern ValveSDK::QAngle velocity;
	extern ValveSDK::QAngle AAA;
	extern ValveSDK::QAngle strafeang;
	extern 	ValveSDK::CBaseEntity *GlobalpLocal;
	extern float OldSimulationTime[65];
	extern bool strafing;
	extern int missedshots;
	extern int missedticks;
	extern int command_number;
	extern bool retarget;
	extern bool retargetplayer[65];
	extern int chokedticks;
	extern int maxmissedshots;
	extern int renderedticks;
	extern int predictedticks;
	extern int iSelectedPlayer;
	extern bool SelectedPlayerIgnore[65];
	extern float yAAA;
	extern float xAAA;
	extern int command;
	extern int targ;
	extern bool aiming;
	extern bool xSwitch;
	extern bool bSendPacket;
}
typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;

// intp is an integer that can accomodate a pointer
// (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)
typedef intptr_t				intp;
typedef uintptr_t				uintp;

inline float BitsToFloat(uint32 i)
{
	union Convertor_t
	{
		float f;
		unsigned long ul;
	}tmp;
	tmp.ul = i;
	return tmp.f;
}
#define FLOAT32_NAN_BITS     (uint32)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define VEC_T_NAN FLOAT32_NAN

#define DECL_ALIGN(x)			__declspec( align( x ) )

#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)

namespace ValveSDK
{
	class model_t;
	struct mstudiobbox_t;
	struct mstudiohitboxset_t;
	struct mstudiobone_t;
	struct studiohdr_t;
	struct DrawModelState_t;
	struct ModelRenderInfo_t;
	struct surfacephysicsparams_t;
	struct surfaceaudioparams_t;
	struct surfacesoundnames_t;
	struct surfacegameprops_t;
	struct surfacedata_t;
	class CEntityList;
	class CGlobalVarsBase;
	class IGameMovement;
	class CGlowObjectManager;
	class CHLClient;
	class CUserCmd;
	class CInput;
	class IInputSystem;
	class CMoveHelper;
	class IPrediction;
	class IDebugOverlay;
	class IEngineClient;
	class IEngineTrace;
	struct FireBulletData;
	class IGameEvent;
	class IGameEventListner2;
	class IGameEventManager2;
	class KeyValues;
	class IMaterial;
	class IModelInfo;
	class IModelRender;
	class IRenderView;
	class IPanel;
	class ISurface;
	class CRenderSurface;
	class IMultiplayerPhysics;
	class IBreakableWithPropData;
	class IPhysicsSurfaceProps;
	class IMaterialSystem;
	class CHudTexture;
	class CWeaponData;
	class CBaseCombatWeapon;
	class CBaseEntity;
	class PlayerData;
	class CTools;
	class IViewRender;
	class CBaseViewModel;
	class CGlowObjectManager;
	class ICVar;
	class SpoofedConvar;
}

extern ValveSDK::CEntityList* g_pEntityList;
extern ValveSDK::CGlobalVarsBase* g_pGlobalVarsBase;
extern ValveSDK::IGameMovement* g_pGameMovement;
extern ValveSDK::CGlowObjectManager* g_pGlowObjectManager;
extern ValveSDK::CHLClient* g_pClient;
extern ValveSDK::CInput* g_pInput;
extern ValveSDK::CMoveHelper* g_pMoveHelper;
extern ValveSDK::IPrediction* g_pPrediction;
extern ValveSDK::IDebugOverlay* g_pDebugOverlay;
extern ValveSDK::IEngineClient* g_pEngine;
extern ValveSDK::IEngineTrace* g_pEngineTrace;
extern ValveSDK::IGameEventManager2* g_pGameEventManager;
extern ValveSDK::IModelInfo* g_pModelInfo;
extern ValveSDK::IModelRender* g_pModelRender;
extern ValveSDK::IRenderView* g_pRenderView;
extern ValveSDK::ICVar* g_pICvar;
extern ValveSDK::IMaterialSystem* g_pMaterialSystem;
extern ValveSDK::IPhysicsSurfaceProps* g_pPhysSurface;
extern ValveSDK::IPanel* g_pPanel;
extern ValveSDK::ISurface* g_pSurface;
extern ValveSDK::CRenderSurface* g_pRenderSurface;
extern ValveSDK::CTools* g_pTools;
extern ValveSDK::IViewRender* g_pViewRender;
extern ValveSDK::CGlowObjectManager*	m_pGlowManager;
extern ValveSDK::SpoofedConvar* g_pSpoofConvar;
extern ValveSDK::IInputSystem* g_pIInput;
template< typename Function > Function call_vfunc(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}

namespace ValveSDK
{
	struct matrix3x4_t
	{
		matrix3x4_t() {}
		matrix3x4_t(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23)
		{
			m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
			m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
			m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
		}

		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
		{
			m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
			m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
			m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
		}

		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
		{
			Init(xAxis, yAxis, zAxis, vecOrigin);
		}

		inline void SetOrigin(Vector const & p)
		{
			m_flMatVal[0][3] = p.x;
			m_flMatVal[1][3] = p.y;
			m_flMatVal[2][3] = p.z;
		}

		inline void Invalidate(void)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m_flMatVal[i][j] = VEC_T_NAN;
				}
			}
		}

		float *operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
		const float *operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
		float *Base() { return &m_flMatVal[0][0]; }
		const float *Base() const { return &m_flMatVal[0][0]; }

		float m_flMatVal[3][4];
	};

	class ALIGN16 matrix3x4a_t : public matrix3x4_t
	{
	public:
		/*
		matrix3x4a_t() { if (((size_t)Base()) % 16 != 0) { Error( "matrix3x4a_t missaligned" ); } }
		*/
		matrix3x4a_t& operator=(const matrix3x4_t& src) { memcpy(Base(), src.Base(), sizeof(float) * 3 * 4); return *this; };
	};
	struct mstudiobbox_t
	{
		int				bone;				// 0x0
		int				group;				// 0x4
		Vector	bbmin;				// 0x8
		Vector	bbmax;				// 0x14
		int				szhitboxnameindex;	// 0x18
		PAD(0x8);							// 0x1C	
		char* GetHitboxName(void)
		{
			if (szhitboxnameindex == 0)
				return "";

			return ((char*)this) + szhitboxnameindex;
		} // 0x28 
		PAD(0x18);

	};
	struct mstudiohitboxset_t
	{
		int						sznameindex;
		inline char* const		GetName(void) const { return ((char*)this) + sznameindex; }
		int						numhitboxes;
		int						hitboxindex;
		inline mstudiobbox_t*	pHitbox(int i) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
	};
	struct mstudiobone_t
	{
		int					sznameindex;
		inline char * const GetName(void) const { return ((char *)this) + sznameindex; }
		int		 			parent;
		int					bonecontroller[6];

		Vector				pos;
		float				quat[4];
		Vector				rot;
		Vector				posscale;
		Vector				rotscale;

		matrix3x4			poseToBone;
		float				qAlignment[4];
		int					flags;
		int					proctype;
		int					procindex;		// procedural rule
		mutable int			physicsbone;	// index into physically simulated bone
		inline void *		GetProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((BYTE *)this) + procindex); };
		int					surfacepropidx;	// index into string tablefor property name
		inline char * const GetSurfaceProps(void) const { return ((char *)this) + surfacepropidx; }
		int					contents;		// See BSPFlags.h for the contents flags

		int					unused[8];		// remove as appropriate
	};

	class ConVar
	{
	public:
		void InternalSetString(const char *str)
		{
			typedef void(__thiscall* SetStringFn)(void*, const char *);
			CallVirtual< SetStringFn >(this, 17)(this, str);
		}
		char* GetName()
		{
			typedef char*(__thiscall* SetStringFn)(void*);
			return CallVirtual< SetStringFn >(this, 5)(this);
		}
		void SetValue(const char* value)
		{
			typedef void(__thiscall* SetStringFn)(void*, const char*);
			return  CallVirtual<SetStringFn>(this, 14)(this, value);
		}
		void SetValue(int value)
		{
			typedef void(__thiscall* SetStringFn)(void*, int);
			return CallVirtual<SetStringFn>(this, 16)(this, value);
		}
		char pad_0x0000[0x4]; //0x0000
		ConVar* pNext; //0x0004 
		__int32 bRegistered; //0x0008 
		char* pszName; //0x000C 
		char* pszHelpString; //0x0010 
		__int32 nFlags; //0x0014 
		char pad_0x0018[0x4]; //0x0018
		ConVar* pParent; //0x001C 
		char* pszDefaultValue; //0x0020 
		char* strString; //0x0024 
		__int32 StringLength; //0x0028 
		float fValue; //0x002C 
		__int32 nValue; //0x0030 
		__int32 bHasMin; //0x0034 
		float fMinVal; //0x0038 
		__int32 bHasMax; //0x003C 
		float fMaxVal; //0x0040 
		void* fnChangeCallback; //0x0044 

	};//Size=0x0048

	typedef void(*FnChangeCallback_t)(ConVar *var, const char *pOldValue, float flOldValue);
	class ICVar
	{
	public:
		ConVar	*FindVar(const char *var_name)
		{
			typedef ConVar*(__thiscall* FindVarFn)(void*, const char *);
			return CallVirtual<FindVarFn>(this, 15)(this, var_name);
		}
		virtual void			RegisterConCommand(ConVar *pCommandBase) = 0;
		virtual void			UnregisterConCommand(ConVar *pCommandBase) = 0;
		// Value set
		virtual void SetValue(const char *pValue) = 0;
		virtual void SetValue(float flValue) = 0;
		virtual void SetValue(int nValue) = 0;
		// Return name of command
		virtual const char *GetName(void) const = 0;

		// Accessors.. not as efficient as using GetState()/GetInfo()
		// if you call these methods multiple times on the same IConVar
		virtual bool IsFlagSet(int nFlag) const = 0;
	};

	class CViewSetup
	{
	public:
		int			x, x_old;
		int			y, y_old;
		int			width, width_old;
		int			height, height_old;
		bool		m_bOrtho;
		float		m_OrthoLeft;
		float		m_OrthoTop;
		float		m_OrthoRight;
		float		m_OrthoBottom;
		bool		m_bCustomViewMatrix;
		matrix3x4_t	m_matCustomViewMatrix;
		char		pad_0x68[0x48];
		float		fov;
		float		fovViewmodel;
		Vector		origin;
		QAngle		angles;
		float		zNear;
		float		zFar;
		float		zNearViewmodel;
		float		zFarViewmodel;
		float		m_flAspectRatio;
		float		m_flNearBlurDepth;
		float		m_flNearFocusDepth;
		float		m_flFarFocusDepth;
		float		m_flFarBlurDepth;
		float		m_flNearBlurRadius;
		float		m_flFarBlurRadius;
		int			m_nDoFQuality;
		int			m_nMotionBlurMode;
		float		m_flShutterTime;
		Vector		m_vShutterOpenPosition;
		QAngle		m_shutterOpenAngles;
		Vector		m_vShutterClosePosition;
		QAngle		m_shutterCloseAngles;
		float		m_flOffCenterTop;
		float		m_flOffCenterBottom;
		float		m_flOffCenterLeft;
		float		m_flOffCenterRight;
		int			m_EdgeBlur;
	};
	struct studiohdr_t
	{
		int					id;
		int					version;
		int					checksum;
		char				name[64];
		int					length;
		Vector				eyeposition;
		Vector				illumposition;
		Vector				hull_min;
		Vector				hull_max;
		Vector				view_bbmin;
		Vector				view_bbmax;
		int					flags;
		int					numbones;
		int					boneindex;

		inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((BYTE *)this) + boneindex) + i; };

		int					numbonecontrollers;
		int					bonecontrollerindex;
		int					numhitboxsets;
		int					hitboxsetindex;

		mstudiohitboxset_t* pHitboxSet(int i) const
		{
			return (mstudiohitboxset_t*)(((BYTE*)this) + hitboxsetindex) + i;
		}

		inline mstudiobbox_t* pHitbox(int i, int set) const
		{
			mstudiohitboxset_t const* s = pHitboxSet(set);

			if (!s)
				return NULL;

			return s->pHitbox(i);
		}

		inline int GetHitboxCount(int set) const
		{
			mstudiohitboxset_t const* s = pHitboxSet(set);

			if (!s)
				return 0;

			return s->numhitboxes;
		}

		int					numlocalanim;
		int					localanimindex;
		int					numlocalseq;
		int					localseqindex;
		mutable int			activitylistversion;
		mutable int			eventsindexed;
		int					numtextures;
		int					textureindex;
		int					numcdtextures;
		int					cdtextureindex;
		int					numskinref;
		int					numskinfamilies;
		int					skinindex;
		int					numbodyparts;
		int					bodypartindex;
		int					numlocalattachments;
		int					localattachmentindex;
		int					numlocalnodes;
		int					localnodeindex;
		int					localnodenameindex;
		int					numflexdesc;
		int					flexdescindex;
		int					numflexcontrollers;
		int					flexcontrollerindex;
		int					numflexrules;
		int					flexruleindex;
		int					numikchains;
		int					ikchainindex;
		int					nummouths;
		int					mouthindex;
		int					numlocalposeparameters;
		int					localposeparamindex;
		int					surfacepropindex;
		int					keyvalueindex;
		int					keyvaluesize;
		int					numlocalikautoplaylocks;
		int					localikautoplaylockindex;
		float				mass;
		int					contents;
		int					numincludemodels;
		int					includemodelindex;
		mutable void		*virtualModel;
		int					szanimblocknameindex;
		int					numanimblocks;
		int					animblockindex;
		mutable void		*animblockModel;
		int					bonetablebynameindex;
		void				*pVertexBase;
		void				*pIndexBase;
		BYTE				constdirectionallightdot;
		BYTE				rootLOD;
		BYTE				numAllowedRootLODs;
		PAD(0x5);
		int					numflexcontrollerui;
		int					flexcontrolleruiindex;
		float				flVertAnimFixedPointScale;
		PAD(0x4);
		int					studiohdr2index;
		PAD(0x4);
	};
	struct DrawModelState_t
	{
		studiohdr_t*		m_pStudioHdr;
		unsigned long		m_pStudioHWData;
		CBaseEntity*		m_pRenderable;
		const matrix3x4*	m_pModelToWorld;
		unsigned long		m_decals;
		int					m_drawFlags;
		int					m_lod;
	};
	struct ModelRenderInfo_t
	{
		Vector				origin;
		QAngle				angles;
		CBaseEntity*		pRenderable;
		const model_t*		pModel;
		const matrix3x4*	pModelToWorld;
		const matrix3x4*	pLightingOffset;
		const Vector*		pLightingOrigin;
		int					flags;
		int					entity_index;
		int					skin;
		int					body;
		int					hitboxset;
		unsigned short		instance;
		ModelRenderInfo_t(void)
		{
			pModelToWorld = NULL;
			pLightingOffset = NULL;
			pLightingOrigin = NULL;
		}
	};
	struct GlowObject_t {
		CBaseEntity*	m_pEntity;	// 0
		Vector		m_vGlowColor;	// 4
		float		m_flGlowAlpha;	// 16
		unsigned char   junk[16];	// 20
		bool		m_bShouldGlow;	// 36
		bool		m_bUnknown;	// 37
		bool		m_bFullBloomRender; // 38
		unsigned char   junk2[13];	// 39
	}; // total size should be 52
	struct surfacephysicsparams_t
	{
		float   friction;
		float   elasticity; // collision elasticity - used to compute coefficient of restitution
		float   density;        // physical density (in kg / m^3)
		float   thickness;      // material thickness if not solid (sheet materials) in inches
		float   dampening;
	};
	struct surfaceaudioparams_t
	{
		float   reflectivity;                   // like elasticity, but how much sound should be reflected by this surface
		float   hardnessFactor;                 // like elasticity, but only affects impact sound choices
		float   roughnessFactor;                // like friction, but only affects scrape sound choices
		float   roughThreshold;                 // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
		float   hardThreshold;                  // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
		float   hardVelocityThreshold;  // collision velocity > this causes "hard" impacts, < this causes "soft" impacts       
	};
	struct surfacesoundnames_t
	{
		unsigned short  stepleft;
		unsigned short  stepright;
		unsigned short  impactSoft;
		unsigned short  impactHard;
		unsigned short  scrapeSmooth;
		unsigned short  scrapeRough;
		unsigned short  bulletImpact;
		unsigned short  rolling;
		unsigned short  breakSound;
		unsigned short  strainSound;
	};
	struct surfacegameprops_t
	{
	public:
		float   maxSpeedFactor;
		float   jumpFactor;
		PAD(0x4);
		float   flPenetrationModifier;
		float   flDamageModifier;
		unsigned short  material;
		PAD(0x3);

	};
	struct surfacedata_t
	{
		surfacephysicsparams_t	physics;
		surfaceaudioparams_t	audio;
		surfacesoundnames_t		sounds;
		surfacegameprops_t		game;
	};
	
	class CEntityList
	{
	public:
		CBaseEntity* GetBaseEntity( int iIndex )
		{
			VirtualFn( CBaseEntity* )( PVOID, int );
			return CallVirtual< OriginalFn >( this, 3 )( this, iIndex );
		}
		CBaseEntity* GetBaseEntityFromHandle( EHANDLE hEntity )
		{
			VirtualFn( CBaseEntity* )( PVOID, EHANDLE );
			return CallVirtual< OriginalFn >( this, 4 )( this, hEntity );
		}
		int GetHighestEntityIndex( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 6 )( this );
		}
	};
	class CGlobalVarsBase
	{
	public:
		float	realtime;
		int		framecount;
		float	absoluteframetime;
		float	unknown;
		float	curtime;
		float	frametime;
		int		maxclients;
		int		tickcount;
		float	interval_per_tick;
		float	interpolation_amount;
	};
	class IGameMovement
	{
	public:
		void ProcessMovement( CBaseEntity* pBaseEntity, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, PVOID );
			CallVirtual< OriginalFn >( this, 1 )( this, pBaseEntity, pMoveData );
		}
	};
	class CHLClient
	{
	public:
		ClientClass* GetFirstClass( void )
		{
			VirtualFn( ClientClass* )( PVOID );
			return CallVirtual< OriginalFn >( this, 8 )( this );
		}
		void RenderView( const CViewSetup &view, int nClearFlags, int whatToDraw )
		{
			VirtualFn( void )( PVOID, const CViewSetup&, int, int );
			CallVirtual< OriginalFn >( this, 27 )( this, view, nClearFlags, whatToDraw );
		}
		bool GetPlayerView( CViewSetup &playerView )
		{
			VirtualFn( bool )( PVOID, CViewSetup& );
			return CallVirtual< OriginalFn >( this, 59 )( this, playerView );
		}
	};
	class CUserCmd
	{
	public:
		PAD( 0x4 );
		int				command_number;
		int				tick_count;
		QAngle			viewangles;
		Vector			aimdirection;
		float			forwardmove;
		float			sidemove;
		float			upmove;
		int				buttons;
		BYTE			impulse;
		int				weaponselect;
		int				weaponsubtype;
		int				random_seed;
		short			mousedx;
		short			mousedy;
		bool			hasbeenpredicted;
		QAngle			headangles;
		Vector			headoffset;

	public:
		CRC32_t GetChecksum( void ) const
		{
			CRC32_t crc;
			CRC32_Init( &crc );
			CRC32_ProcessBuffer( &crc, &command_number, sizeof( command_number ) );
			CRC32_ProcessBuffer( &crc, &tick_count, sizeof( tick_count ) );
			CRC32_ProcessBuffer( &crc, &viewangles, sizeof( viewangles ) );
			CRC32_ProcessBuffer( &crc, &aimdirection, sizeof( aimdirection ) ); //new
			CRC32_ProcessBuffer( &crc, &forwardmove, sizeof( forwardmove ) );
			CRC32_ProcessBuffer( &crc, &sidemove, sizeof( sidemove ) );
			CRC32_ProcessBuffer( &crc, &upmove, sizeof( upmove ) );
			CRC32_ProcessBuffer( &crc, &buttons, sizeof( buttons ) );
			CRC32_ProcessBuffer( &crc, &impulse, sizeof( impulse ) );
			CRC32_ProcessBuffer( &crc, &weaponselect, sizeof( weaponselect ) );
			CRC32_ProcessBuffer( &crc, &weaponsubtype, sizeof( weaponsubtype ) );
			CRC32_ProcessBuffer( &crc, &random_seed, sizeof( random_seed ) );
			CRC32_ProcessBuffer( &crc, &mousedx, sizeof( mousedx ) );
			CRC32_ProcessBuffer( &crc, &mousedy, sizeof( mousedy ) );
			CRC32_Final( &crc );
			return crc;
		}
	};
	class IInputSystem
	{
	public:
		// Attach, detach input system from a particular window
		// This window should be the root window for the application
		// Only 1 window should be attached at any given time.
		virtual void AttachToWindow(void* hWnd) = 0;
		virtual void DetachFromWindow() = 0;

		// Enables/disables input. PollInputState will not update current 
		// button/analog states when it is called if the system is disabled.
		virtual void EnableInput(bool bEnable) = 0;
	};


	class CInput
	{
	public:
		class CVerifiedUserCmd
		{
		public:
			CUserCmd	m_cmd;
			CRC32_t		m_crc;
		};
	public:
		void*               pvftable;                     //0x00
		bool                m_fTrackIRAvailable;          //0x04
		bool                m_fMouseInitialized;          //0x05
		bool                m_fMouseActive;               //0x06
		bool                m_fJoystickAdvancedInit;      //0x07
		char                pad_0x08[0x2C];               //0x08
		void*               m_pKeys;                      //0x34
		char                pad_0x38[0x64];               //0x38
		bool                m_fCameraInterceptingMouse;   //0x9C
		bool                m_fCameraInThirdPerson;       //0x9D
		bool                m_fCameraMovingWithMouse;     //0x9E
		Vector              m_vecCameraOffset;            //0xA0
		bool                m_fCameraDistanceMove;        //0xAC
		int                 m_nCameraOldX;                //0xB0
		int                 m_nCameraOldY;                //0xB4
		int                 m_nCameraX;                   //0xB8
		int                 m_nCameraY;                   //0xBC
		bool                m_CameraIsOrthographic;       //0xC0
		QAngle              m_angPreviousViewAngles;      //0xC4
		QAngle              m_angPreviousViewAnglesTilt;  //0xD0
		float               m_flLastForwardMove;          //0xDC
		int                 m_nClearInputState;           //0xE0
		char                pad_0xE4[0x8];                //0xE4
		CUserCmd*           m_pCommands;                  //0xEC
		CVerifiedUserCmd*   m_pVerifiedCommands;          //0xF0
		CUserCmd* GetUserCmd( int slot, int sequence_number )
		{
			VirtualFn( CUserCmd* )( PVOID, int, int );
			return CallVirtual< OriginalFn >( this, 8 )( this, slot, sequence_number );
		}
	};

	class CMoveHelper
	{
	public:
		void SetHost(CBaseEntity* pPlayer)
		{
			VirtualFn(void)(PVOID, CBaseEntity*);
			CallVirtual< OriginalFn >(this, 1)(this, pPlayer);
		}
	};

	class IPrediction
	{
	public:
		bool InPrediction( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 14 )( this );
		}
		void RunCommand( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pMoveHelper )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID );
			CallVirtual< OriginalFn >( this, 19 )( this, pBaseEntity, pCmd, pMoveHelper );
		}
		void SetupMove( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pEmpty, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID, PVOID );
			CallVirtual< OriginalFn >( this, 20 )( this, pBaseEntity, pCmd, pEmpty, pMoveData );
		}
		void FinishMove( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID );
			CallVirtual< OriginalFn >( this, 21 )( this, pBaseEntity, pCmd, pMoveData );
		}
	};
	class IDebugOverlay
	{
	public:
		int ScreenPoint( const Vector& vecOrigin, Vector& vecScreen )
		{
			VirtualFn( int )( PVOID, const Vector&, Vector& );
			return CallVirtual< OriginalFn >( this, 13 )( this, vecOrigin, vecScreen );
		}
		void AddSweptBoxOverlay( const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration )
		{
			VirtualFn( void )( PVOID, const Vector&, const Vector&, const Vector&, const Vector&, const QAngle&, int, int, int, int, float );
			CallVirtual< OriginalFn >( this, 9 )( this, start, end, mins, max, angles, r, g, b, a, flDuration );
		}
		void AddBoxOverlay2(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, const Color& faceColor, const Color& edgeColor, float duration)
		{
			VirtualFn(void)(PVOID, const Vector& , const Vector& , const Vector& , QAngle const& , const Color& , const Color& , float);
			CallVirtual< OriginalFn >(this, 21)(this, origin, mins, max, orientation, faceColor, edgeColor, duration);
		}
		void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float flDuration) 
		{
			VirtualFn(void)(PVOID, const Vector&, const Vector& , int, int, int, int, bool, float);
			CallVirtual<OriginalFn>(this, 4)(this, origin, dest, r, g, b, a, noDepthTest, flDuration);
		}
	};
	class IEngineClient
	{
	public:
		typedef struct
		{
			unsigned __int64            unknown;
			unsigned __int64            xuid;
			char                        name[32];

			char	 unknown01[96];

			int                         userID;
			char                        guid[32 + 1];
			__int32                     friendsID;
			char                        friendsName[32];
			bool                        fakeplayer;
			bool                        ishltv;
			unsigned long				customFiles[4];
			unsigned char				filesDownloaded;
			char pad[304];
		} player_info_t;
	public:
		bool IsTakingScreenshot( void ) {
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 92 )( this );
		}
		void GetScreenSize( int& iWidth, int& iHeight )
		{
			VirtualFn( void )( PVOID, int&, int& );
			CallVirtual< OriginalFn >( this, 5 )( this, iWidth, iHeight );
		}
		void GetScreenSize( int* piScreenSize )
		{
			GetScreenSize( piScreenSize[ 0 ], piScreenSize[ 1 ] );
		}
		void ClientCmd( const char* pszCmd, ... )
		{
			VirtualFn( void )( PVOID, const char* );
			CallVirtual< OriginalFn >( this, 7 )( this, pszCmd );
		}
		bool GetPlayerInfo( int iIndex, player_info_t* pInfo )
		{
			VirtualFn( bool )( PVOID, int, player_info_t* );
			return CallVirtual< OriginalFn >( this, 8 )( this, iIndex, pInfo );
		}
		int GetPlayerForUserID( int iUserId )
		{
			VirtualFn( int )( PVOID, int );
			return CallVirtual< OriginalFn >( this, 9 )( this, iUserId );
		}
		int GetLocalPlayer( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 12 )( this );
		}
		float GetLastTimeStamp( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 14 )( this );
		}
		void GetViewAngles( QAngle& qViewAngles )
		{
			VirtualFn( void )( PVOID, QAngle& );
			CallVirtual< OriginalFn >( this, 18 )( this, qViewAngles );
		}
		void SetViewAngles( QAngle& qViewAngles )
		{
			VirtualFn( void )( PVOID, QAngle& );
			CallVirtual< OriginalFn >( this, 19 )( this, qViewAngles );
		}
		int GetMaxClients( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 20 )( this );
		}
		bool IsIngame( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 26 )( this );
		}
		bool IsConnected( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 27 )( this );
		}
		std::string GetGameDirectory( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 36 )( this ) );
		}
		void ExecuteClientCmd( const char* pszCmd )
		{
			VirtualFn( void )( PVOID, const char* );
			CallVirtual< OriginalFn >( this, 108 )( this, pszCmd );
		}
	};
	class IEngineTrace
	{
	public:
		struct cplane_t
		{
			Vector normal;
			float dist;
			BYTE type;
			BYTE signBits;
			BYTE pad[ 2 ];
		};
		struct csurface_t
		{
			const char*		name;
			short			surfaceProps;
			unsigned short	flags;
		};
		struct Ray_t
		{
			VectorAligned  m_Start;	// starting point, centered within the extents
			VectorAligned  m_Delta;	// direction + length of the ray
			VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
			VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
			const matrix3x4 *m_pWorldAxisTransform;
			bool	m_IsRay;	// are the extents zero?
			bool	m_IsSwept;	// is delta != 0?

			Ray_t( ) : m_pWorldAxisTransform( NULL )	{}

			void Init( Vector const& start, Vector const& end )
			{
				Assert( &end );
				VectorSubtract( end, start, m_Delta );

				m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );

				VectorClear( m_Extents );
				m_pWorldAxisTransform = NULL;
				m_IsRay = true;

				// Offset m_Start to be in the center of the box...
				VectorClear( m_StartOffset );
				VectorCopy( start, m_Start );
			}

			void Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs )
			{
				Assert( &end );
				VectorSubtract( end, start, m_Delta );

				m_pWorldAxisTransform = NULL;
				m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );

				VectorSubtract( maxs, mins, m_Extents );
				m_Extents *= 0.5f;
				m_IsRay = ( m_Extents.LengthSqr( ) < 1e-6 );

				// Offset m_Start to be in the center of the box...
				VectorAdd( mins, maxs, m_StartOffset );
				m_StartOffset *= 0.5f;
				VectorAdd( start, m_StartOffset, m_Start );
				m_StartOffset *= -1.0f;
			}

			// compute inverse delta
			Vector InvDelta( ) const
			{
				Vector vecInvDelta;
				for( int iAxis = 0; iAxis < 3; ++iAxis )
				{
					if( m_Delta[ iAxis ] != 0.0f )
					{
						vecInvDelta[ iAxis ] = 1.0f / m_Delta[ iAxis ];
					}
					else
					{
						vecInvDelta[ iAxis ] = FLT_MAX;
					}
				}
				return vecInvDelta;
			}

		private:
		};
		struct trace_t
		{
			Vector	start;
			Vector	endpos;
			cplane_t	plane;
			float		fraction;
			int			contents;
			WORD		dispFlags;
			bool		allSolid;
			bool		startSolid;
			float		fractionLeftSolid;
			csurface_t	surface;
			int			hitgroup;
			short		physicsBone;
			WORD		m_nWorldSurfaceIndex;
			CBaseEntity* m_pEnt;
			int			hitbox;
		};
		class ITraceFilter
		{
		public:
			virtual bool ShouldHitEntity( PVOID pEntity, int contentsMask ) = 0;
			virtual TraceType_t	GetTraceType( ) const = 0;
		};
		class CTraceFilterSkipTwoEntities : public ITraceFilter {
		public:
			CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2) {
				passentity1 = pPassEnt1;
				passentity2 = pPassEnt2;
			}

			virtual bool ShouldHitEntity(void *pEntityHandle, int contentsMask) {
				return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
			}

			virtual TraceType_t    GetTraceType() const {
				return TRACE_EVERYTHING;
			}

			void *passentity1;
			void *passentity2;
		};
		class CTraceFilter : public ITraceFilter
		{
		public:
			CTraceFilter( PVOID pEntToSkip = NULL )
			{
				pSkip = pEntToSkip;
			}
			bool ShouldHitEntity( PVOID pEntityHandle, int contentsMask )
			{
				return !( pEntityHandle == pSkip );
			}
			virtual TraceType_t GetTraceType( ) const
			{
				return TRACE_EVERYTHING;
			}
			void* pSkip;
		};

	public:
		int GetPointContents( const Vector& vecAbsPosition, UINT nMask, CBaseEntity** ppEntity = NULL )
		{
			VirtualFn( int )( PVOID, const Vector&, UINT, CBaseEntity** );
			return CallVirtual< OriginalFn >( this, 0 )( this, vecAbsPosition, nMask, ppEntity );
		}
		//void TraceRay( const Ray_t& ray, unsigned int nMask, ITraceFilter* pTraceFilter, trace_t* pTrace )
		//{
		//	VirtualFn( void )( PVOID, const Ray_t&, unsigned int, ITraceFilter*, trace_t* );
		//	CallVirtual< OriginalFn >( this, 5 )( this, ray, nMask, pTraceFilter, pTrace );
		//}
		void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
		{
			typedef void(__thiscall* fnTraceRay)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
			call_vfunc<fnTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
		}
		void ClipRayToEntity( const Ray_t& ray, unsigned int nMask, CBaseEntity* pEntity, trace_t* pTrace )
		{
			VirtualFn( void )( PVOID, const Ray_t&, unsigned int, CBaseEntity*, trace_t* );
			CallVirtual< OriginalFn >( this, 3 )( this, ray, nMask, pEntity, pTrace );
		}

	};


	class IGameEvent
	{
	public:
		std::string GetName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 1 )( this ) );
		}
		bool GetBool( std::string strKeyName, bool bDefaultValue = false )
		{
			VirtualFn( bool )( PVOID, const char*, bool );
			const char* c = strKeyName.c_str( );
			return CallVirtual< OriginalFn >( this, 5 )( this, c, bDefaultValue );
		}
		int GetInt( std::string strKeyName, int iDefaultValue = 0 )
		{
			VirtualFn( int )( PVOID, const char*, int );
			const char* c = strKeyName.c_str( );
			return CallVirtual< OriginalFn >( this, 6 )( this, c, iDefaultValue );
		}
		std::string GetString( std::string strKeyName, int iDefaultValue = 0 )
		{
			VirtualFn( const char* )( PVOID, const char*, int );
			const char* c = strKeyName.c_str( );
			return std::string( CallVirtual< OriginalFn >( this, 9 )( this, c, iDefaultValue ) );
		}
		void SetString(std::string strKeyName, std::string strValue)
		{
			VirtualFn( void )( PVOID, const char*, const char* );
			const char* c = strKeyName.c_str( );
			const char* c2 = strValue.c_str( );
			CallVirtual< OriginalFn >( this, 15 )( this, c, c2 );

		}
	};
	class IGameEventListener2
	{
	public:
		virtual ~IGameEventListener2( void ){}
		virtual void FireGameEvent( IGameEvent* pGameEvent ) = 0;
		virtual int GetEventDebugID( void )
		{
			return m_nDebugId;
		}

	public:
		int	m_nDebugId;
	};
	class IGameEventManager2
	{
	public:
		bool AddListener( IGameEventListener2* pListener, std::string strName, bool bServerSide )
		{
			VirtualFn( bool )( PVOID, IGameEventListener2*, const char*, bool );
			const char* c = strName.c_str( );
			return CallVirtual< OriginalFn >( this, 3 )( this, pListener, c, bServerSide );
		}
		void RemoveListener(IGameEventListener2* pListener)
		{
			VirtualFn(void)(PVOID, IGameEventListener2*);
			CallVirtual< OriginalFn >(this, 5)(this, pListener);
		}
		bool FireEventClientSide( IGameEvent* pGameEvent )
		{
			VirtualFn( bool )( PVOID, IGameEvent* );
			return CallVirtual< OriginalFn >( this, 8 )( this, pGameEvent );
		}
	};
	class IMaterial
	{
	public:
		std::string GetName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 0 )( this ) );
		}
		std::string GetTextureGroupName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 1 )( this ) );
		}
		void IncrementReferenceCount( void )
		{
			VirtualFn( void )( PVOID );
			CallVirtual< OriginalFn >( this, 12 )( this );
		}
		void AlphaModulate( float alpha )
		{
			VirtualFn( void )( PVOID, float );
			CallVirtual< OriginalFn >( this, 27 )( this, alpha );
		}
		void ColorModulate( float r, float g, float b )
		{
			VirtualFn( void )( PVOID, float, float, float );
			CallVirtual< OriginalFn >( this, 28 )( this, r, g, b );
		}
		void SetMaterialVarFlag( MaterialVarFlags_t flag, bool on )
		{
			VirtualFn( void )( PVOID, MaterialVarFlags_t, bool );
			CallVirtual< OriginalFn >( this, 29 )( this, flag, on );
		}
		float GetAlphaModulation()
		{
			VirtualFn(float)(PVOID);
			return CallVirtual< OriginalFn >(this, 44)(this);
		}
		void GetColorModulation(float* r, float* g, float* b)
		{
			VirtualFn(void)(PVOID, float*, float*, float*);
			CallVirtual< OriginalFn >(this, 45)(this, r, g, b);
		}
	};
	class IModelInfo
	{
	public:
		const model_t* GetModel( int iMdlIndx ) 
		{
			VirtualFn( const model_t* )( PVOID, int );
			return CallVirtual< OriginalFn >( this, 1 )( this, iMdlIndx);
		}
		int GetModelIndex( std::string strModelName )
		{
			const char* c = strModelName.c_str( );
			VirtualFn( int )( PVOID, const char* );
			return CallVirtual< OriginalFn >( this, 2 )( this, c );
		}
		std::string GetModelName( const model_t* pModel )
		{
			VirtualFn( const char* )( PVOID, const model_t* );
			return std::string( CallVirtual< OriginalFn >( this, 3 )( this, pModel ) );
		}
		void GetModelRenderBounds(const model_t *model, Vector& mins, Vector& maxs)
		{
			VirtualFn( void )( PVOID, const model_t*, Vector&, Vector& );
			CallVirtual< OriginalFn >( this, 7 )( this, model, mins, maxs );
		}
		void GetModelMaterials( const model_t* pModel, int iCount, IMaterial** ppMaterial )
		{
			VirtualFn( void )( PVOID, const model_t*, int, IMaterial** );
			CallVirtual< OriginalFn >( this, 17 )( this, pModel, iCount, ppMaterial );
		}
		studiohdr_t* GetStudioModel( const model_t* pModel )
		{
			VirtualFn( studiohdr_t* )( PVOID, const model_t* );
			return CallVirtual< OriginalFn >( this, 30 )( this, pModel );
		}
	};
	class IModelRender
	{
	public:
		void DrawModelExecute( PVOID pContext, const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld )
		{
			VirtualFn( void )( PVOID, PVOID, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4* );
			CallVirtual< OriginalFn >( this, 21 )( this, pContext, pState, pInfo, pCustomBoneToWorld );
		}
		void ForcedMaterialOverride( IMaterial *newMaterial, int nOverrideType = 0, int iUnknown = 0 )
		{
			VirtualFn( void )( PVOID, IMaterial*, int, int );
			CallVirtual< OriginalFn >( this, 1 )( this, newMaterial, nOverrideType, iUnknown );
		}
	};
	class IRenderView
	{
	public:
		void SetBlend( float blend )
		{
			VirtualFn( void )( PVOID, float );
			CallVirtual< OriginalFn >( this, 4 )( this, blend );
		}
		void SetColorModulation( float const* blend )
		{
			VirtualFn( void )( PVOID, float const* );
			CallVirtual< OriginalFn >( this, 6 )( this, blend );
		}
	};
	class IPanel
	{
	public:
		std::string GetName( unsigned int VGUIPanel )
		{
			VirtualFn( const char* )( PVOID, unsigned int );
			return std::string( CallVirtual< OriginalFn >( this, 36 )( this, VGUIPanel ) );
		}
	};
	class ISurface
	{
	public:
		void DrawSetColor( Color color )
		{
			VirtualFn( void )( PVOID, Color );
			CallVirtual< OriginalFn >( this, 14 )( this, color );
		}
		void DrawFilledRect( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 16 )( this, x0, y0, x1, y1 );
		}
		void DrawOutlinedRect( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 18 )( this, x0, y0, x1, y1 );
		}
		void DrawLine( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 19 )( this, x0, y0, x1, y1 );
		}
		void DrawSetTextFont( HFont font )
		{
			VirtualFn( void )( PVOID, HFont );
			CallVirtual< OriginalFn >( this, 23 )( this, font );
		}
		void DrawSetTextColor( Color color )
		{
			VirtualFn( void )( PVOID, Color );
			CallVirtual< OriginalFn >( this, 24 )( this, color );
		}
		void DrawSetTextPos( int x, int y )
		{
			VirtualFn( void )( PVOID, int, int );
			CallVirtual< OriginalFn >( this, 26 )( this, x, y );
		}
		void DrawPrintText( const wchar_t* pwszText, int nLenght, FontDrawType_t drawType = FONT_DRAW_DEFAULT )
		{
			VirtualFn( void )( PVOID, const wchar_t*, int, FontDrawType_t );
			CallVirtual< OriginalFn >( this, 28 )( this, pwszText, nLenght, drawType );
		}
		HFont FontCreate( void )
		{
			VirtualFn( HFont )( PVOID );
			return CallVirtual< OriginalFn >( this, 71 )( this );
		}
		bool SetFontGlyphSet( HFont font, std::string szWindowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax )
		{
			VirtualFn( bool )( PVOID, HFont, const char*, int, int, int, int, int, int, int );
			return CallVirtual< OriginalFn >( this, 72 )( this, font, szWindowsFontName.c_str( ), tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax );
		}
		bool GetTextSize( HFont font, std::string szText, int& width, int& tall )
		{
			std::wstring wszString( szText.begin( ), szText.end( ) );

			VirtualFn( bool )( PVOID, HFont, const wchar_t*, int&, int& );
			return CallVirtual< OriginalFn >( this, 79 )( this, font, wszString.c_str( ), width, tall );
		}
		void GetCursorPos( int& x, int& y )
		{
			VirtualFn( void )( PVOID, int&, int& );
			CallVirtual< OriginalFn >( this, 100 )( this, x, y );
		}
		void GetCursorPos( int* piOut )
		{
			GetCursorPos( piOut[ 0 ], piOut[ 1 ] );
		}
		void DrawOutlinedCircle( int x, int y, int radius, int segments )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 103 )( this, x, y, radius, segments );
		}
		void DrawUnicodeString( const wchar_t *pwString, FontDrawType_t drawType = FONT_DRAW_DEFAULT )
		{
			VirtualFn( void )( PVOID, const wchar_t*, FontDrawType_t );
			CallVirtual< OriginalFn >( this, 132 )( this, pwString, drawType );
		}
	};
	class CRenderSurface
	{
	private:
		class CSurfaceFont
		{
		public:
			std::string	m_strName;
			std::string m_strWindowsFontName;
			int			m_iTall;
			int			m_iWeight;
			int			m_iBlur;
			int			m_iScanlines;
			int			m_iFlags;
			int			m_iRangeMin;
			int			m_iRangeMax;
			ULONG		m_Font;
		};
		typedef struct
		{
			int x, y, w, h;
		}Corner_t;

		Corner_t					m_Corner[ 8 ];
		bool						m_bSurfaceFontsCreated;
		ISurface*					m_pSurface;
		std::vector< CSurfaceFont >	m_vSurfaceFonts;

	private:
		int TweakColor( int c1, int c2, int variation )
		{
			if( c1 == c2 )
				return c1;
			else if( c1 < c2 )
				c1 += variation;
			else
				c1 -= variation;
			return c1;
		}
		std::size_t GetSurfaceFontIndex( std::string strName )
		{
			if( strName.empty( ) )
				return -1;

			for( std::size_t i = 0; i < m_vSurfaceFonts.size( ); i++ )
				if( !m_vSurfaceFonts[ i ].m_strName.compare( strName ) )
					return i;

			return -1;
		}
	public:
		CRenderSurface( ISurface* pSurface )
		{
			m_bSurfaceFontsCreated = false;
			SetSurface( pSurface );
		}
		ULONG GetSurfaceFont( std::string strName )
		{
			std::size_t nSurfaceFont = GetSurfaceFontIndex( strName );
			if( nSurfaceFont != -1 )
				return m_vSurfaceFonts[ nSurfaceFont ].m_Font;

			return NULL;
		}
		void AddFont( std::string strName, std::string strFont, int iWidth, int iWeight, int iBlur, int iScanLines, int iFlags, int iRangeMin = 0, int iRangeMax = 0 )
		{
			if( !m_bSurfaceFontsCreated )
			{
				if( GetSurfaceFontIndex( strName ) != -1 )
					return;

				CSurfaceFont font;
				font.m_strName = strName;
				font.m_strWindowsFontName = strFont;
				font.m_iTall = iWidth;
				font.m_iWeight = iWeight;
				font.m_iBlur = iBlur;
				font.m_iScanlines = iScanLines;
				font.m_iFlags = iFlags;
				font.m_iRangeMin = iRangeMin;
				font.m_iRangeMax = iRangeMax;

				m_vSurfaceFonts.push_back( font );
			}
		}

		void RenderBones(Vector* vBones, Color color) {

			this->Line((int)vBones[0].x, (int)vBones[0].y, (int)vBones[1].x, (int)vBones[1].y, color); // head to neck
			this->Line((int)vBones[1].x, (int)vBones[1].y, (int)vBones[2].x, (int)vBones[2].y,color); // neck to lower neck
			this->Line((int)vBones[2].x, (int)vBones[2].y, (int)vBones[7].x, (int)vBones[7].y,color); // lower neck to upper chest

			this->Line((int)vBones[7].x, (int)vBones[7].y, (int)vBones[6].x, (int)vBones[6].y,color); // upper chest to chest
			this->Line((int)vBones[6].x, (int)vBones[6].y, (int)vBones[18].x, (int)vBones[18].y,color);
			this->Line((int)vBones[6].x, (int)vBones[6].y, (int)vBones[16].x, (int)vBones[16].y, color);

			this->Line((int)vBones[16].x, (int)vBones[16].y, (int)vBones[17].x, (int)vBones[17].y, color);
			this->Line((int)vBones[17].x, (int)vBones[17].y, (int)vBones[14].x, (int)vBones[14].y, color);
			this->Line((int)vBones[18].x, (int)vBones[18].y, (int)vBones[15].x, (int)vBones[15].y, color);

			this->Line((int)vBones[6].x, (int)vBones[6].y, (int)vBones[5].x, (int)vBones[5].y,color);
			this->Line((int)vBones[5].x, (int)vBones[5].y, (int)vBones[4].x, (int)vBones[4].y,color);
			this->Line((int)vBones[4].x, (int)vBones[4].y, (int)vBones[3].x, (int)vBones[3].y,color);

			this->Line((int)vBones[3].x, (int)vBones[3].y, (int)vBones[9].x, (int)vBones[9].y,color);
			this->Line((int)vBones[3].x, (int)vBones[3].y, (int)vBones[8].x, (int)vBones[8].y,color);

			this->Line((int)vBones[9].x, (int)vBones[9].y, (int)vBones[11].x, (int)vBones[11].y,color);
			this->Line((int)vBones[11].x, (int)vBones[11].y, (int)vBones[13].x, (int)vBones[13].y,color);

			this->Line((int)vBones[8].x, (int)vBones[8].y, (int)vBones[10].x, (int)vBones[10].y,color);
			this->Line((int)vBones[10].x, (int)vBones[10].y, (int)vBones[12].x, (int)vBones[12].y,color);
		}

		void BorderBox( int x, int y, int w, int h, int thickness, Color color )
		{
			this->Rect( x, y, w, thickness, color );
			this->Rect( x, y, thickness, h, color );
			this->Rect( x + w, y, thickness, h, color );
			this->Rect( x, y + h, w + thickness, thickness, color );
		}
		void BorderBoxOutlined( int x, int y, int w, int h, int thickness, Color color, Color outlined )
		{
			this->BorderBox( x, y, w, h, thickness, color );
			this->BorderBox( x - 1, y - 1, w + 2, h + 2, 1, outlined );
			this->BorderBox( x + 1, y + 1, w - 2, h - 2, 1, outlined );
		}
		void BorderBoxOutlinedText(int x, int y, int w, int h, int thickness, Color color, Color outlined, const char* meme)
		{
			//this->BorderBox(x, y, w, h, 1, color);
			//this->BorderBox(x - 1, y - 1, w + 2, h + 2, 1, outlined);
			//this->BorderBox(x + 1, y + 1, w - 2, h - 2, 1, outlined);
			//this->String(x + 5, y, outlined, "FONT_TABNOTE", meme);


			RECT txtSize = this->GetTextSizeREC("FONT_MENU", meme);
			this->Rect(x + 2, y + 2, w - 4, h - 4, Color(outlined.r(), outlined.g(), outlined.b(), 15));
			this->String(x + 15, y - (txtSize.bottom / 2), outlined, "FONT_MENU", meme);

			this->Line(x, y, x + 12, y, outlined);
			this->Line(x + 15 + txtSize.right + 5, y, x + w, y, outlined);
			this->Line(x, y, x, y + h, outlined);
			this->Line(x, y + h, x + w, y + h, outlined);
			this->Line(x + w, y, x + w, y + h, outlined);

		}
		void Circle( int x, int y, int radius, int segments, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawOutlinedCircle( x, y, radius, segments );
		}
		void CornerBox( int x, int y, int w, int h, Color color, bool outlined, int indicatorH = 5, int indicatorW = 5 )
		{
			m_Corner[ 0 ].x = x;
			m_Corner[ 0 ].y = y;
			m_Corner[ 0 ].w = w / indicatorW;
			m_Corner[ 0 ].h = 1;

			m_Corner[ 1 ].x = x + w - ( w / indicatorW );
			m_Corner[ 1 ].y = y;
			m_Corner[ 1 ].w = w / indicatorW;
			m_Corner[ 1 ].h = 1;

			m_Corner[ 2 ].x = x;
			m_Corner[ 2 ].y = y + h;
			m_Corner[ 2 ].w = w / indicatorW;
			m_Corner[ 2 ].h = 1;

			m_Corner[ 3 ].x = x + w - ( w / indicatorW );
			m_Corner[ 3 ].y = y + h;
			m_Corner[ 3 ].w = w / indicatorW;
			m_Corner[ 3 ].h = 1;

			m_Corner[ 4 ].x = x;
			m_Corner[ 4 ].y = y;
			m_Corner[ 4 ].w = 1;
			m_Corner[ 4 ].h = h / indicatorH;

			m_Corner[ 5 ].x = x + w - 1;
			m_Corner[ 5 ].y = y;
			m_Corner[ 5 ].w = 1;
			m_Corner[ 5 ].h = h / indicatorH;

			m_Corner[ 6 ].x = x;
			m_Corner[ 6 ].y = y + h - ( h / indicatorH );
			m_Corner[ 6 ].w = 1;
			m_Corner[ 6 ].h = h / indicatorH;

			m_Corner[ 7 ].x = x + w - 1;
			m_Corner[ 7 ].y = y + h - ( h / indicatorH ) + 1;
			m_Corner[ 7 ].w = 1;
			m_Corner[ 7 ].h = h / indicatorH;

			if( outlined )
				for( int i = 0; i < 8; i++ )
				{
					Rect( m_Corner[ i ].x - 1, m_Corner[ i ].y - 1, m_Corner[ i ].w + 2, m_Corner[ i ].h + 2, Color( 0, 0, 0, 255 ) );
					Rect( m_Corner[ i ].x + 1, m_Corner[ i ].y + 1, m_Corner[ i ].w - 2, m_Corner[ i ].h - 2, Color( 0, 0, 0, 255 ) );
				}

			for( int i = 0; i < 8; i++ )
				Rect( m_Corner[ i ].x, m_Corner[ i ].y, m_Corner[ i ].w, m_Corner[ i ].h, color );
		}
		void GardientRect( int x, int y, int w, int h, Color color1, Color color2, int variation )
		{

			Rect(x, y, w, h, color1);
			BYTE first = color2.r();
			BYTE second = color2.g();
			BYTE third = color2.b();
			for (int i = 0; i < h; i++)
			{
				float fi = i, fh = h;
				float a = fi / fh;
				DWORD ia = a * 255;
				Rect(x, y + i, w, 1, Color(first, second, third, ia));
			}
		}
		void GetTextSize( std::string szFontWrapperName, std::string szString, int& iWidth, int& iHeight )
		{
			if( szFontWrapperName.empty( ) || szString.empty( ) )
				return;

			UINT nFont = GetSurfaceFont( szFontWrapperName );
			if( !nFont )
				return;

			GetTextSize( nFont, szString, iWidth, iHeight );
		}
		void GetTextSize( ULONG Font, std::string szString, int& iWidth, int& iHeight )
		{
			if( szString.empty( ) )
				return;

			if( !Font )
				return;

			m_pSurface->GetTextSize( Font, szString, iWidth, iHeight );
		}
		RECT GetTextSizeREC(std::string szFontWrapperName, std::string text)
		{
			UINT font = GetSurfaceFont( szFontWrapperName );

			RECT rect; int x, y;
			m_pSurface->GetTextSize(font, text, x, y);
			rect.left = x; rect.bottom = y;
			rect.right = x;
			return rect;
		}

		void GetTextSize( std::string szFontWrapperName, std::string szString, int* iTextSize )
		{
			GetTextSize( szFontWrapperName, szString, iTextSize[ 0 ], iTextSize[ 1 ] );
		}
		void Line( int x0, int y0, int x1, int y1, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawLine( x0, y0, x1, y1 );
		}
		void Rect( int x, int y, int w, int h, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawFilledRect( x, y, x + w, y + h );
		}
		void Rect2(int x, int y, int w, int h, int r, int g, int b, int a)
		{
			Color color = Color(r, g, b, a);
			m_pSurface->DrawSetColor(color);
			m_pSurface->DrawFilledRect(x, y, x + w, y + h);
		}
		void Rect3(int x, int y, int w, int h, Color color)
		{
			m_pSurface->DrawSetColor(color);
			m_pSurface->DrawFilledRect(x, y, x + w, y + h);
		}
		void LineRGBA(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
		{
			Color color = Color(r, g, b, a);
			g_pSurface->DrawSetColor(color);
			g_pSurface->DrawLine(x1, y1, x2, y2);
		}
		void RectOutlined( int x, int y, int w, int h, int thickness, Color color, Color outlined )
		{
			this->Rect( x, y, w, h, color );
			this->BorderBox( x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined );
		}
		void RectOutlined2(int x, int y, int w, int h, int thickness, Color outlined)
		{
			this->BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined);
		}
		void StringOutlined( int x, int y, Color color, std::string szFontWrapperName, const char* fmt, ... )
		{
			ULONG SurfaceFont = GetSurfaceFont( szFontWrapperName );
			if( !SurfaceFont )
				return;

			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );
			va_end( args );

			this->StringOutlined( x, y, color, SurfaceFont, szBuffer );


		}
		std::wstring stringToWide(const std::string& text)
		{
			std::wstring wide(text.length(), L' ');
			std::copy(text.begin(), text.end(), wide.begin());

			return wide;
		}
		int Width(std::string font, const char* input, ...)
		{
			INT iWide = 0;
			INT iTall = 0;
			ULONG SurfaceFont = GetSurfaceFont(font);

			m_pSurface->GetTextSize(SurfaceFont, input, iWide, iTall);

			return iWide;
		}
		void DrawStringA(std::string font, bool center, int x, int y, ValveSDK::Color color, const char *input, ...)
		{
			CHAR szBuffer[MAX_PATH];

			if (!input)
				return;
			ULONG SurfaceFont = GetSurfaceFont(font);
			if (!SurfaceFont)
				return;
			vsprintf_s(szBuffer, input, (char*)&input + _INTSIZEOF(input));

			if (center)
				x -= Width(font, szBuffer) / 2;

			y += 4;

			m_pSurface->DrawSetTextColor(color);
			m_pSurface->DrawSetTextFont(SurfaceFont);
			m_pSurface->DrawSetTextPos(x, y);
			std::wstring wide = stringToWide(std::string(szBuffer));
			m_pSurface->DrawPrintText(wide.c_str(), wide.length());
		}

		void String( int x, int y, Color color, ULONG font, const char* fmt, ... )
		{
			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );

			m_pSurface->DrawSetTextPos( x, y );
			m_pSurface->DrawSetTextFont( font );
			m_pSurface->DrawSetTextColor( color );

			int nChars = MultiByteToWideChar( CP_ACP, 0, szBuffer, -1, NULL, 0 );

			const WCHAR *pwcsName;
			pwcsName = new WCHAR[ nChars ];
			MultiByteToWideChar( CP_ACP, 0, szBuffer, -1, ( LPWSTR )pwcsName, nChars );

			va_end( args );

			m_pSurface->DrawPrintText( pwcsName, wcslen( pwcsName ) );
		}
		void String( int x, int y, Color color, std::string szFontWrapperName, const char* fmt, ... )
		{
			ULONG SurfaceFont = GetSurfaceFont( szFontWrapperName );
			if( !SurfaceFont )
				return;

			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );

			this->String( x, y, color, SurfaceFont, szBuffer );
		}

		void LennyFace(int x, int y, Color color, std::string szFontWrapperName, int iLennyFaceNumer)
		{

			ULONG SurfaceFont = GetSurfaceFont(szFontWrapperName);
			if (!SurfaceFont)
				return;

			m_pSurface->DrawSetTextPos(x, y);
			m_pSurface->DrawSetTextFont(SurfaceFont);
			m_pSurface->DrawSetTextColor(color);
		

			wchar_t* wcsLenny = L"LOL";

			switch (iLennyFaceNumer) {
				case 1:
					wcsLenny = L"( ͡° ͜ʖ ͡°)";
					break;
				case 2:
					wcsLenny = L"[̲̅$̲̅(̲̅ ͡° ͜ʖ ͡°̲̅)̲̅$̲̅]";
					break;
				case 3:
					wcsLenny = L"(▀̿Ĺ̯▀̿ ̿)";
					break;
				case 4:
					wcsLenny = L"( ͡°( ͡° ͜ʖ( ͡° ͜ʖ ͡°)ʖ ͡°) ͡°)";
					break;
				case 5:
					wcsLenny = L"▄︻̷̿┻̿═━一";
					break;
			}

			m_pSurface->DrawUnicodeString(wcsLenny);
		}

		void UnicodeString(int x, int y, Color color, std::string szFontWrapperName, wchar_t* wcText)
		{

			ULONG SurfaceFont = GetSurfaceFont(szFontWrapperName);
			if (!SurfaceFont)
				return;

			m_pSurface->DrawSetTextPos(x, y);
			m_pSurface->DrawSetTextFont(SurfaceFont);
			m_pSurface->DrawSetTextColor(color);


			m_pSurface->DrawUnicodeString(wcText);
		}
		void StringOutlined( int x, int y, Color color, ULONG font, const char* fmt, ... )
		{
			std::string szBuffer;
			va_list args;
			va_start( args, fmt );
			int iSize = _vscprintf( fmt, args );
			szBuffer.resize( iSize );
			vsnprintf_s( ( char* )szBuffer.data( ), iSize, _TRUNCATE, fmt, args );
			va_end( args );


			this->String( x - 1, y, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y - 1, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );

			this->String( x + 1, y, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y + 1, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y, color, font, szBuffer.c_str( ) );

			va_end( args );
		}
		void CreateAllFonts( void )
		{
			if( !m_bSurfaceFontsCreated )
			{
				for( std::size_t i = 0; i < m_vSurfaceFonts.size( ); i++ )
				{
					m_vSurfaceFonts.at( i ).m_Font = m_pSurface->FontCreate( );
					m_pSurface->SetFontGlyphSet( m_vSurfaceFonts.at( i ).m_Font,
						m_vSurfaceFonts.at( i ).m_strWindowsFontName.c_str( ),
						m_vSurfaceFonts.at( i ).m_iTall,
						m_vSurfaceFonts.at( i ).m_iWeight,
						m_vSurfaceFonts.at( i ).m_iBlur,
						m_vSurfaceFonts.at( i ).m_iScanlines,
						m_vSurfaceFonts.at( i ).m_iFlags,
						m_vSurfaceFonts.at( i ).m_iRangeMin,
						m_vSurfaceFonts.at( i ).m_iRangeMax );
				}


				m_bSurfaceFontsCreated = true;
			}
		}
		void SetSurface( ISurface* pSurface )
		{
			m_pSurface = pSurface;
		}
	};
	class IMultiplayerPhysics
	{
	public:
		virtual int		GetMultiplayerPhysicsMode( void ) = 0;
		virtual float	GetMass( void ) = 0;
		virtual bool	IsAsleep( void ) = 0;
	};
	class IBreakableWithPropData
	{
	public:
		// Damage modifiers
		virtual void            SetDmgModBullet( float flDmgMod ) = 0;
		virtual void            SetDmgModClub( float flDmgMod ) = 0;
		virtual void            SetDmgModExplosive( float flDmgMod ) = 0;
		virtual float           GetDmgModBullet( void ) = 0;
		virtual float           GetDmgModClub( void ) = 0;
		virtual float           GetDmgModExplosive( void ) = 0;
		// Explosive
		virtual void            SetExplosiveRadius( float flRadius ) = 0;
		virtual void            SetExplosiveDamage( float flDamage ) = 0;
		virtual float           GetExplosiveRadius( void ) = 0;
		virtual float           GetExplosiveDamage( void ) = 0;
		// Physics damage tables
		virtual void            SetPhysicsDamageTable( char* iszTableName ) = 0;
		virtual char*           GetPhysicsDamageTable( void ) = 0;
		// Breakable chunks
		virtual void            SetBreakableModel( char* iszModel ) = 0;
		virtual char*           GetBreakableModel( void ) = 0;
		virtual void            SetBreakableSkin( int iSkin ) = 0;
		virtual int                     GetBreakableSkin( void ) = 0;
		virtual void            SetBreakableCount( int iCount ) = 0;
		virtual int                     GetBreakableCount( void ) = 0;
		virtual void            SetMaxBreakableSize( int iSize ) = 0;
		virtual int                     GetMaxBreakableSize( void ) = 0;
		// LOS blocking
		virtual void            SetPropDataBlocksLOS( bool bBlocksLOS ) = 0;
		virtual void            SetPropDataIsAIWalkable( bool bBlocksLOS ) = 0;
		// Interactions
		virtual void            SetInteraction( propdata_interactions_t Interaction ) = 0;
		virtual bool            HasInteraction( propdata_interactions_t Interaction ) = 0;
		// Multi player physics mode
		virtual void            SetPhysicsMode( int iMode ) = 0;
		virtual int                     GetPhysicsMode( ) = 0;
		// Multi player breakable spawn behavior
		virtual void            SetMultiplayerBreakMode( mp_break_t mode ) = 0;
		virtual mp_break_t      GetMultiplayerBreakMode( void ) const = 0;
		// Used for debugging
		virtual void            SetBasePropData( char* iszBase ) = 0;
		virtual char*           GetBasePropData( void ) = 0;
	};

	class IPhysicsSurfaceProps
	{
	public:
		virtual ~IPhysicsSurfaceProps(void) {}

		// parses a text file containing surface prop keys
		virtual int		ParseSurfaceData(const char *pFilename, const char *pTextfile) = 0;
		// current number of entries in the database
		virtual int		SurfacePropCount(void) const = 0;

		virtual int		GetSurfaceIndex(const char *pSurfacePropName) const = 0;
		virtual void	GetPhysicsProperties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;

		virtual surfacedata_t	*GetSurfaceData(int surfaceDataIndex) = 0;
		virtual const char		*GetString(unsigned short stringTableIndex) const = 0;


		virtual const char		*GetPropName(int surfaceDataIndex) const = 0;

		// sets the global index table for world materials
		// UNDONE: Make this per-CPhysCollide
		virtual void	SetWorldMaterialIndexTable(int *pMapArray, int mapSize) = 0;

		// NOTE: Same as GetPhysicsProperties, but maybe more convenient
		virtual void	GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
	};
	class KeyValues
	{
	public:
		static void SetUseGrowableStringTable( bool bUseGrowableTable );

		KeyValues( const char *setName )
		{
			Init( );
			SetName( setName );
		}

		class AutoDelete
		{
		public:
			explicit inline AutoDelete( KeyValues *pKeyValues ) : m_pKeyValues( pKeyValues ) {}
			explicit inline AutoDelete( const char *pchKVName ) : m_pKeyValues( new KeyValues( pchKVName ) ) {}
			inline ~AutoDelete( void ) { if( m_pKeyValues ) m_pKeyValues->deleteThis( ); }
			inline void Assign( KeyValues *pKeyValues ) { m_pKeyValues = pKeyValues; }
			KeyValues *operator->( )	{ return m_pKeyValues; }
			operator KeyValues *( )	{ return m_pKeyValues; }
		private:
			AutoDelete( AutoDelete const &x ); // forbid
			AutoDelete & operator= ( AutoDelete const &x ); // forbid
			KeyValues *m_pKeyValues;
		};

		const char *GetName( ) const;
		void SetName( const char *setName )
		{
			m_iKeyName = 2;
		}

		int GetNameSymbol( ) const { return m_iKeyName; }

		void UsesEscapeSequences( bool state ); // default false
		void UsesConditionals( bool state ); // default true

		KeyValues *FindKey( const char *keyName, bool bCreate = false );
		KeyValues *FindKey( int keySymbol ) const;
		KeyValues *CreateNewKey( );		// creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
		void AddSubKey( KeyValues *pSubkey );	// Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
		void RemoveSubKey( KeyValues *subKey );	// removes a subkey from the list, DOES NOT DELETE IT

		KeyValues *GetFirstSubKey( ) { return m_pSub; }	// returns the first subkey in the list
		KeyValues *GetNextKey( ) { return m_pPeer; }		// returns the next subkey
		void SetNextKey( KeyValues * pDat );
		KeyValues *FindLastSubKey( );	// returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

		KeyValues* GetFirstTrueSubKey( );
		KeyValues* GetNextTrueSubKey( );

		KeyValues* GetFirstValue( );	// When you get a value back, you can use GetX and pass in NULL to get the value.
		KeyValues* GetNextValue( );

		// Data access
		int   GetInt( const char *keyName = NULL, int defaultValue = 0 );
		float GetFloat( const char *keyName = NULL, float defaultValue = 0.0f );
		const char *GetString( const char *keyName = NULL, const char *defaultValue = "" );
		const wchar_t *GetWString( const char *keyName = NULL, const wchar_t *defaultValue = L"" );
		void *GetPtr( const char *keyName = NULL, void *defaultValue = ( void* )0 );
		bool GetBool( const char *keyName = NULL, bool defaultValue = false );
		bool  IsEmpty( const char *keyName = NULL );

		// Data access
		int   GetInt( int keySymbol, int defaultValue = 0 );
		float GetFloat( int keySymbol, float defaultValue = 0.0f );
		const char *GetString( int keySymbol, const char *defaultValue = "" );
		const wchar_t *GetWString( int keySymbol, const wchar_t *defaultValue = L"" );
		void *GetPtr( int keySymbol, void *defaultValue = ( void* )0 );
		bool  IsEmpty( int keySymbol );

		// Key writing
		void SetWString( const char *keyName, const wchar_t *value );
		void SetString( const char *keyName, const char *value );
		void SetInt( const char *keyName, int value );
		void SetUint64( const char *keyName, UINT value );
		void SetFloat( const char *keyName, float value );
		void SetPtr( const char *keyName, void *value );
		void SetBool( const char *keyName, bool value ) { SetInt( keyName, value ? 1 : 0 ); }

		KeyValues& operator=( KeyValues& src );

		// Adds a chain... if we don't find stuff in this keyvalue, we'll look
		// in the one we're chained to.
		void ChainKeyValue( KeyValues* pChain );

		// Allocate & create a new copy of the keys
		KeyValues *MakeCopy( void ) const;

		// Make a new copy of all subkeys, add them all to the passed-in keyvalues
		void CopySubkeys( KeyValues *pParent ) const;

		// Clear out all subkeys, and the current value
		void Clear( void );

		// Data type
		enum types_t
		{
			TYPE_NONE = 0,
			TYPE_STRING,
			TYPE_INT,
			TYPE_FLOAT,
			TYPE_PTR,
			TYPE_WSTRING,
			TYPE_COLOR,
			TYPE_UINT64,
			TYPE_NUMTYPES,
		};
		types_t GetDataType( const char *keyName = NULL );

		// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
		void deleteThis( );

		void SetStringValue( char const *strValue );

		// unpack a key values list into a structure
		void UnpackIntoStructure( struct KeyValuesUnpackStructure const *pUnpackTable, void *pDest, size_t DestSizeInBytes );

		// Process conditional keys for widescreen support.
		bool ProcessResolutionKeys( const char *pResString );

		// Dump keyvalues recursively into a dump context
		bool Dump( class IKeyValuesDumpContext *pDump, int nIndentLevel = 0 );

		// Merge in another KeyValues, keeping "our" settings
		void RecursiveMergeKeyValues( KeyValues *baseKV );

	public:
		KeyValues( KeyValues& );	// prevent copy constructor being used

		// prevent delete being called except through deleteThis()
		~KeyValues( );

		KeyValues* CreateKey( const char *keyName );

		KeyValues* CreateKeyUsingKnownLastChild( const char *keyName, KeyValues *pLastChild );
		void AddSubkeyUsingKnownLastChild( KeyValues *pSubKey, KeyValues *pLastChild );

		void RecursiveCopyKeyValues( KeyValues& src );
		void RemoveEverything( );

		void Init( )
		{
			m_iKeyName = -1;
			m_iDataType = TYPE_NONE;

			m_pSub = NULL;
			m_pPeer = NULL;
			m_pChain = NULL;

			m_sValue = NULL;
			m_wsValue = NULL;
			m_pValue = NULL;

			m_bHasEscapeSequences = false;

			// for future proof
			memset( unused, 0, sizeof( unused ) );
		}

		void FreeAllocatedValue( );
		void AllocateValueBlock( int size );

		int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

		// These are needed out of the union because the API returns string pointers
		char *m_sValue;
		wchar_t *m_wsValue;

		// we don't delete these
		union
		{
			int m_iValue;
			float m_flValue;
			void *m_pValue;
			unsigned char m_Color[ 4 ];
		};

		char	   m_iDataType;
		char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
		char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
		char	   unused[ 1 ];

		KeyValues *m_pPeer;	// pointer to next key in list
		KeyValues *m_pSub;	// pointer to Start of a new sub key list
		KeyValues *m_pChain;// Search here if it's not in our list

	private:
		// Statics to implement the optional growable string table
		// Function pointers that will determine which mode we are in
		static int( *s_pfGetSymbolForString )( const char *name, bool bCreate );
		static const char *( *s_pfGetStringForSymbol )( int symbol );

	public:
		// Functions that invoke the default behavior
		static int GetSymbolForStringClassic( const char *name, bool bCreate = true );
		static const char *GetStringForSymbolClassic( int symbol );

		// Functions that use the growable string table
		static int GetSymbolForStringGrowable( const char *name, bool bCreate = true );
		static const char *GetStringForSymbolGrowable( int symbol );

		// Functions to get external access to whichever of the above functions we're going to call.
		static int CallGetSymbolForString( const char *name, bool bCreate = true ) { return s_pfGetSymbolForString( name, bCreate ); }
		static const char *CallGetStringForSymbol( int symbol ) { return s_pfGetStringForSymbol( symbol ); }

		bool LoadFromBuffer( KeyValues *pThis, const char *pszFirst, const char *pszSecond, PVOID pSomething = 0, PVOID pAnother = 0, PVOID pLast = 0 )
		{
			typedef bool( __thiscall *LoadFromBuffer_t )( KeyValues*, const char*, const char*, PVOID, PVOID, PVOID );

			static LoadFromBuffer_t callLoadBuff = ( LoadFromBuffer_t )( Offsets::m_dwLoadFromBuffer );

			return callLoadBuff( pThis, pszFirst, pszSecond, pSomething, pAnother, pLast );
		}//wait i will check my code
	};
	class IMaterialSystem
	{
	public:
		IMaterial* CreateMaterial(const char* pMaterialName, KeyValues* pVMTKeyValues)
		{
			VirtualFn(IMaterial*)(PVOID, const char*, KeyValues*);
			return CallVirtual< OriginalFn >(this, 83)(this, pMaterialName, pVMTKeyValues);
		}
		IMaterial* FindMaterial(const char* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = 0)
		{
			VirtualFn(IMaterial*)(PVOID, const char*, const char*, bool, const char*);
			return CallVirtual< OriginalFn >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
		}
		MaterialHandle_t FirstMaterial()
		{
			VirtualFn(MaterialHandle_t)(PVOID);
			return CallVirtual< OriginalFn >(this, 86)(this);
		}
		MaterialHandle_t NextMaterial(MaterialHandle_t h)
		{
			VirtualFn(MaterialHandle_t)(PVOID, MaterialHandle_t);
			return CallVirtual< OriginalFn >(this, 87)(this, h);
		}
		MaterialHandle_t InvalidMaterial()
		{
			VirtualFn(MaterialHandle_t)(PVOID);
			return CallVirtual< OriginalFn >(this, 88)(this);
		}
		IMaterial* GetMaterial(MaterialHandle_t h)
		{
			VirtualFn(IMaterial*)(PVOID, MaterialHandle_t);
			return CallVirtual< OriginalFn >(this, 89)(this, h);
		}
		int	GetNumMaterials()
		{
			VirtualFn(int)(PVOID);
			return CallVirtual< OriginalFn >(this, 90)(this);
		}
		
	};
	class CHudTexture
	{
		char	szShortName[64];	//0x0000
		char	szTextureFile[64];	//0x0040
		bool	bRenderUsingFont;	//0x0080
		bool	bPrecached;			//0x0081
		char	cCharacterInFont;	//0x0082
		BYTE	pad_0x0083;			//0x0083
		int		hFont;				//0x0084
		int		iTextureId;			//0x0088
		float	afTexCoords[4];		//0x008C
		int		iPosX[4];			//0x009C
	}; //Size=0x00AC

	class CWeaponData
	{
	public:
		char _0x0000[4];
		BYTE m_bParsedScript; //0x0004 
		BYTE m_bLoadedHudElements; //0x0005 
		BYTE m_szClassName; //0x0006 
		char _0x0007[1961];
		__int32 m_iAmmoType; //0x07B0 
		char _0x07B4[12];
		CHudTexture* m_pHudTexture_WeaponSilenced; //0x07C0 
		CHudTexture* m_pHudTexture_Weapon; //0x07C4 
		CHudTexture* m_pHudTexture_Ammo; //0x07C8 
		char _0x07CC[4];
		CHudTexture* m_pHudTexture_Crosshair; //0x07D0 
		char _0x07D4[20];
		__int32 m_iWeaponType; //0x07E8 
		__int32 m_iTeam; //0x07EC 
		__int32 m_iWeaponId; //0x07F0 
		BYTE m_IsFullAuto; //0x07F4 
		char _0x07F5[3];
		float m_flHeatPerShot; //0x07F8 
		__int32 m_iWeaponPrice; //0x07FC 
		float m_flArmorRatio; //0x0800 
		float m_flMaxPlayerSpeed; //0x0804 
		float m_flMaxPlayerSpeedAlt; //0x0808 
		__int32 m_iCrosshairMinDistance; //0x080C 
		__int32 m_iCrosshairDeltaDistance; //0x0810 
		float m_flPenetration; //0x0814 
		__int32 m_iDamage; //0x0818 
		float m_flRange; //0x081C 
		float m_flRangeModifier; //0x0820 
		__int32 m_iBullets; //0x0824 
		float m_flCycleTime; //0x0828 
		float m_flCycleTimeAlt; //0x082C 
		char _0x0830[416];
		float m_flSpread; //0x09D0 
		float m_flSpreadAlt; //0x09D4 
		float m_flInaccuracyCrouch; //0x09D8 
		float m_flInaccuracyCrouchAlt; //0x09DC 
		float m_flInaccuracyStand; //0x09E0 
		float m_flInaccuracyStandAlt; //0x09E4 
		float m_flInaccuracyJump; //0x09E8 
		float m_flInaccuracyJumpAlt; //0x09EC 
		float m_flInaccuracyLand; //0x09F0 
		float m_flInaccuracyLandAlt; //0x09F4 
		float m_flInaccuracyLadder; //0x09F8 
		float m_flInaccuracyLadderAlt; //0x09FC 
		float m_flInaccuracyFire; //0x0A00 
		float m_flInaccuracyFireAlt; //0x0A04 
		float m_flInaccuracyMove; //0x0A08 
		float m_flInaccuracyMoveAlt; //0x0A0C 
		float m_flRecoveryTimeStand; //0x0A10 
		float m_flRecoveryTimeCrouch; //0x0A14 
		float m_flInaccuracyReload; //0x0A18 
		float m_flInaccuracyAltSwitch; //0x0A1C 
		float m_flRecoilAngle; //0x0A20 
		float m_flRecoilAngleAlt; //0x0A24 
		float m_flRecoilAngleVariance; //0x0A28 
		float m_flRecoilAngleVarianceAlt; //0x0A2C 
		float m_flRecoilMagnitude; //0x0A30 
		float m_flRecoilMagnitudeAlt; //0x0A34 
		float m_flRecoilMagnitudeVariance; //0x0A38 
		float m_flRecoilMagnitudeVarianceAlt; //0x0A3C 
		__int32 m_iRecoilSeed; //0x0A40 
		float m_flFlinchVelocityModifierLarge; //0x0A44 
		float m_flFlinchVelocityModifierSmall; //0x0A48 
		float m_flTimeToIdle; //0x0A4C 
		float m_flIdleInterval; //0x0A50 
	};//Size=0x1038
	class CBaseCombatWeapon
	{
	public:
		bool IsPistol( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_PISTOLS ? true : false;
		}
		bool IsTaser( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_TASER ? true : false;
		}
		bool IsShotgun( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SHOTGUN ? true : false;
		}
		bool IsSMG( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SMG ? true : false;
		}
		bool IsRifle( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_RIFLE ? true : false;
		}
		bool IsMG( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_MG ? true : false;
		}
		bool IsSniper( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SNIPER ? true : false;
		}
		bool IsGrenade( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_GRENADE;
		}
		bool IsKnife( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_KNIFE ? true : false;
		}
		bool IsValid( bool bTaserIsValid = false )
		{
			int iItemSchemaWeaponType = GetItemSchemaWeaponType( );

			switch( iItemSchemaWeaponType )
			{
			case WEAPON_TYPE_PISTOLS:
				break;
			case WEAPON_TYPE_SHOTGUN:
				break;
			case WEAPON_TYPE_SMG:
				break;
			case WEAPON_TYPE_RIFLE:
				break;
			case WEAPON_TYPE_MG:
				break;
			case WEAPON_TYPE_SNIPER:
				break;
			case WEAPON_TYPE_TASER:
				if( bTaserIsValid )
					break;
				else return false;
			default:
				return false;
			}

			return( GetClip1( ) > 0 );
		}
		bool IsAutomatic( bool bAutoSniper = false )
		{
			if( bAutoSniper )
			{
				int iItemSchemaId = GetItemDefinitionIndex( );
				if( iItemSchemaId == WEAPON_SCAR20 || WEAPON_G3SG1 )
					return true;
			}

			int iItemSchemaWeaponType = GetItemSchemaWeaponType( );
			switch( iItemSchemaWeaponType )
			{
			case WEAPON_TYPE_SMG:
				return true;
			case WEAPON_TYPE_RIFLE:
				return true;
			case WEAPON_TYPE_MG:
				return true;
			default:
				break;
			}

			return false;
		}
		bool HitChance( float flChance )
		{
			if( flChance >= 99.f )
				flChance = 99.f;

			if( flChance < 1 )
				flChance = 1;

			float flSpread = GetSpread( );
			return( ( ( ( 100.f - flChance ) * 0.65f ) * 0.01125 ) >= flSpread );
		}
		CWeaponData* GetWeaponData( void )
		{
			VirtualFn(CWeaponData*)( PVOID );
			return CallVirtual< OriginalFn >( this, 456 )( this );
		}
		float GetSpread( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 484 )( this );
		}
		float GetInaccuracy( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 483 )( this );
		}
		float GetNextPrimaryAttack( void )
		{
			return *( float* )( ( DWORD )this + Offsets::m_flNextPrimaryAttack );
		}
		int GetClip1( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iClip1 );
		}
		int GetItemDefinitionIndex( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iItemDefinitionIndex );
		}
		int GetItemSchemaWeaponType( void )
		{
			int iItemSchemaId = GetItemDefinitionIndex( );

			switch( iItemSchemaId )
			{
			case WEAPON_DEAGLE:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_DUALS:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_FIVE7:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_GLOCK:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_AK47:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_AUG:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_AWP:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_FAMAS:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_G3SG1:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_GALIL:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_M249:
				return WEAPON_TYPE_MG;
			case WEAPON_M4A1:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_MAC10:
				return WEAPON_TYPE_SMG;
			case WEAPON_P90:
				return WEAPON_TYPE_SMG;
			case WEAPON_UMP45:
				return WEAPON_TYPE_SMG;
			case WEAPON_XM1014:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_BIZON:
				return WEAPON_TYPE_SMG;
			case WEAPON_MAG7:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_NEGEV:
				return WEAPON_TYPE_MG;
			case WEAPON_SAWEDOFF:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_TEC9:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_TASER:
				return WEAPON_TYPE_TASER;
			case WEAPON_P2000:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_REVOLVER:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_MP7:
				return WEAPON_TYPE_SMG;
			case WEAPON_MP9:
				return WEAPON_TYPE_SMG;
			case WEAPON_NOVA:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_P250:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_SCAR20:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_SG553:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_SCOUT:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_KNIFE_T:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_FLASH:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_HE:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_SMOKE:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_MOLOTOV:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_DECOY:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_INC:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_C4:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_KNIFE_CT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_M4A1S:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_USPS:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_CZ75:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_KNIFE_BAYONET:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_FLIP:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_GUT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_KARAMBIT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_M9BAYONET:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_FALCHION:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_BUTTERFLY:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_SHADOWDAGGERS:
				return WEAPON_TYPE_KNIFE;
			default:
				break;
			}

			return WEAPON_TYPE_INVALID;
		}
		int GetWeaponId( void )
		{
			return GetItemDefinitionIndex( );
		}
		void UpdateAccuracyPenalty( void )
		{
			VirtualFn( void )( PVOID );
			CallVirtual< OriginalFn >( this, 485 )( this );
		}
		int GetOwner( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_hOwnerEntity );
		}
		void SetPattern(int skin, int quality, int seed, int stattrak, const char* name)
		{

			*( int* )( ( DWORD )this + Offsets::m_nFallbackPaintKit) = skin;
			*( int* )( ( DWORD )this + Offsets::m_iEntityQuality) = quality;
			*( int* )( ( DWORD )this + Offsets::m_nFallbackSeed ) = seed;
			*( int* )( ( DWORD )this + Offsets::m_nFallbackStatTrak) = stattrak;
			*( float* )( ( DWORD )this + Offsets::m_flFallbackWear ) = 0.0001;

			if (name != "") {
				char* a = (char*)((DWORD)this + Offsets::m_szCustomName);
				sprintf_s(a, 32, "%s", name);
			}

			*( int* )( ( DWORD )this + Offsets::m_iItemIDHigh) = -1;
		}
	};
	
	class CBaseEntity
	{
	public:
		CBaseCombatWeapon* GetWeapon( void )
		{
			EHANDLE hWeapon = GetActiveWeapon( );
			if( !hWeapon )
				return nullptr;

			return ( CBaseCombatWeapon* )g_pEntityList->GetBaseEntityFromHandle( hWeapon );
		}
		bool IsValid2()
		{
			bool bRetVal = (GetHealth() >= 1 && !IsDormant()) ? true : false;

			return bRetVal;

		}
		bool IsValid()
		{
			bool bRetVal = ( GetHealth( ) >= 1 && !IsDormant( ) ) ? true : false;
			if(IsProtected( ) )
				bRetVal = false;

			return bRetVal;

		}
		int GetIndex()
		{
			int iEntIndex;

			PVOID pEnt = (PVOID)this;

			__asm
			{
				MOV ECX, this
				MOV EAX, DWORD PTR DS : [ECX + 0x8]
				MOV EDX, DWORD PTR DS : [EAX + 0x28]
				LEA ESI, DWORD PTR DS : [ECX + 0x8]
				MOV ECX, ESI
				CALL EDX
				MOV iEntIndex, EAX
			}

			return iEntIndex;
		}
		int SetFov(int fovvalue)
		{
			static int iOffset = g_pNetVars->GetOffset("DT_BasePlayer", "m_iDefaultFOV");
			*(int*)((DWORD)this + iOffset) = fovvalue;
			static int iOffset2 = g_pNetVars->GetOffset("DT_CSPlayer", "m_bIsScoped");
			bool scopecheck = *(bool*)((DWORD)this + iOffset2);
			if (!scopecheck)
			{
				static int iOffset3 = g_pNetVars->GetOffset("DT_BasePlayer", "m_iFOV");
				*(int*)((DWORD)this + iOffset3) = fovvalue;
			}
			return true;
		}
		bool IsDormant( void )
		{
			VirtualFn( bool )( PVOID );
			PVOID pNetworkable = GetNetworkable( );
			return CallVirtual< OriginalFn >( pNetworkable, 9 )( pNetworkable );
		}
		bool IsScoped( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsScoped );
		}
		bool HasHelmet( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bHasHelmet );
		}
		bool IsBroken( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsBroken );
		}
		bool IsDefusing( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsDefusing );
		}
		bool IsChicken(void)
		{
			return this->GetClientClass()->GetClassID() == 30;
		}
		bool IsProtected( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bGunGameImmunity );
		}
		bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
		{
			*(int*)((uintptr_t) this + Offsets::m_nWriteableBones) = 0;
			*(int*)((uintptr_t) this + Offsets::m_iDidCheckForOcclusion) = reinterpret_cast<int*>(Offsets::m_dOcclusionArray)[1];
			reinterpret_cast<void(__fastcall*)(void*)>(Offsets::InvalidateBoneCache)(this);
			__asm
			{
				mov edi, this
				lea ecx, dword ptr ds : [edi + 0x4]
				mov edx, dword ptr ds : [ecx]
				push currentTime
				push boneMask
				push nMaxBones
				push pBoneToWorldOut
				call dword ptr ds : [edx + 0x34]
			}
		}
		bool SetupBones2(CBaseEntity *pAnimating, matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
		{
			bool bRet;
			__asm
			{
				PUSH currentTime
				PUSH boneMask
				PUSH nMaxBones
				PUSH pBoneToWorldOut
				MOV ECX, DWORD PTR DS : [pAnimating]
				ADD ECX, 4
				MOV EDX, DWORD PTR DS : [pAnimating]
				MOV EAX, DWORD PTR DS : [EDX + 4]
				MOV EDX, DWORD PTR DS : [EAX + 0x34]
				CALL EDX
				MOV bRet, AL
			}
			return bRet;
		}
		BYTE GetFlags( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_fFlags );
		}
		BYTE GetLifeState( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_lifeState );
		}
		BYTE GetMoveType( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_moveType );
		}
		int GetCash()
		{
			static int iOffset = g_pNetVars->GetOffset("DT_CSPlayer", "m_iAccount");
			return *(int*)((DWORD)this + iOffset);
		}
		Color GetTeamColor( bool bIsVisible = false )
		{
			int iTeam = GetTeam( );

			Color color = ( iTeam == 2 ) ? Color( 255, 0, 0 ) : Color( 0, 176, 255 );
			if( bIsVisible )
				color = ( iTeam == 2 ) ? Color( 255, 201, 14 ) : Color( 0, 255, 0 );

			return color;
		}
		Color GetHealthColor( void )
		{
			if( !this->IsValid() )
				return Color( 175, 175, 175 );

			float flHealth = ( float )GetHealth( );
			float r = 255.f - flHealth * 2.55f;
			float g = flHealth * 2.55f;
			return Color( int( r ), int( g ), 0 );
		}
		ClientClass* GetClientClass( void )
		{
			VirtualFn( ClientClass* )( PVOID );
			PVOID pNetworkable = GetNetworkable( );
			return CallVirtual< OriginalFn >( pNetworkable, 2 )( pNetworkable );
		}
		EHANDLE GetActiveWeapon(void)
		{
			return *(EHANDLE*)((DWORD)this + Offsets::m_hActiveWeapon);
		}
		EHANDLE* GetWeapons(void)
		{
			return (EHANDLE*)((DWORD)this + Offsets::m_hMyWeapons);
		}
		int GetArmorValue( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_ArmorValue );
		}
		int GetCollisionGroup( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_CollisionGroup );
		}
		int GetMoney( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iAccount );
		}
		int GetHealth( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iHealth );
		}
		int GetTeam( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iTeamNum );
		}
		int GetTickBase( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_nTickBase );
		}
		int GetShotsFired( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iShotsFired );
		}

		model_t* GetModel( void )
		{
			VirtualFn( model_t* )( PVOID );
			PVOID pRenderable = GetRenderable( );
			return CallVirtual< OriginalFn >( pRenderable, 8 )( pRenderable );
		}
		void GetRenderBounds(Vector &mins, Vector &maxs)
		{
			VirtualFn(void)(PVOID, Vector&, Vector&);
			PVOID pRenderable = GetRenderable();
			CallVirtual< OriginalFn >(pRenderable, 17)(pRenderable, mins, maxs);
		}
		PVOID GetRenderable( void )
		{
			return ( PVOID )( ( DWORD )this + 0x4 );
		}
		PVOID GetNetworkable( void )
		{
			return ( PVOID )( ( DWORD )this + 0x8 );
		}
		UINT PhysicsSolidMaskForEntity( void )
		{
			VirtualFn( UINT )( PVOID );
			return CallVirtual< OriginalFn >( this, 148 )( this );
		}
		QAngle& GetAbsAngles( void )
		{
			VirtualFn( QAngle& )( PVOID );
			return CallVirtual< OriginalFn >( this, 11 )( this );
		}
		Vector& GetAbsOrigin( void )
		{
			VirtualFn( Vector& )( PVOID );
			return CallVirtual< OriginalFn >( this, 10 )( this );
		}
		Vector& m_vecNetworkOrigin() {
			static int offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFriction") - sizeof(Vector);
			return *(Vector*)((DWORD)this + offset);
		}
		Vector GetEyePosition( void )
		{
			return GetAbsOrigin( ) + *( Vector* )( ( DWORD )this + Offsets::m_vecViewOffset );


		}
		float& m_flOldSimulationTime() {
			static int offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flSimulationTime") + 0x4;
			return *(float*)((DWORD)this + offset);
		}
		float& m_flSimulationTime() {
			static int offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flSimulationTime");
			return *(float*)((DWORD)this + offset);
		}

		int GetChockedPackets() {
			if (m_flSimulationTime() > Global::OldSimulationTime[this->GetIndex()])
				return TIME_TO_TICKS(fabs(m_flSimulationTime() - Global::OldSimulationTime[this->GetIndex()]));
			return 0;
		}
		Vector GetEyeAngles()
		{
			static int iOffset = g_pNetVars->GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
			return *(Vector*)((DWORD)this + iOffset);
		}
		QAngle GetEyeAnglesXY()
		{
			return *(QAngle*)((DWORD)this + g_pNetVars->GetOffset("DT_CSPlayer", "m_angEyeAngles"));
		}
		void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector &out)
		{
			out.x = in1.Dots(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
			out.y = in1.Dots(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
			out.z = in1.Dots(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
		}
		float GenerateRandomFloat(float Min, float Max)
		{
			float randomized = (float)rand() / (float)RAND_MAX;
			return Min + randomized * (Max - Min);
		}

		Vector GetHitboxPosition( int Hitbox)
		{

			matrix3x4_t matrix[128];

			if (!this->SetupBones(matrix, 128, 0x00000100, 0))
				return Vector(0, 0, 0);

			studiohdr_t* hdr = g_pModelInfo->GetStudioModel(this->GetModel());
			if (!hdr)
				return Vector(0, 0, 0);
			mstudiohitboxset_t* set = hdr->pHitboxSet(this->GetHitboxSet());//hdr->pHitboxSet(0);

			mstudiobbox_t* hitbox = set->pHitbox(Hitbox);

			if (!hitbox)
				return Vector(0, 0, 0);

			Vector vMin, vMax, vCenter, sCenter;
			VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
			VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
			vCenter = (vMin + vMax) * 0.5;
			if (!vCenter)
				return Vector(0, 0, 0);
			Vector VHandle[30];

			float pointscale = g_CVars.GetCVar("rage_pointscale")->GetFloat();
			vCenter.z += pointscale*3;
			if (this->GetChockedPackets() > 3 && g_CVars.GetCVar("rage_prediction")->GetBool())
			{
				vCenter -= this->GetAbsOrigin();
				vCenter += this->m_vecNetworkOrigin();
			}
			if (!vCenter)
				return Vector(0, 0, 0);

			if (g_CVars.GetCVar("rage_multipoint")->GetInt() > 0)
			{

				for (auto i = 0; i <= 10; i++)
				{
					ValveSDK::IEngineTrace::trace_t tr;
					ValveSDK::IEngineTrace::Ray_t ray;
					ValveSDK::IEngineTrace::CTraceFilter filter;
					filter.pSkip = this;
					int look = g_CVars.GetCVar("rage_multipoint")->GetInt() * 4;
					float randflz = GenerateRandomFloat(0, look);
					float randflxy = GenerateRandomFloat(-look, look);
					ray.Init(Global::pLocalAngles, vCenter + ValveSDK::Vector(randflxy, randflxy, randflz));
					g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
					if (tr.fraction == 1.f || tr.m_pEnt == this) return tr.endpos;
					else
						return vCenter;
				}
			}

			return vCenter;
		}
		Vector GetVelocity( void )
		{
			return *( Vector* )( ( DWORD )this + Offsets::m_vecVelocity );
		}
		QAngle GetViewPunch( void )
		{
			return *( QAngle* )( ( DWORD )this + Offsets::m_viewPunchAngle );
		}
		QAngle GetAimPunch( void )
		{
			return *( QAngle* )( ( DWORD )this + Offsets::m_aimPunchAngle );
		}
		CBaseViewModel* GetViewModel( void ) 
		{
			return ( CBaseViewModel* )g_pEntityList->GetBaseEntityFromHandle( *( PDWORD )( ( DWORD )this + Offsets::m_hViewModel ) );
		}
		int GetHitboxSet(void)
		{
			return *( int* )( ( DWORD )this + Offsets::m_nHitboxSet );
		}
	};
	/*class CBaseViewModel
	{
	public:
		int GetModelIndex( void ) 
		{
			return *(int*)((DWORD)this + Offsets::m_nModelIndex);
		}

		DWORD GetOwner( void ) 
		{
			return *(PDWORD)((DWORD)this + Offsets::m_hOwner);
		}

		DWORD GetWeapon( void ) {
			return *(PDWORD)((DWORD)this + Offsets::m_hWeapon);
		}

		void SetWeaponModel(const char* Filename, CBaseEntity* Weapon)
		{
			VirtualFn( void )(PVOID, const char*, CBaseEntity*);
			CallVirtual< OriginalFn >(this, 241)(this, Filename, Weapon);
		}
	};
	*/
	class PlayerData
	{
	public:
		bool		m_bActive;					// enable list for this player
		std::string	m_strName;					// entity name
		int			m_iIndex;					// entity index
		bool		m_bFriend;					// Is a friend? ignore him
		int			m_iCustomHitbox;			// Custom aim hitbox
		int			m_iCustomSmartAim;			// Number of bullets needed to enable smart aim
		int			m_iCustomSmartAimHitbox;	// Custom aim smart hitbox
		int			m_iTotalHits;				// Number of total hits
		int			m_iTotalMisses;				// Number of total misses
		int			m_iCurrentHits;				// current shots hit since last change
		int			m_iCurrentMisses;			// current shots missed since the last change
		float		m_flPitch;					// custom pitch
		float		m_flYaw;					// custom yaw

	public:
		void Reset( void )
		{
			m_bActive = false;
			m_strName.clear( );
			m_iIndex = 0;
			m_bFriend = false;
			m_iCustomHitbox = 0;
			m_iCustomSmartAim = 0;
			m_iCustomSmartAimHitbox = 0;
			m_iTotalHits = 0;
			m_iTotalMisses = 0;
			m_iCurrentHits = 0;
			m_iCurrentMisses = 0;
			m_flPitch = 0.f;
			m_flYaw = 0.f;
		}
	};
	inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
	{
		if (nGrowSize)
			nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
		else
		{
			if (!nAllocationCount)
				nAllocationCount = (31 + nBytesItem) / nBytesItem;

			while (nAllocationCount < nNewSize)
				nAllocationCount *= 2;
		}

		return nAllocationCount;
	}

	template< class T, class I = int >
	class CUtlMemory
	{
	public:
		T& operator[](I i)
		{
			return m_pMemory[i];
		}

		T* Base()
		{
			return m_pMemory;
		}

		int NumAllocated() const
		{
			return m_nAllocationCount;
		}

		void Grow(int num = 1)
		{
			if (IsExternallyAllocated())
				return;

			int nAllocationRequested = m_nAllocationCount + num;
			int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

			if ((int)(I)nNewAllocationCount < nAllocationRequested)
			{
				if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
					--nNewAllocationCount;
				else
				{
					if ((int)(I)nAllocationRequested != nAllocationRequested)
						return;

					while ((int)(I)nNewAllocationCount < nAllocationRequested)
						nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
				}
			}

			m_nAllocationCount = nNewAllocationCount;

			if (m_pMemory)
				m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
			else
				m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
		}

		bool IsExternallyAllocated() const
		{
			return m_nGrowSize < 0;
		}

	protected:
		T* m_pMemory;
		int m_nAllocationCount;
		int m_nGrowSize;
	};

	template <class T>
	inline T* Construct(T* pMemory)
	{
		return ::new(pMemory) T;
	}

	template <class T>
	inline void Destruct(T* pMemory)
	{
		pMemory->~T();
	}
	template< class T, class A = CUtlMemory<T> >
	class CUtlVector
	{
		typedef A CAllocator;
	public:
		T& operator[](int i)
		{
			return m_Memory[i];
		}

		T& Element(int i)
		{
			return m_Memory[i];
		}

		T* Base()
		{
			return m_Memory.Base();
		}

		int Count() const
		{
			return m_Size;
		}

		void RemoveAll()
		{
			for (int i = m_Size; --i >= 0; )
				Destruct(&Element(i));

			m_Size = 0;
		}

		int AddToTail()
		{
			return InsertBefore(m_Size);
		}

		int InsertBefore(int elem)
		{
			GrowVector();
			ShiftElementsRight(elem);
			Construct(&Element(elem));

			return elem;
		}

	protected:
		void GrowVector(int num = 1)
		{
			if (m_Size + num > m_Memory.NumAllocated())
				m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());

			m_Size += num;
			ResetDbgInfo();
		}

		void ShiftElementsRight(int elem, int num = 1)
		{
			int numToMove = m_Size - elem - num;
			if ((numToMove > 0) && (num > 0))
				memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
		}

		CAllocator m_Memory;
		int m_Size;

		T* m_pElements;

		inline void ResetDbgInfo()
		{
			m_pElements = Base();
		}
	};
	class CGlowObjectManager
	{
	public:

		int RegisterGlowObject(CBaseEntity *pEntity, const Color &GlowColor, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot)
		{
			int nIndex;
			if (m_nFirstFreeSlot == GlowObjectDefinition_t::END_OF_FREE_LIST)
			{
				nIndex = m_GlowObjectDefinitions.AddToTail();
			}
			else
			{
				nIndex = m_nFirstFreeSlot;
				m_nFirstFreeSlot = m_GlowObjectDefinitions[nIndex].m_nNextFreeSlot;
			}

			m_GlowObjectDefinitions[nIndex].m_hEntity = pEntity;
			m_GlowObjectDefinitions[nIndex].m_vGlowColor = Vector((float)GlowColor.r() / 255.0f, (float)GlowColor.g() / 255.0f, (float)GlowColor.b() / 255.0f);
			m_GlowObjectDefinitions[nIndex].m_flGlowAlpha = (float)GlowColor.a() / 255.f;
			m_GlowObjectDefinitions[nIndex].flUnk = 0.0f;
			m_GlowObjectDefinitions[nIndex].m_flBloomAmount = 1.0f;
			m_GlowObjectDefinitions[nIndex].localplayeriszeropoint3 = 0.0f;
			m_GlowObjectDefinitions[nIndex].m_bRenderWhenOccluded = bRenderWhenOccluded;
			m_GlowObjectDefinitions[nIndex].m_bRenderWhenUnoccluded = bRenderWhenUnoccluded;
			m_GlowObjectDefinitions[nIndex].m_bFullBloomRender = false;
			m_GlowObjectDefinitions[nIndex].m_nFullBloomStencilTestValue = 0;
			m_GlowObjectDefinitions[nIndex].m_nSplitScreenSlot = nSplitScreenSlot;
			m_GlowObjectDefinitions[nIndex].m_nNextFreeSlot = GlowObjectDefinition_t::ENTRY_IN_USE;

			return nIndex;
		}

		void UnregisterGlowObject(int nGlowObjectHandle)
		{
			if (!m_GlowObjectDefinitions[nGlowObjectHandle].IsUnused())
				return;

			m_GlowObjectDefinitions[nGlowObjectHandle].m_nNextFreeSlot = m_nFirstFreeSlot;
			m_GlowObjectDefinitions[nGlowObjectHandle].m_hEntity = NULL;
			m_nFirstFreeSlot = nGlowObjectHandle;
		}

		int HasGlowEffect(CBaseEntity* pEntity)
		{
			for (int i = 0; i < m_GlowObjectDefinitions.Count(); ++i)
			{
				if (!m_GlowObjectDefinitions[i].IsUnused() && m_GlowObjectDefinitions[i].m_hEntity == pEntity)
					return i;
			}

			return NULL;
		}

		class GlowObjectDefinition_t
		{
		public:
			void Set(Color color)
			{
				m_vGlowColor = Vector((float)color.r() / 255.0f, (float)color.g() / 255.0f, (float)color.b() / 255.0f);
				m_flGlowAlpha = (float)color.a() / 255.0f;
				m_bRenderWhenOccluded = true;
				m_bRenderWhenUnoccluded = false;
				m_flBloomAmount = 1.0f;
			}

			CBaseEntity* GetEnt()
			{
				return m_hEntity;
			}

			bool IsUnused() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

		public:
			CBaseEntity*    m_hEntity;
			Vector            m_vGlowColor;
			float            m_flGlowAlpha;

			char            unknown[4]; //pad 
			float            flUnk; //confirmed to be treated as a float while reversing glow functions 
			float            m_flBloomAmount;
			float            localplayeriszeropoint3;


			bool            m_bRenderWhenOccluded;
			bool            m_bRenderWhenUnoccluded;
			bool            m_bFullBloomRender;
			char            unknown1[1]; //pad 


			int                m_nFullBloomStencilTestValue; // 0x28 
			int                iUnk; //appears like it needs to be zero  
			int                m_nSplitScreenSlot; //Should be -1 

												   // Linked list of free slots 
			int                m_nNextFreeSlot;

			// Special values for GlowObjectDefinition_t::m_nNextFreeSlot 
			static const int END_OF_FREE_LIST = -1;
			static const int ENTRY_IN_USE = -2;
		};

		CUtlVector< GlowObjectDefinition_t > m_GlowObjectDefinitions;
		int m_nFirstFreeSlot;
	};
	class CTools
	{
	private:
		PlayerData	m_PlayerData[ 128 ];

	public:
		CTools(void);
		void			ClampMovement(CUserCmd *pCmd);
		ULONG			FindPatternAlt(std::string szModuleName, PBYTE pbPattern, std::string szMask, ULONG uCodeBase, ULONG uSizeOfCode);
		void			Normalize(ValveSDK::Vector &vIn, ValveSDK::Vector &vOut);
		void			VectorTransform(Vector& in1, matrix3x4a_t& in2, Vector &out);
		void			AngleVectors(const ValveSDK::Vector &angles, ValveSDK::Vector *forward, ValveSDK::Vector *right, ValveSDK::Vector *up);
		bool 			GetHitboxVector(CBaseEntity* pBaseEntity, int iHitbox, Vector& vecHitbox);
		bool			IsAbleToShoot(CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon);
		bool			IsBreakableEntity(CBaseEntity* pBaseEntity);
		bool			IsVisible(Vector& StartPos, Vector& EndPos, CBaseEntity* localPly, CBaseEntity* pEnt);
		bool            IsVisibles(int bone, CBaseEntity* pLocal, CBaseEntity* pEntity);
		bool 			TraceDidHitWorld(IEngineTrace::trace_t* pTrace);
		bool 			TraceDidHitNonWorldEntity(IEngineTrace::trace_t* pTrace);
		bool			TraceToExit(Vector& vecEnd, IEngineTrace::trace_t* pEnterTrace, Vector vecStart, Vector vecDir, IEngineTrace::trace_t* pExitTrace);
		bool			WorldToScreen(const Vector& vecOrigin, Vector& vecScreen);
		CBaseEntity*	GetLocalPlayer(void);
		DWORD_PTR		FindPattern(std::string strModuleName, PBYTE pbPattern, std::string strMask, DWORD_PTR nCodeBase = 0, DWORD_PTR nSizeOfCode = 0);
		float			DotProduct(const float *v1, const float *v2);
		float			DotProduct(const Vector& v1, const Vector& v2);
		float			GetDistance(const Vector& vecOrigin, const Vector& vecOther);
		//float			GetFoV(QAngle qAngles, Vector vecSource, Vector vecDestination, bool bDistanceBased = false);
		float			GetFoV(const QAngle& qViewAngle, const QAngle& qAimAngle);
		float			GetHitgroupDamageMult(int iHitgroup);
		IMaterial*		CreateMaterial(bool bFullbright, bool bIgnorez);
		IMaterial*		CreateMaterial(bool bShouldIgnoreZ, bool bFullBright, bool bIsWireframe);
		mstudiobbox_t*	GetHitboxData(CBaseEntity* pBaseEntity, int iHitbox);
		bool			GetHitboxVector2(CBaseEntity* target, int iBone, Hitbox* hitbox);
		PlayerData*		GetPlayerData(int iIndex);
		QAngle			GetAntiAimAngles(CBaseEntity* pBaseEntity, bool bEnemyOnly = true);
		void			AngleVectors(const QAngle& qAngles, Vector& vecForward);
		void			AngleVectors2(const QAngle & qAngles, Vector& vecForward, Vector& vecRight, Vector& vecUp);
		void 			CalcAngle(const Vector& vecSource, const Vector& vecDestination, QAngle& qAngles);
		void 			ClampAngles(QAngle& qAngles);
		void 			UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, CBaseEntity* pCSIgnore, IEngineTrace::trace_t* pTrace);
		void 			ForceFullUpdate(void);
		void			ForceMaterial(Color color, IMaterial* material, bool useColor = true, bool forceMaterial = true);
		void 			MakeVector(QAngle qAngles, Vector& vecOut);
		void			MatrixToVector(const matrix3x4_t& pMatrix, Vector& out);
		void			NormalizeVector(Vector& vecIn);
		void 			ScaleDamage(int iHitgroup, CBaseEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage);
		void 			SinCos(float flRadians, float* pflSine, float* pflCosine);
		void			VectorAngles(const Vector &vecForward, Vector &vecAngles);
		void 			VectorTransform(const float *in1, const matrix3x4_t& in2, float *out);
		void 			VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
		void			ClearPlayerData(void);
		void			RandomSeed( UINT Seed );
		float			RandomFloat(float fMin, float fMax);
		bool			GetHitboxPosition(CBaseEntity* pBaseEntity, int iHitBox, Vector& vOut);
		float			GetFov(ValveSDK::Vector ViewOffSet, ValveSDK::Vector View, ValveSDK::CBaseEntity* pEntity, int aHitBox);
		void			NormalizeDelta(ValveSDK::Vector &vIn, ValveSDK::Vector &vOut);
		bool			IsValids(int iEnt, ValveSDK::CBaseEntity* pLocal,ValveSDK::CUserCmd *pCmd);
		bool			NonVisIsValid(int iEnt, ValveSDK::CBaseEntity* pLocal);
		int				AATARGE(ValveSDK::CUserCmd *pCmd, ValveSDK::CBaseEntity* pLocalEntity, ValveSDK::CBaseCombatWeapon* pWeapon);
		bool			IsValidTARGET(int iEnt, ValveSDK::CBaseEntity* pLocal);

	};
}

#endif

/*COPY PASTES!!!*/


///NoSpread
/*
float fRand1 = RandomFloat( 0.f, 1.f ); // the game does some checks here, didn't bother to see if they ever return false 
float fRandPi1 = RandomFloat( 0.f, 2.f * (float) M_PI ); 
float fRand2 = RandomFloat( 0.f, 1.f ); // the game does some checks here, didn't bother to see if they ever return false 
float fRandPi2 = RandomFloat( 0.f, 2.f * (float) M_PI ); 

float fRandInaccuracy = fRand1 * pWeapon->GetInaccuracy(); 
float fRandSpread = fRand2 * pWeapon->GetSpread(); 

float fSpreadX = cos( fRandPi1 ) * fRandInaccuracy + cos( fRandPi2 ) * fRandSpread; 
float fSpreadY = sin( fRandPi1 ) * fRandInaccuracy + sin( fRandPi2 ) * fRandSpread;
*/