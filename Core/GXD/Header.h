#pragma once

#include <ShareHeader.h>
#include "WorldMobjectScale.h"

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MOTION_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MOTION_FOR_GXD
{
public:

	BOOL mCheckValidState;
	int mFrameNum;
	int mBoneNum;
	D3DXMATRIX* mKeyMatrix;

	void Init( void );
	BOOL Free( void );

	BOOL LoadFromG3M( char *tFileName, int tLoadSort );
	BOOL Save( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char *tFileName );
	BOOL Load( HANDLE hFile, BOOL tNeedCheckValid = TRUE );

	BOOL SaveToMOTION2( char *tFileName );

};

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_BUMPEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
struct BUMPEFFECT_FOR_GXD
{
	DWORD		dwPass;
	float		fAmdPower;
	float		fSpecPower;
	int			iMetrialType;
	BUMPEFFECT_FOR_GXD( )
		:dwPass( 0L),
		fAmdPower( 2.0f),
		fSpecPower( 20.0f),
		iMetrialType( 0)
	{
	}
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SKIN_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SKIN_FOR_GXD
{

private :

	SKINVERTEX_FOR_GXD mVertexBufferForBillboard[4];

	BOOL mCheckChangeNormalState;

public :

	BOOL mCheckValidState;
	SKINEFFECT_FOR_GXD mEffect;
	int mVertexNum;
	int mUVNum;
	int mWeightNum;
	int mTrisNum;
	float *mVertex;
	float *mNormal;
	float *mUV;
	float *mWeight;
	WORD *mTris;
	SKINSIZE_FOR_GXD mSize;
	SKINVERTEX_FOR_GXD* mVertexBuffer;
	SKINWEIGHT_FOR_GXD* mWeightBuffer;
	WORD* mIndexBuffer;
	float* mMotionVertex;
	float* mMotionNormal;
	TEXTURE_FOR_GXD mTexture[2];
	int mTextureAnimationNum;
	TEXTURE_FOR_GXD *mTextureAnimation;

	void Init( void );
	BOOL Free( void );
	
	BOOL LoadFromG3S( char *tFileName, char *tTextureName );
	BOOL ChangeStructureForAcceleration( void );
	BOOL Save( HANDLE hFile );
	BOOL SaveForLOD( HANDLE hFile, float a3 );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL LoadOnlyPolygon( HANDLE hFile );
	BOOL LoadOnlyTexture( HANDLE hFile );
	void CreateTexture( BOOL tCheckRemoveFileData );
	void DeleteTexture( void );
	BOOL ProcessInvertNormal( void );
	BOOL ProcessTwoSide( BOOL tCheckTwoSide );
	BOOL ProcessRadiation( BOOL tCheckRadiation, float tRadiationSpeed, float tRadiationLowLimit[4], float tRadiationHighLimit[4] );
	BOOL ProcessLightBright( BOOL tCheckLightBright );
	BOOL ProcessCameraSpecularEffect( BOOL tCheckCameraSpecularEffect, int tCameraSpecularEffectSort, float tCameraSpecularEffectMaterialValue[4], float tCameraSpecularEffectMaterialPower, float tCameraSpecularEffectLightAddValue );
	BOOL CreateWithBlankTextureAnimation( int tTextureAnimationNum );
	BOOL ProcessTextureAnimation( BOOL tCheckTextureAnimation, float tTextureAnimationSpeed );
	BOOL ProcessUVScroll1( BOOL tCheckUVScroll1, int tUVScrollSort1, float tUVScrollSpeed1 );
	BOOL ProcessBillboard( BOOL tCheckBillboard, int tBillboardSort );
	BOOL ProcessUVScroll2( BOOL tCheckUVScroll2, int tUVScrollSort2, float tUVScrollSpeed2 );

	void Draw( int tFrame, float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture,
		MOTION_FOR_GXD* tMotion, BOOL tCheckDrawCameraSpecularEffect, void* tWorld,
		BOOL tCheckCalculateNormal
	);
	void DrawForSelect( void );

	void GetCenterCoord( float tCoord[3] );
};

class SOBJECT_FOR_GXD
{
public:
	BOOL mCheckValidState;
	int mSkinNum;
	SKIN_FOR_GXD* mSkin;

	SOBJECT_FOR_GXD( void );
	~SOBJECT_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL CreateWithBlankSkin( int tSkinNum );
	BOOL Save( char *tFileName );
	BOOL SaveForLOD( char *lpFileName, float a3 );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL LoadOnlyPolygon( char *tFileName );
	void LoadOnlyTexture( char *tFileName );
	void CreateTexture( BOOL tCheckRemoveFileData );
	void DeleteTexture( void );


	void Draw( 
		int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, 
		BOOL tCheckDrawCameraSpecularEffect, MOTION_FOR_GXD *tMotion, float tRangeForCulling, BOOL tCheckShadow, void *tWorld, BOOL tCheckCalculateNormal
	);
	void DrawForSelect( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tRangeForCulling );
	
	void DrawForLOD( 
		int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, 
		MOTION_FOR_GXD *tMotion, float tRangeForCulling, BOOL tCheckShadow, void *tWorld, BOOL tCheckCalculateNormal, SOBJECT_FOR_GXD* tOther
	);


