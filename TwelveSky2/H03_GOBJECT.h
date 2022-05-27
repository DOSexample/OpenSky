#pragma once

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GIMAGE2D
//-------------------------------------------------------------------------------------------------
//DEFINE
class GIMAGE2D
{

private :

	char mFileName[100];
	float mLastUsedTime;

public :

	BOOL mCheckValidState;
	IMAGE_FOR_GXD mDATA;

	GIMAGE2D( void );

	void Init( int tValue01, int tValue02, int tValue03 );
	void Free( void );

	BOOL Load( void );
	int GetTwoPowerNumber( int tNumber );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	void Display( int sX, int sY );
	void Display( int sX, int sY, WORD iX, WORD iY, WORD lX, WORD lY );
	void Display( int sX, int sY, float tScaleX, float tScaleY );
	BOOL CheckIn( int sX, int sY, int mX, int mY );
	BOOL CheckIn( int sX, int sY, int mWidth, int mHeight, int mX, int mY );
	WORD GetXSize( void );
	WORD GetYSize( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GOBJECT
//-------------------------------------------------------------------------------------------------
//DEFINE
template<typename T>
class GOBJECT
{
public:

	GOBJECT( void )
	{
		mCheckValidState = FALSE;
		mFileName[0] = '\0';
	}
	~GOBJECT( void )
	{
		Free();
	}

	BOOL mCheckValidState;
	char mFileName[100];
	T mDATA;
	float mLastUsedTime;
	
	void Init( char* tFileName )
	{
		mCheckValidState = FALSE;
		mDATA.Init();
		sprintf( mFileName, "%s", tFileName );
	}

	void Free( void )
	{
		mCheckValidState = FALSE;
		mDATA.Free();
	}

	BOOL Load( BOOL isLocalClient )
	{
		return FALSE;
	}
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GMOBJECT
//-------------------------------------------------------------------------------------------------
//DEFINE
class GMOBJECT : private GOBJECT<MOBJECT_FOR_GXD>
{

public :

	GMOBJECT( void );

	void Init( int tValue01, int tValue02, int tValue03, int tValue04 );
	void Free( void );

	BOOL Load( BOOL isLocalClient );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	int GetTotalFrameNum( void );
	MESHSIZE_FOR_GXD * GetMI( int tMeshIndex, float pFrame );
	BOOL GetBoundingInfo( float pFrame, float tL[3], float tA[3], MESHSIZE_FOR_GXD tMI[1] );
	void DisplayMObject( int tDrawSort, float pFrame, float tL[3], float tA[3] );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GEFFECT
//-------------------------------------------------------------------------------------------------
//DEFINE
#define MAX_GEFFECT_NUM				10
class GEFFECT
{

private :

	float mLastUsedTime;

public :

	BOOL mCheckValidState;
	EFFECTGROUP_FOR_GXD mDATA;

	GEFFECT( void );

	void InitProjectile( char *tFileName );
	void InitMotionEffect( char *tFileName );
	void InitSkillEffect( char *tFileName );
	void InitNPCEffect( char *tFileName );
	void InitShadowEffect( BYTE tIndex );
	void InitMonsterSkillEffect( char *tFileName, USHORT tJob );
	void InitBaseEffect( USHORT tIndex );
	void InitQuestEffect( USHORT tIndex );
	void InitRoutingEffect( USHORT tIndex );
	void InitChariotsEffect( char *tFileName );
	void InitCreateAvatarEffect( char *tFileName );
	void InitVendorEffect( USHORT tIndex );
	void Init( int tValue01, int tValue02, int tValue03, int tValue04 );
	BOOL Init();
	void Free( BOOL bClear = TRUE );

	BOOL Load( void );
	BOOL CopyFrom( GEFFECT *tEffect );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	int GetTotalFrameNum( void );
	//	MESHSIZE_FOR_GXD * GetMI( int tMeshIndex, float pFrame );
	BOOL GetBoundingInfo( float pFrame, float tL[3], float tA[3], MESHSIZE_FOR_GXD tMI[1] );
//	void DisplayEffect( int tDrawSort, float pFrame, float tL[3], float tA[3] );

	void Update( SOBJECT_FOR_GXD *pSObjectDummy, MOTION_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
//	void Update2( SOBJECT2_FOR_GXD *pSObjectDummy, MOTION2_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void ReStart( void );
	void DisplayPObject( void );
	void DisplayMObject( BYTE tSort );
	void Display( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GMOTION
//-------------------------------------------------------------------------------------------------
//DEFINE
class GMOTION : private GOBJECT<TW2AddIn::MOTION2_FOR_GXD>
{

private :

	int mFrameNum;

public :


	GMOTION( void );

	void Init( int tValue01, int tValue02, int tValue03, int tValue04, int tValue05 );
	void Free( void );

	BOOL Load( BOOL isLocalClient );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	int GetTotalFrameNum( void );
	//BOOL UseForSObject( void );
	TW2AddIn::MOTION2_FOR_GXD * GetMotionPointer( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GSOBJECT
//-------------------------------------------------------------------------------------------------
//DEFINE
class GSOBJECT : private GOBJECT<TW2AddIn::SOBJECT2_FOR_GXD>
{

public :

	GSOBJECT( void );

	void Init( int tValue01, int tValue02, int tValue03, int tValue04, int tValue05, int tValue06 );
	void Free( void );

	BOOL Load( BOOL isLocalClient );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	void GetSObjectCoord( int tSkinIndex, float tCoord[3], float pFrame, float tL[3], float tYAngle, float tScale[3], GMOTION *tMOTION );
	void DisplaySObjectShadow( float pFrame, float tL[3], float tXAngle, float tYAngle, float tHeightForCulling, void *tWORLD, GMOTION *tMOTION, float tScale[3], int iType = 0 );
	void DisplaySObject( int tDrawSort, float pFrame, float tL[3], float tXAngle, float tYAngle, float tHeightForCulling, GMOTION *tMOTION, float tScale = 1.0f );
	void DisplaySObjectForEffect( int tDrawSort, TW2AddIn::TEXTURE_FOR_GXD *tTEXTURE, float pFrame, float tL[3], float tYAngle, float tHeightForCulling, GMOTION *tMOTION );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GSOBJECT_OLD
//-------------------------------------------------------------------------------------------------
//DEFINE
class GSOBJECT_OLD : private GOBJECT<SOBJECT_FOR_GXD>
{

public :

	GSOBJECT_OLD( void );

	void Init( int tValue01, int tValue02, int tValue03, int tValue04, int tValue05, int tValue06 );
	void Free( void );

	BOOL Load( BOOL isLocalClient );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	void GetSObjectCoord( int tSkinIndex, float tCoord[3], float pFrame, float tL[3], float tYAngle, float tScale[3], GMOTION *tMOTION );
	void DisplaySObjectShadow( float pFrame, float tL[3], float tXAngle, float tYAngle, float tHeightForCulling, void *tWORLD, GMOTION *tMOTION, float tScale[3], int iType = 0 );
	void DisplaySObject( int tDrawSort, float pFrame, float tL[3], float tXAngle, float tYAngle, float tHeightForCulling, GMOTION *tMOTION, float tScale = 1.0f );
	void DisplaySObjectForEffect( int tDrawSort, TEXTURE_FOR_GXD *tTEXTURE, float pFrame, float tL[3], float tYAngle, float tHeightForCulling, GMOTION *tMOTION );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GSOUND
//-------------------------------------------------------------------------------------------------
//DEFINE
class GSOUND : private GOBJECT<SOUNDDATA_FOR_GXD>
{

public :

	GSOUND( void );

	void Init( int tValue01, int tValue02, int tValue03, int tValue04, int tValue05 );
	void Free( void );

	BOOL Load( void );

	void ProcessForMemory( float tPresentTime, float tValidTimeLength );

	void Play( BOOL tCheckLoop, int tVolumeSize );
	void Play( void );
	void Play( float tSourceLocation[3], float tPostCoord[3] );
	void Stop( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_GSOUND
//-------------------------------------------------------------------------------------------------
//DEFINE
#define MAX_OLD_TRIBE_NUM											3
#define MAX_GIMAGE2D_UI_MAIN_NUM									4500
#define MAX_GIMAGE2D_UI_ITEM_NUM									3300
#define MAX_GIMAGE2D_UI_ICON_NUM									760
#define MAX_GIMAGE2D_UI_SKILL_INFO_NUM								150
#define MAX_GIMAGE2D_UI_HELP_NUM									999
#define MAX_GIMAGE2D_UI_SKILL_ICON_NUM								35
#define MAX_GIMAGE2D_UI_LOAD_NUM									350
class GDATA
{

public:
	MOTION_FOR_GXD mBlankMotion1;
	TW2AddIn::MOTION2_FOR_GXD mBlankMotion2;
	GIMAGE2D mUI_MAIN[MAX_GIMAGE2D_UI_MAIN_NUM];
	GIMAGE2D mUI_ITEM[MAX_GIMAGE2D_UI_ITEM_NUM];
	GIMAGE2D mUI_ICON[MAX_GIMAGE2D_UI_ICON_NUM];
	GIMAGE2D mUI_SKILLINFO[MAX_GIMAGE2D_UI_SKILL_INFO_NUM];
	GIMAGE2D mUI_HELP[MAX_GIMAGE2D_UI_HELP_NUM];
	GIMAGE2D mUI_BUFFICON[MAX_OLD_TRIBE_NUM][MAX_GIMAGE2D_UI_SKILL_ICON_NUM];
	GIMAGE2D mUI_LOAD[MAX_GIMAGE2D_UI_LOAD_NUM];

	GDATA( void );

	BOOL Init( void );
	void Free( void );
};
extern GDATA mGDATA;
//-------------------------------------------------------------------------------------------------