	void GetSkinCoord( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tSkinCoord[3] );

};


//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_ONE_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _ONE_MESHINFO_FOR_MULTIDRAW
{
	D3DXVECTOR3 vCenter;
	FLOAT fRadius;
	BOOL bIsDraw;
	_ONE_MESHINFO_FOR_MULTIDRAW( )
	:fRadius( 0.0f)
	,bIsDraw( TRUE)
	{
		ZeroMemory( &vCenter , sizeof( D3DXVECTOR3) );
	}
}
ONE_MESHINFO_FOR_MULTIDRAW;
typedef ONE_MESHINFO_FOR_MULTIDRAW* LPONE_MESHINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_ONE_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _ONE_MOBJECTINFO_FOR_MULTIDRAW
{
	float fFrame;
	float fPostTimeForEffect;
	float fMaxScaleRate;
	D3DXMATRIX MObjectMat;	
	D3DXMATRIX ScaletMat;	
	D3DXMATRIX RotationMat;	
	D3DXMATRIX TransMat;	
	LPONE_MESHINFO_FOR_MULTIDRAW pMeshInfo;
	_ONE_MOBJECTINFO_FOR_MULTIDRAW( )
	:fFrame( 0.0f)
	,fPostTimeForEffect( 0.0f)
	,fMaxScaleRate( 1.0f)
	,pMeshInfo( NULL)
	{
		D3DXMatrixIdentity( &MObjectMat );
		D3DXMatrixIdentity( &ScaletMat );
		D3DXMatrixIdentity( &RotationMat );
		D3DXMatrixIdentity( &TransMat );
	}
}
ONE_MOBJECTINFO_FOR_MULTIDRAW;
typedef ONE_MOBJECTINFO_FOR_MULTIDRAW* LPONE_MOBJECTINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _MOBJECTINFO_FOR_MULTIDRAW
{
	WORD wMObjectNum;
	LPONE_MOBJECTINFO_FOR_MULTIDRAW pOneMObjectInfo;
	_MOBJECTINFO_FOR_MULTIDRAW( )
	:wMObjectNum( 0)
	,pOneMObjectInfo( NULL)
	{
	}
}
MOBJECTINFO_FOR_MULTIDRAW;
typedef MOBJECTINFO_FOR_MULTIDRAW* LPMOBJECTINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MESH_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MESH_FOR_GXD
{
public :
	
	MESHVERTEX_FOR_GXD mVertexBufferForBillboard[4];
	BOOL mCheckValidState;
	MESHEFFECT_FOR_GXD mEffect;
	int mFrameNum;
	int mVertexNum;
	int mUVNum;
	int mTrisNum;
	float *mVertex;
	float *mNormal;
	float *mUV;
	WORD *mTris;
	MESHSIZE_FOR_GXD *mSize;
	IDirect3DVertexBuffer9 *mVertexBuffer;
	IDirect3DIndexBuffer9 *mIndexBuffer;
	TEXTURE_FOR_GXD mTexture[2];
	int mTextureAnimationNum;
	TEXTURE_FOR_GXD *mTextureAnimation;

	MESH_FOR_GXD( void );
    ~MESH_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromG3O( char *tFileName, char *tTextureName );
	BOOL CalculateOneFrameMeshSize( MESHSIZE_FOR_GXD *tSize, int tVertexNum, float *tVertex );
	BOOL ChangeStructureForAcceleration( void );
	BOOL Save( HANDLE hFile, WORD wMajorVersion, WORD wMinorVersion );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL ProcessInvertNormal( void );
	BOOL ProcessTwoSide( BOOL tCheckTwoSide );
	BOOL ProcessRadiation( BOOL tCheckRadiation, float tRadiationSpeed, float tRadiationLowLimit[4], float tRadiationHighLimit[4] );
	BOOL ProcessLightBright( BOOL tCheckLightBright );
	BOOL ProcessCameraSpecularEffect( BOOL tCheckCameraSpecularEffect, int tCameraSpecularEffectSort, float tCameraSpecularEffectMaterialValue[4], float tCameraSpecularEffectMaterialPower, float tCameraSpecularEffectLightAddValue );
	BOOL CreateWithBlankTextureAnimation( int tTextureAnimationNum );
	BOOL ProcessTextureAnimation( BOOL tCheckTextureAnimation, float tTextureAnimationSpeed );
	BOOL ProcessUVScroll1( BOOL tCheckUVScroll1, int tUVScrollSort1, float tUVScrollSpeed1 );
	BOOL ProcessBillboard( BOOL tCheckBillboard, int tBillboardSort );
	BOOL ProcessUVScroll2( BOOL tCheckUVScroll2, int tUVScrollSort2, float tUVScrollSpeed2 );
	void Draw( int tFrame, float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, TEXTURE_FOR_GXD *tNormalTexture, TEXTURE_FOR_GXD *tSpeculerTexture, BOOL tCheckDrawCameraSpecularEffect, BYTE tBlendValue, LPD3DXMATRIX pScaleMat = NULL, LPD3DXMATRIX pRotationMat = NULL, LPD3DXMATRIX pTransMat = NULL );
	void Draw( int tFrame, float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, BYTE tBlendValue );

	void MultiDraw( WORD wMeshIndex , LPMOBJECTINFO_FOR_MULTIDRAW MultiDrawInfo, TEXTURE_FOR_GXD *tTexture , TEXTURE_FOR_GXD *tNormalTexture , TEXTURE_FOR_GXD *tSpeculerTexture , BOOL tCheckDrawCameraSpecularEffect );
	//--------------------------------------------------------------------------------------------------------------------

	void DrawForShadow( int tFrame, TEXTURE_FOR_GXD *tTexture );
	void DrawForSelect( int tFrame );
	BOOL LoadGeometryInfo( void );
	void FreeGeometryInfo( void );
	BOOL GetSizeInfo( int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MOBJECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MOBJECT_FOR_GXD
{

//private :
//
//	D3DXVECTOR3 mScaleValue;	/** Scaling 정보 */
//
//	float GetMaxScaleValue_( );	/** Scaling 정보( Scale_X, Scale_Y, Scale_Z) 중 가장 큰 값을 반환하는 함수. */

public :

	BOOL mCheckValidState;
	//WORD    m_wMajorVersion;
	//WORD    m_wMinorVersion;
	int mMeshNum;
	MESH_FOR_GXD *mMesh;
	MESHSIZE_FOR_GXD *mSize;
	HANDLE mFile;


	MOBJECT_FOR_GXD( void );
    ~MOBJECT_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL CreateWithBlankMesh( int tMeshNum );
	BOOL Save( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData , LPWORD pLoadIndexes , WORD wLoadCount );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData, BOOL tNeedCheckValid = TRUE );
	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, BYTE tBlendValue );


	void MultiDraw( int tDrawSort, LPMOBJECTINFO_FOR_MULTIDRAW MultiDrawInfo, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect  );

	void DrawForShadow( float tFrame, float tCoord[3], float tAngle[3] );
	void DrawForSelect( int tSelectMeshIndex, float tFrame, float tCoord[3], float tAngle[3] );
	BOOL GetMeshSize( float tFrame, float tCoord[3], float tAngle[3] );

	BOOL TestCameraInMObject( float tFrame, float tCoord[3], float tAngle[3], float tCameraLook[3], float tCameraEye[3] );
	BOOL SetScale( float x, float y, float z );
	BOOL GetMeshSizeAfterScale( int tMeshIndex, int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );
	BOOL GetMeshSizeBeforeScale( int tMeshIndex, int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );
	D3DXVECTOR3 GetScaleValue( );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_PSYSTEM_FOR_GXD
//-------------------------------------------------------------------------------------------------
class PSYSTEM_FOR_GXD
{

public :

	BOOL mCheckValidState;
	TEXTURE_FOR_GXD mTexture;
	MOTION_FOR_GXD mMotion;
	float mTotalLifeTime;
	float mFrameRatio;
	float mEmitRate;
	float mEmitSort;
	float mEmitRadius;
	float mEmitRange[3];
	float mOneLifeTime;
	float mMinRandomVelocity[3];
	float mMaxRandomVelocity[3];
	float mWeight;
	float mSize;
	float mMinColor[4];
	float mMaxColor[4];
	float mMainForce[3];
	float mMinRandomForce[3];
	float mMaxRandomForce[3];
	float mWeightDelta;
	float mSizeDelta;
	float mColorDelta[4];

	PSYSTEM_FOR_GXD( void );
   ~PSYSTEM_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Save( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void Adjust( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_POBJECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
class POBJECT_FOR_GXD
{
private :
	D3DXVECTOR3 mScaleValue;

public :

	BOOL mCheckValidState;
	PSYSTEM_FOR_GXD *mPSystem;
	float mTotalLifeTime;
	float mCoord[3];
	float mAngle[3];
	float mEmitParticleNum;
	int mMaxParticleNum;
	PARTICLE_FOR_GXD *mParticle;

	POBJECT_FOR_GXD( void );
   ~POBJECT_FOR_GXD( void );

	void Init( void );
	void Free( void );

	void Set( PSYSTEM_FOR_GXD *tPSystem );
	void Update( float tTime, float tCoord[3], float tAngle[3] );
	void Draw( void );

	const D3DXVECTOR3& GetScale() const;
	BOOL SetScale( float x, float y, float z );
};
//-------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//CLASS_OF_EFFECT_FOR_GXD
//-----------------------------------------------------------------------------------------------
#define DEF_SIZE_BUFFER												64
#define DEF_LEN_FILE_NAME											256
struct EF_NEXTNODE
{
	int m_iSkinCoord;
	float m_fTime;
	float m_fPos[3];
	POBJECT_FOR_GXD *m_pPObject;
	EF_NEXTNODE( int iSkinCoord = 0, float fTime = 1.0f )
	{
		m_iSkinCoord = iSkinCoord;
		m_fTime = fTime;
		m_fPos[0] = 0;
		m_fPos[1] = 0;
		m_fPos[2] = 0;
		m_pPObject = NULL;
	}
	bool Load( HANDLE hFile );
	bool Save( HANDLE hFile );
};
struct EF_ALPHAKEY
{
	float m_fKeyFrame;
	BYTE m_byteALPHA;
	EF_ALPHAKEY( float fKeyFrame = 0, BYTE byteALPHA = 0 )
	{
		Set( fKeyFrame, byteALPHA );
	}
	void Set( float fKeyFrame, BYTE byteALPHA )
	{
		m_fKeyFrame = fKeyFrame;
		m_byteALPHA = byteALPHA;
	}
};
class EFFECTGROUP_FOR_GXD;
class EFFECT_FOR_GXD
{
private :
	int mMObjectSort;

public:
	EFFECT_FOR_GXD( void );
	virtual ~EFFECT_FOR_GXD( void );
	inline PSYSTEM_FOR_GXD * GetSystemPtr( void )
	{
		return m_pSystem;
	}
	inline POBJECT_FOR_GXD * GetObjectPtr( void )
	{
		return m_pPObject;
	}
	inline float * GetPos( void )
	{
		return m_fPos;
	}
	void SetTexturePath( char *pPath )
	{
		m_TextureName = pPath;
	}
	bool Init();
	bool Free();
	bool Load( HANDLE hFile, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	bool Save( HANDLE hFile );
	BOOL SaveToEFFECT2( HANDLE hFile,int tLODStepNum );
	void Update( SOBJECT_FOR_GXD *pSObjectDummy, MOTION_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	//void Update2( SOBJECT2_FOR_GXD *pSObjectDummy, MOTION2_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void DrawMObject( int iSort );
	void DrawPObject();
	void ReStart();
	void Stop( bool bIsAfterVisible = false );
	bool AddKeyFrame( float fKey );
	void DelKeyFrame( int ixVecter );
	static bool CompAlphaKey( const EF_ALPHAKEY &alphaKeyLeft, const EF_ALPHAKEY &alphaKeyRight );
	BYTE GetAlpha( int ixVector );
	void EditAlpha( int ixVector, int iAlpha );
	void CalcDrawAlphaVector();
	void SkinCoordScale( float fPos[3], float fSkinCoord[3], float fScale[3] );
	void SetName( std::string strName )
	{
		m_Name = strName;
	}
	void SetMoveType( int iMoveType );
	void SetMoveType2( int iMoveType2 );
	void SetMobjectRepeat( bool bRepeat )
	{
		m_bMObjectRepeat = bRepeat;
	}
	void InitializeSystem( void );
	void AllClear();
	bool ReAllocTempNode();
	void ReCalcTotlaMoveTime();
	void ReSetVectorSystem();
	void ParticleUpdateUseScale( POBJECT_FOR_GXD *pPObject, float fElapsedTime, float fPos[3], float fAng[3], float fScale[3] );
	void IncMObject( float fDiffTime );
	void NewParticle();
	bool NewMOBJECT( char achPath[] );
	void AddNode( int ixSkinCoord );
	void RemoveNode( int ixSkinCoord );
	void SetMoveTime( int ixNode, float fMoveTime );
	int GetChkCount();
	int GetMoveType();
	float GetTotalMoveTime();
	bool CopyFrom( EFFECT_FOR_GXD *pEffect );

	float m_fPosBase[3];
	bool m_bMObjectRepeat;
	int m_aiMoveType[2];
	int m_iCountInterObject;
	float m_fStartFrame;
	float m_fLifeFrame;
	float m_fTotalMoveTimeOrg;
	PSYSTEM_FOR_GXD *m_pSystem;
	MOBJECT_FOR_GXD *m_pMobject;
	//MOBJECT2_FOR_GXD *m_pMobject2;
	std::string m_Name;
	//std::vector<EF_NEXTNODE> m_vectorNextNode;
	//std::vector<EF_ALPHAKEY> m_vectorMObjectAlPha;
	int m_iIsStopAndVisible;
	bool m_bIsCopy;
	float m_fPos[3];
	float m_fAng[3];
	float m_fScale[3];
	std::string m_TextureName;
	float m_fFrame;
	float m_fNowTime;
	float m_fNowInterTime;
	int m_iNowIndex;
	int m_iDirectionRotateMove;
	bool m_bDrawMObject;
	bool m_bDrawPObject;
	bool m_bEndTime;
	float m_fTotalMoveTime;
	POBJECT_FOR_GXD *m_pPObject;
	//std::vector<EF_NEXTNODE> m_vectorTempNode;
	//std::vector<BYTE> m_vectorMObjectDrawAlpha;
};
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//CLASS_OF_GEFFECTGROUP
//-----------------------------------------------------------------------------------------------
class EFFECTGROUP_FOR_GXD
{
private :
	int mMObjectSort;

public:
	bool mCheckValidState;
	EFFECTGROUP_FOR_GXD();
	virtual ~EFFECTGROUP_FOR_GXD();
	bool Init();
	bool Free();
	bool Load( char *tFileName, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	bool Load( HANDLE hFile, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void Update( SOBJECT_FOR_GXD *pSObjectDummy, MOTION_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	//void Update2( SOBJECT2_FOR_GXD *pSObjectDummy, MOTION2_FOR_GXD *pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void DrawMObject( int iSort );
	void DrawPObject();
	void ReStart();
	void Stop( bool bIsAfterVisible = false );
	BOOL CopyFrom( EFFECTGROUP_FOR_GXD *pEffectGroup );
	BOOL CheckCollisionForMouseMS( int tX, int tY );
	EFFECT_FOR_GXD *GetGAttachObject( unsigned int index );
	int GetCount();
	bool IsEnd();
	BOOL Load();
	bool Save( char *tFileName );
	bool Save( HANDLE hFile );
	BOOL SaveToEFFECT2( char *tFileName, int tLODStepNum );

	char mFileName[DEF_LEN_FILE_NAME];
	float mLastUsedTime;
	//std::vector<EFFECT_FOR_GXD *> m_vecterAttachObject;
	const int m_iVersionEffect;

private:
	BOOL m_bCreateTexture;
	BOOL m_bRemoveFileData;
};
//-----------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_POBJECTINFO_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	float mCoord[3];
	float mAngle[3];
	POBJECT_FOR_GXD mParticle;
}
POBJECTINFO_FOR_GXD;

//-------------------------------------------------------------------------------------------------
//DEFINE_WORLD_FVF
//-------------------------------------------------------------------------------------------------
const static DWORD WORLD_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_WORLD_FOR_GXD
//-------------------------------------------------------------------------------------------------
class WORLD_FOR_GXD
{

private :

	int mWaterWaveTextureSize;

	BOOL GetXCoordWithTris( int tTrisIndex, float y, float z, float *x );
	BOOL GetYCoordWithTris( int tTrisIndex, float x, float z, float *y );
	BOOL GetZCoordWithTris( int tTrisIndex, float x, float y, float *z );
	BOOL CheckPointInTris( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInTrisWithoutYCoord( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInWorldWithoutYCoord( float tPoint[3] );
	BOOL CheckRayInTris( int tTrisIndex, float tQ[3], float tV[3], float tCoord[3], BOOL tCheckTwoSide );
	BOOL CheckSegmentInTris( int tTrisIndex, float tQ[3], float tV[3], float tCoord[3], BOOL tCheckTwoSide );

	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9*		m_ppIndexBuffer;	

	LPDWORD						m_dwpIndexNumOfTexture;

	LPMOBJECTINFO_FOR_MULTIDRAW		m_MObjectMultiInfo;

	CWorldMobjectScale m_MObjectScale;

	float GetMinXWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMinYWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMinZWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxXWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxYWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxZWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );

public :

	BOOL mCheckValidState;
	int mLoadSort;
	int mTextureNum;
	TEXTURE_FOR_GXD *mTexture;
	IDirect3DTexture9 *mWaterWaveTexture;
	TEXTURE_FOR_GXD mShadowTexture;
	int mG3WMeshNum;
	G3WMESH_FOR_GXD *mG3WMesh;
	int mWorldTrisNum;
	WORLDTRIS_FOR_GXD *mWorldTris;
	int mMObjectNum;
	MOBJECT_FOR_GXD *mMObject;
	char *mMObjectFileName;
	int mMObjectInfoNum;
	MOBJECTINFO_FOR_GXD *mMObjectInfo;
	int mPSystemNum;
	PSYSTEM_FOR_GXD *mPSystem;
	char *mPSystemFileName;
	int mPObjectInfoNum;
	POBJECTINFO_FOR_GXD *mPObjectInfo;
	int mTotalQuadtreeNodeNum;
	int mMaxQuadtreeNodeLeafNum;
	QUADTREENODE_FOR_GXD *mQuadtree;
	int *mTextureTrisPostIndex;
	int mSaveDrawQuadtreeNodeNum;
	int *mSaveDrawQuadtreeNodeIndex;
	int *mSaveDrawWorldTrisFlag;

	WORLD_FOR_GXD( void );
   ~WORLD_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromG3W( char *tFileName );
	BOOL CreateQuadtree( void );
	BOOL RecursionForCreateQuadtree( int tParentNodeIndex, int tChildNodeSortIndex, int tMaxQuadtreeDepth, int tPresentQuadtreeDepth );

	BOOL SaveWG( char *tFileName );
	BOOL SaveWG2( char *tFileName );
	BOOL SaveWM( char *tFileName );
	BOOL SaveWM2( char *tFileName );
	BOOL SaveWO( char *tFileName );
	BOOL SaveWO2( char *tFileName, int tLODStepNum );
	BOOL SaveWP( char *tFileName );
	BOOL SaveWP2( char *tFileName );

	BOOL LoadWG( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL LoadWM( char *tFileName );
	BOOL LoadWO( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );

	//-----------------------//
	//월드내 스케일 정보 관련//
	//-----------------------//
	BOOL LoadWS( char *tFileName);
	BOOL SaveWS( char *tFileName);
	BOOL InitWS( );
	BOOL InsertMObjectScale();
	BOOL SetMObjectScale(WORD wIndex , FLOAT fRate);
	VOID ClearLastScaleRate()
	{
		m_MObjectScale.ClearLastScaleRate();
		return;
	}
	const FLOAT GetScaleRateX(WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateX(wIndex);
	}
	const FLOAT GetScaleRateY(WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateY(wIndex);
	}
	const FLOAT GetScaleRateZ(WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateZ(wIndex);
	}
	const FLOAT GetLastScaleRateX()
	{
		return m_MObjectScale.GetLastScaleRateX();
	}
	const FLOAT GetLastScaleRateY()
	{
		return m_MObjectScale.GetLastScaleRateY();
	}
	const FLOAT GetLastScaleRateZ()
	{
		return m_MObjectScale.GetLastScaleRateZ();
	}
	//-----------------------//
	//-----------------------//
	//-----------------------//

	void FreeMObjectInfo( void );
	BOOL LoadWP( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void FreePObjectInfo( void );
	void Update( float tFrameRatio, float tTime );
	void Draw( int tDrawSort, BOOL tCheckDrawWaterEffect, float tWaterEffectValue, BOOL tCheckDrawCameraSpecularEffect, float tPostLimitCoord[3], float tPostLimitLength, float tPostLengthRatioForBlendValue );
	void RecursionForDraw( int tParentNodeIndex );
	void DrawWithWM( void );
	void RecursionForDrawWithWM( int tParentNodeIndex );
	BOOL MakeWaterWaveTexture( void );
	BOOL MakeShadowTexture( char *tFileName );

	BOOL ScreenCoordToWorldCoord( int tX, int tY, int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForScreenCoordToWorldCoord( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL TestRayInWorld( float tSCoord[3], float tECoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForTestRayInWorld( int tParentNodeIndex, float tQ[3], float tV[3], BOOL tCheckTwoSide );
	BOOL FindRayInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForFindRayInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL TestSegmentInWorld( float tSCoord[3], float tECoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForTestSegmentInWorld( int tParentNodeIndex, float tQ[3], float tV[3], BOOL tCheckTwoSide );
	BOOL FindSegmentInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForFindSegmentInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );

	BOOL FindCameraInWorld( float tCameraLook[3], float tCameraEye[3], float tCameraRadius, float tCameraCoord[3] );
	BOOL RecursionForFindCameraInWorld( int tParentNodeIndex, float tCameraLook[3], float tCameraEye[3], float tCameraRadius, float tCameraCoord[3] );
	BOOL TestCameraInWorldMObject( float tCameraLook[3], float tCameraEye[3] );

	BOOL GetYCoord( float x, float z, float *y, BOOL tCheckExistPostYCoord, float tPostYCoord, BOOL tCheckTwoSide, BOOL tCheckOnlyOne );
	void Path( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, float tResult[3] );
	BOOL Move( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival );
    BOOL Move2 (float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival);

private:
    bool    SetUpAtlasUV (D3DXMATRIX& viewmatrix, D3DXMATRIX& projmatrix);

};



class GXD
{

public :

	inline DWORD F2DW( FLOAT f ) { return *( ( DWORD *) &f ); }


	int mTextureOptionWidth;
	int mTextureOptionHeight;
	int unkA[24];
	BOOL mCheckInitState;

	//------//
	//OPTION//
	//------//
	//int mTextureOptionValue;
	//int mSamplerOptionValue;
	//int mNormalMapOptionValue;
	//float mLODLengthInfo[2];
	//int mFilterOptionValue;
	//BOOL mCheckDepthBias;
	//BOOL mCheckTwoSideStencilFunction;
	//------//
	//------//
	//------//

	BOOL mCheckFullScreen;
	HINSTANCE mInstanceHandle;
	HWND mWindowHandle;
	int mScreenXSize;
	int mScreenYSize;
	float mFovY;
	float mNearPlane;
	float mFarPlane;
	BOOL mUseFog;
	D3DXFONT_DESC mFontInfo;
	int mMaxParticleNum;
	int unk1;

	LARGE_INTEGER mHighResolutionTicks;
	double mTicksForRange;
	double mTicksForTime1;
	double mTicksForTime2;

	IDirect3D9 *mDirect3D;
	D3DCAPS9 mGraphicSupportInfo;
	D3DPRESENT_PARAMETERS mGraphicPresentParameters;
	IDirect3DDevice9 *mGraphicDevice;
	ID3DXSprite *mGraphicSprite;
	ID3DXFont *mGraphicFont;
	PARTICLEVERTEX_FOR_GXD* mParticleVertexBuffer;

	ID3DXEffect *mOriEffect;
	IDirect3DTexture9 *mFilterTexture[2];
	IDirect3DSurface9 *mFilterSurface[2];

	//int mDRAW_POLYGON_NUM;

	D3DVIEWPORT9 mViewport;
	D3DXMATRIX mViewportMatrix;
	D3DXMATRIX mPerspectiveMatrix;
	D3DXVECTOR3 mCameraEye;
	D3DXVECTOR3 mCameraLook;
	D3DXVECTOR3 mCameraForward;
	D3DXMATRIX mViewMatrix;
	D3DXMATRIX mBillboardMatrixInfoForAll;
	D3DXVECTOR3 mBillboardVertexInfoForAll[2];
	D3DXMATRIX mBillboardMatrixInfoForY;
	D3DXVECTOR3 mBillboardVertexInfoForY[2];
	D3DXMATRIX mWorldMatrix;

	D3DMATERIAL9 mMaterial;

	D3DLIGHT9 mLight;
	BYTE mClearColor0;//clear color?
	BYTE mClearColor1;//clear color?
	BYTE mClearColor2;//clear color?
	D3DCOLOR mFogColor;
	D3DXVECTOR3 mLightDirectionForShadow;

	DWORD mSamplerOption0;
	DWORD mSamplerOption1;
	DWORD mSamplerOption2;

	float mFrustumPlane[6][4];

	BOOL mCheckOriEffect;
	D3DXHANDLE mOriFilter;
	D3DXHANDLE mOriSource;
	D3DXHANDLE mOriGrow;

	BOOL mCheckValidStateForSound;
	IDirectSound8 *mDirectSound;
	IDirectSoundBuffer *mSoundPrimaryBuffer;
	char mSoundOutBufferForPCM[4096];

	IDirectInput8 *mDirectInput;
	IDirectInputDevice8 *mKeyboard;
	BYTE mKeyboardImmediateData[256];
	DWORD mKeyboardBufferedDataNum;
	DIDEVICEOBJECTDATA mKeyboardBufferedData[32];


	HINSTANCE mCompressLibrary;
	FCompressBound mFCompressBound;
	FCompress mFCompress;
	FUncompress mFUncompress;

//	BOOL m_bUseMultiDraw;
//
//	//------//
//	//SHADOW//
//	//------//
//	DRAWSHADOWVERTEX_FOR_GXD mSaveShadowVertexBuffer[MAX_SAVE_SHADOW_VERTEX_NUM];
//	int mDrawShadowTrisInfo[MAX_DRAW_SHADOW_TRIS_NUM];
//	int mDrawShadowVertexNum;
//	IDirect3DVertexBuffer9 *mDrawShadowVertexBuffer;
//	//------//
//	//------//
//	//------//
//
//	//--------------//
//	//SHADER_PROGRAM//
//	//--------------//
//	IDirect3DVertexDeclaration9 *mDECLForSKIN2;
//	IDirect3DVertexDeclaration9 *mDECLForSKIN2SHADOW;
//	//00
//	int mPresentShaderProgramNumber;
//	//01-[VERTEX_SHADER-01]
//	ID3DXConstantTable *mAmbient1_VS_ConstantTable;
//	IDirect3DVertexShader9 *mAmbient1_VS_Shader;
//	D3DXHANDLE mAmbient1_VS_WorldViewProjMatrix;
//	D3DXHANDLE mAmbient1_VS_LightAmbient;
//	//02-[PIXEL_SHADER-01]
//	ID3DXConstantTable *mAmbient1_PS_ConstantTable;
//	IDirect3DPixelShader9 *mAmbient1_PS_Shader;
//	D3DXHANDLE mAmbient1_PS_Texture0;
//	D3DXCONSTANT_DESC mAmbient1_PS_Texture0_DESC;
//	//03-[VERTEX_SHADER-02]
//	ID3DXConstantTable *mAmbient2_VS_ConstantTable;
//	IDirect3DVertexShader9 *mAmbient2_VS_Shader;
//	D3DXHANDLE mAmbient2_VS_KeyMatrix;
//	D3DXHANDLE mAmbient2_VS_WorldViewProjMatrix;
//	D3DXHANDLE mAmbient2_VS_LightDirection;
//	D3DXHANDLE mAmbient2_VS_LightAmbient;
//	D3DXHANDLE mAmbient2_VS_LightDiffuse;
//	//04-[PIXEL_SHADER-02]
//	ID3DXConstantTable *mAmbient2_PS_ConstantTable;
//	IDirect3DPixelShader9 *mAmbient2_PS_Shader;
//	D3DXHANDLE mAmbient2_PS_Texture0;
//	D3DXCONSTANT_DESC mAmbient2_PS_Texture0_DESC;
//	//05-[VERTEX_SHADER-03]
//	ID3DXConstantTable *mNormal1_VS_ConstantTable;
//	IDirect3DVertexShader9 *mNormal1_VS_Shader;
//	D3DXHANDLE mNormal1_VS_KeyMatrix;
//	D3DXHANDLE mNormal1_VS_WorldViewProjMatrix;
//	D3DXHANDLE mNormal1_VS_LightDirection;
//	//06-[PIXEL_SHADER-03]
//	ID3DXConstantTable *mNormal1_PS_ConstantTable;
//	IDirect3DPixelShader9 *mNormal1_PS_Shader;
//	D3DXHANDLE mNormal1_PS_Texture0;
//	D3DXCONSTANT_DESC mNormal1_PS_Texture0_DESC;
//	D3DXHANDLE mNormal1_PS_Texture1;
//	D3DXCONSTANT_DESC mNormal1_PS_Texture1_DESC;
//	D3DXHANDLE mNormal1_PS_LightAmbient;
//	D3DXHANDLE mNormal1_PS_LightDiffuse;
//	//07-[VERTEX_SHADER-04]
//	ID3DXConstantTable *mNormal2_VS_ConstantTable;
//	IDirect3DVertexShader9 *mNormal2_VS_Shader;
//	D3DXHANDLE mNormal2_VS_KeyMatrix;
//	D3DXHANDLE mNormal2_VS_WorldViewProjMatrix;
//	D3DXHANDLE mNormal2_VS_LightDirection;
//	D3DXHANDLE mNormal2_VS_CameraEye;
//	//08-[PIXEL_SHADER-04]
//	ID3DXConstantTable *mNormal2_PS_ConstantTable;
//	IDirect3DPixelShader9 *mNormal2_PS_Shader;
//	D3DXHANDLE mNormal2_PS_Texture0;
//	D3DXCONSTANT_DESC mNormal2_PS_Texture0_DESC;
//	D3DXHANDLE mNormal2_PS_Texture1;
//	D3DXCONSTANT_DESC mNormal2_PS_Texture1_DESC;
//	D3DXHANDLE mNormal2_PS_Texture2;
//	D3DXCONSTANT_DESC mNormal2_PS_Texture2_DESC;
//	D3DXHANDLE mNormal2_PS_LightAmbient;
//	D3DXHANDLE mNormal2_PS_LightDiffuse;
//	//09-[VERTEX_SHADER-05]
//	ID3DXConstantTable *mAmbient3_VS_ConstantTable;
//	IDirect3DVertexShader9 *mAmbient3_VS_Shader;
//	D3DXHANDLE mAmbient3_VS_KeyMatrix;
//	D3DXHANDLE mAmbient3_VS_WorldViewProjMatrix;
//	//10-[PIXEL_SHADER-05]
//	//11-[VERTEX_SHADER-06]
//	//12-[PIXEL_SHADER-06]
//	ID3DXConstantTable *mFilter1_PS_ConstantTable;
//	IDirect3DPixelShader9 *mFilter1_PS_Shader;
//	D3DXHANDLE mFilter1_PS_Texture0;
//	D3DXCONSTANT_DESC mFilter1_PS_Texture0_DESC;
//	D3DXHANDLE mFilter1_PS_Texture0PostSize;
//	//13-[VERTEX_SHADER-07]
//	//14-[PIXEL_SHADER-07]
//	ID3DXConstantTable *mFilter2_PS_ConstantTable;
//	IDirect3DPixelShader9 *mFilter2_PS_Shader;
//	D3DXHANDLE mFilter2_PS_Texture0;
//	D3DXCONSTANT_DESC mFilter2_PS_Texture0_DESC;
//	D3DXHANDLE mFilter2_PS_Texture0PostSize;
//	//15-[VERTEX_SHADER-08]
//	ID3DXConstantTable *mShadow1_VS_ConstantTable;
//	IDirect3DVertexShader9 *mShadow1_VS_Shader;
//	D3DXHANDLE mShadow1_VS_WorldViewProjMatrix;
	//16-[PIXEL_SHADER-08]
	//--------------//
	//--------------//
	//--------------//

	GXD( void );
    ~GXD( void );

	void InitForSound( void );
	BOOL Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, BOOL tUseFog, D3DXFONT_DESC *tFontInfo, int *tRESULT );
	void Free( void );
	float GetRandomNumber( float tMinValue, float tMaxValue );
	float GetTotalElapsedSeconds( void );
	void ChangeViewLength( float tNearPlane, float tFarPlane );
	BOOL SetCameraPosition( float tCameraEyeX, float tCameraEyeY, float tCameraEyeZ, float tCameraLookX, float tCameraLookY, float tCameraLookZ );
	void ChangeCameraForHorizon( float tRA );
	void ChangeCameraForVertical( float tRA );
	void ChangeCameraForForward( float tFD );
	void SetDefaultMaterial( void );
	void SetPresentMaterial( D3DXCOLOR tColor );
	void SetPresentMaterialForSpecular( float* a2, float a3 );
	void ChangeLight( D3DVECTOR a2, D3DXCOLOR a3, D3DCOLORVALUE a4 );
	//void SetDefaultLight( void );
	void SetAmbientLight( int tAmbientSort, D3DXCOLOR tAmbientValue );
	//void SetAmbientLight( int tAmbientSort, float r, float g, float b, float a );
	//void SetAmbientLight( int tAmbientSort, int z );
	void OffAmbientLight( void );
	void SetCameraSpecularEffect( float a2, float a3 );
	void OffCameraSpecularEffect();
	BYTE GetShadowIntensityValueForWorld( void );
	BYTE GetShadowIntensityValueForObject( void );
	void ChangeFogEffect( BYTE* a2, float a3 );
	void ChangeTextureFilter( DWORD a2, DWORD a3, DWORD a4 );
	BOOL ReadyForDrawing( int *tRESULT );
	void BeginForDrawing( SKY_FOR_GXD* tSKY );
	void EndForDrawing( void );

	//void BeginForHighShadow( void );
	//void EndForHighShadow( void );

	void BeginForLowShadow( void );
	void EndForLowShadow( void );

	void BeginForPOBJECT( void );
	void EndForPOBJECT( void );

	void ProcessForFilter( void );

	void BeginFor2D( void );
	void EndFor2D( void );


	int GetStringLength( char *tString );
	void DrawString( char *tString, int tX, int tY, D3DCOLOR tColor, int tOutLineSort );

	void SaveScreenToBMP( char *tFileName );
	void SaveScreenToJPG( char *tFileName );

	
	
	void CalculateFrustum( void );
	BOOL CheckPointInFrustum( float tPoint[3] );
	BOOL CheckPointInFrustumWithoutFarPlane( float tPoint[3] );
	BOOL CheckSphereInFrustum( float tCenter[3], float tRadius );
	BOOL CheckSphereInFrustum( D3DXVECTOR3 *tCenter, float tRadius );
	BOOL CheckSphereInFrustumForWorld( float tCenter[3], float tRadius );
	BOOL CheckBoxInFrustum( float tBoxMin[3], float tBoxMax[3] );

	void TrisProjection( float rkD[3], float akV[3][3], float *rfMin, float *rfMax );
	void BoxProjection( float rkAxis[3], float rkOrigin[3], float akAxis[3][3], float afExtent[3], float *rfMin, float *rfMax );

	BOOL CheckCollisionForRayBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForSegmentBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForWorldTrisBox( WORLDTRIS_FOR_GXD *tWorldTris, float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForBoxBox( float tBoxMin01[3], float tBoxMax01[3], float tBoxMin02[3], float tBoxMax02[3] );
	BOOL CheckCollisionForMouseBox( int tX, int tY, float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForRayMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForSegmentMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForWorldTrisMS( WORLDTRIS_FOR_GXD *tWorldTris, MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForMSMS( MESHSIZE_FOR_GXD *tMeshSize01, MESHSIZE_FOR_GXD *tMeshSize02 );
	BOOL CheckCollisionForMouseMS( int tX, int tY, MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForSphereSphere( float tCenter01[3], float tRadius01, float tCenter02[3], float tRadius02 );

	BOOL GetCompressSize( DWORD tOriginalSize, BYTE *tOriginal, DWORD *tCompressSize );
	BOOL Compress( DWORD tOriginalSize, BYTE *tOriginal, DWORD tCompressSize, BYTE *tCompress );
	BOOL Decompress( DWORD tCompressSize, BYTE *tCompress, DWORD tOriginalSize, BYTE *tOriginal );

	void ChangeFilterTextureSize(int Width, int Height);
	void ProcessForFilter(float a6, float a7, float a8, int a9, float a10, int a11, int a12, float a13);

	void UpdateForInputSystem( BOOL tApplicationActive );
	
	BOOL WorldCoordToScreenCoord( float tCoord[3], int *tX, int *tY );

};

extern GXD mGXD;