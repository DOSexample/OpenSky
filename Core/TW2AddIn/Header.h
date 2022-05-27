#pragma once

#undef SHARE_HEADER_H
#define USE_ADDIN 1
#include <ShareHeader.h>

BEGIN_NS


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MOTION2_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MOTION2_FOR_GXD
{

public :

	BOOL mCheckValidState;
	int mFrameNum;
	int mBoneNum;
	D3DXMATRIX* mKeyMatrix;

	MOTION2_FOR_GXD( void );
    ~MOTION2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( char *tFileName, bool tLoadSort );
	BOOL LoadHeader( HANDLE tHandle, int *tVersion );
	BOOL LoadExtraHeader( HANDLE tHandle, int *tIsVisible, int *tIsCompress );
	BOOL LoadCompressedChunk( HANDLE tHandle );
	BOOL LoadUnCompressedChunk( HANDLE tHandle );
	void GetMotion1VoidPtr( void* tMOTION1 );
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_OF_SOBJECT2
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//STRUCT_OF_SKINEFFECT2_FOR_GXD
typedef struct
{
	int mAnimationMapInfo[2];
	int mRadiationInfo[10];
	int mBillboardInfo[2];
}
SKINEFFECT2_FOR_GXD;
//STRUCT_OF_SKINSIZE2_FOR_GXD
typedef struct
{
	float mBoxSize[3];
}
SKINSIZE2_FOR_GXD;
//STRUCT_OF_SKINVERTEX2_FOR_GXD
typedef struct SKINVERTEX2_FOR_GXD
{
	float mV[3];
	float mW[4];
	DWORD mB;
	float mN1[3];
	float mN2[3];
	float mN3[3];
	float mT[2];
}
SKINVERTEX2_FOR_GXD;
//STRUCT_OF_SKINSHADOWVERTEX2_FOR_GXD
typedef struct SKINSHADOWVERTEX2_FOR_GXD
{
	float mV[3];
	float mW[4];
	DWORD mB;
}
SKINSHADOWVERTEX2_FOR_GXD;
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SKIN2_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SKIN2_FOR_GXD
{
public :

	BOOL mCheckValidState;
	SKINEFFECT2_FOR_GXD mEffect;
	SKINSIZE2_FOR_GXD mSize;
	SKINVERTEX2_FOR_GXD mVertexBufferForBillboard[4];
	SKINVERTEX2_FOR_GXD mVertexBillboardForUse[4];
	int mLODStepNum;
	int* mVertexNum;
	IDirect3DVertexBuffer9** mVertexBuffer;
	int* mTrisNum;
	IDirect3DIndexBuffer9** mIndexBuffer;
	SKINSHADOWVERTEX2_FOR_GXD** mShadowVertexBuffer;
	WORD** mShadowIndexBuffer;
	WORD** mShadowEdgeBuffer;
	TEXTURE_FOR_GXD mDiffuseMap;
	TEXTURE_FOR_GXD mNormalMap;
	TEXTURE_FOR_GXD mSpecularMap;
	int mAnimationMapNum;
	TEXTURE_FOR_GXD* mAnimationMap;

	SKIN2_FOR_GXD( void );
    ~SKIN2_FOR_GXD( void );

	void Init( void );
	void Free( void );
	
	BOOL Load( BYTE *tDataBuffer, int& tDataPosition );
	BOOL Load( HANDLE hFile );

	void Draw( int tDrawSort, MOTION2_FOR_GXD *tMotion, float tFrame, float tLODRatio, TEXTURE_FOR_GXD* tDiffuseMap, TEXTURE_FOR_GXD*tNormalMap, TEXTURE_FOR_GXD *tSpecularMap );

};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SOBJECT2_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SOBJECT2_FOR_GXD
{
public :

	BOOL mCheckValidState;
	int mSkinNum;
	SKIN2_FOR_GXD* mSkin;

	SOBJECT2_FOR_GXD( void );
    ~SOBJECT2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( char *tFileName, bool tLoadSort );
	BOOL LoadHeader( HANDLE hFile , int& tVersion );
	BOOL LoadExtraHeader( HANDLE hFile , int& tIsVisible, int& tIsCompress );
	BOOL LoadUncompressedChunk( HANDLE hFile );
	BOOL LoadCompressedChunk( HANDLE hFile );

	void Draw( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], int tDrawSort, MOTION2_FOR_GXD *tMotion, float tFrame, TEXTURE_FOR_GXD *tDiffuseMap, TEXTURE_FOR_GXD *tNormalMap, TEXTURE_FOR_GXD *tSpecularMap );
	void DrawForHighShadow( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, void *tWorld, float tValidShadowLength );
	void DrawForLowShadow( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, void *tWorld, float tValidShadowLength );

	void GetSkinCoord( int tSkinIndex, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, float tResult[3] );

};
//-------------------------------------------------------------------------------------------------


typedef struct CAtmosphere {
	DWORD data[72];
} CAtmosphere;
typedef struct CRenderStateMgr {
	DWORD data[6];
} CRenderStateMgr;
typedef struct CTextureStageStateMgr {
	DWORD data[49];
} CTextureStageStateMgr;

class GXD
{

public :

	inline DWORD F2DW( FLOAT f ) { return *( ( DWORD *) &f ); }


	BOOL mCheckInitState;

	//------//
	//OPTION//
	//------//
	int mTextureOptionValue;
	int mSamplerOptionValue;
	int mNormalMapOptionValue;
	float mLODLengthInfo[2];
	int mFilterOptionValue;
	BOOL mCheckDepthBias;
	BOOL mCheckTwoSideStencilFunction;
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
	D3DXFONT_DESC mFontInfo;
	int mMaxParticleNum;
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

	IDirect3DTexture9 *mFilterTexture[2];
	IDirect3DSurface9 *mFilterSurface[2];

	int mDRAW_POLYGON_NUM;

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
	D3DXVECTOR3 mLightDirectionForShadow;

	float mFrustumPlane[6][4];

	BOOL mCheckValidStateForSound;
	IDirectSound8 *mDirectSound;
	IDirectSoundBuffer *mSoundPrimaryBuffer;
	char mSoundOutBufferForPCM[4096];

	IDirectInput8 *mDirectInput;
	IDirectInputDevice8 *mKeyboard;
	BYTE mKeyboardImmediateData[256];
	DWORD mKeyboardBufferedDataNum;
	DIDEVICEOBJECTDATA mKeyboardBufferedData[32];

	CAtmosphere m_Atmosphere;
	CRenderStateMgr m_RenderStateMgr;
	CTextureStageStateMgr m_TextureStateMgr;

	HINSTANCE mCompressLibrary;
	FCompressBound mFCompressBound;
	FCompress mFCompress;
	FUncompress mFUncompress;

	BOOL m_bUseMultiDraw;

	//------//
	//SHADOW//
	//------//
	DRAWSHADOWVERTEX_FOR_GXD mSaveShadowVertexBuffer[MAX_SAVE_SHADOW_VERTEX_NUM];
	int mDrawShadowTrisInfo[MAX_DRAW_SHADOW_TRIS_NUM];
	DRAWSHADOWVERTEX2_FOR_GXD for_shadow[12857];
	int mDrawShadowVertexNum;
	IDirect3DVertexBuffer9 *mDrawShadowVertexBuffer;
	//------//
	//------//
	//------//

	//--------------//
	//SHADER_PROGRAM//
	//--------------//
	IDirect3DVertexDeclaration9 *mDECLForSKIN2;
	//IDirect3DVertexDeclaration9 *mDECLForSKIN2SHADOW;
	//00
	int mPresentShaderProgramNumber;
	//01-[VERTEX_SHADER-01]
	ID3DXConstantTable *mAmbient1_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient1_VS_Shader;
	D3DXHANDLE mAmbient1_VS_WorldViewProjMatrix;
	D3DXHANDLE mAmbient1_VS_LightAmbient;
	//02-[PIXEL_SHADER-01]
	ID3DXConstantTable *mAmbient1_PS_ConstantTable;
	IDirect3DPixelShader9 *mAmbient1_PS_Shader;
	D3DXHANDLE mAmbient1_PS_Texture0;
	D3DXCONSTANT_DESC mAmbient1_PS_Texture0_DESC;
	//03-[VERTEX_SHADER-02]
	ID3DXConstantTable *mAmbient2_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient2_VS_Shader;
	D3DXHANDLE mAmbient2_VS_KeyMatrix;
	D3DXHANDLE mAmbient2_VS_WorldViewProjMatrix;
	D3DXHANDLE mAmbient2_VS_LightDirection;
	D3DXHANDLE mAmbient2_VS_LightAmbient;
	D3DXHANDLE mAmbient2_VS_LightDiffuse;
	//04-[PIXEL_SHADER-02]
	ID3DXConstantTable *mAmbient2_PS_ConstantTable;
	IDirect3DPixelShader9 *mAmbient2_PS_Shader;
	D3DXHANDLE mAmbient2_PS_Texture0;
	D3DXCONSTANT_DESC mAmbient2_PS_Texture0_DESC;
	//05-[VERTEX_SHADER-03]
	ID3DXConstantTable *mNormal1_VS_ConstantTable;
	IDirect3DVertexShader9 *mNormal1_VS_Shader;
	D3DXHANDLE mNormal1_VS_KeyMatrix;
	D3DXHANDLE mNormal1_VS_WorldViewProjMatrix;
	D3DXHANDLE mNormal1_VS_LightDirection;
	//06-[PIXEL_SHADER-03]
	ID3DXConstantTable *mNormal1_PS_ConstantTable;
	IDirect3DPixelShader9 *mNormal1_PS_Shader;
	D3DXHANDLE mNormal1_PS_Texture0;
	D3DXCONSTANT_DESC mNormal1_PS_Texture0_DESC;
	D3DXHANDLE mNormal1_PS_Texture1;
	D3DXCONSTANT_DESC mNormal1_PS_Texture1_DESC;
	D3DXHANDLE mNormal1_PS_LightAmbient;
	D3DXHANDLE mNormal1_PS_LightDiffuse;
	//07-[VERTEX_SHADER-04]
	ID3DXConstantTable *mNormal2_VS_ConstantTable;
	IDirect3DVertexShader9 *mNormal2_VS_Shader;
	D3DXHANDLE mNormal2_VS_KeyMatrix;
	D3DXHANDLE mNormal2_VS_WorldViewProjMatrix;
	D3DXHANDLE mNormal2_VS_LightDirection;
	D3DXHANDLE mNormal2_VS_CameraEye;
	//08-[PIXEL_SHADER-04]
	ID3DXConstantTable *mNormal2_PS_ConstantTable;
	IDirect3DPixelShader9 *mNormal2_PS_Shader;
	D3DXHANDLE mNormal2_PS_Texture0;
	D3DXCONSTANT_DESC mNormal2_PS_Texture0_DESC;
	D3DXHANDLE mNormal2_PS_Texture1;
	D3DXCONSTANT_DESC mNormal2_PS_Texture1_DESC;
	D3DXHANDLE mNormal2_PS_Texture2;
	D3DXCONSTANT_DESC mNormal2_PS_Texture2_DESC;
	D3DXHANDLE mNormal2_PS_LightAmbient;
	D3DXHANDLE mNormal2_PS_LightDiffuse;
	//09-[VERTEX_SHADER-05]
	ID3DXConstantTable *mAmbient3_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient3_VS_Shader;
	D3DXHANDLE mAmbient3_VS_KeyMatrix;
	D3DXHANDLE mAmbient3_VS_WorldViewProjMatrix;
	//10-[PIXEL_SHADER-05]
	//11-[VERTEX_SHADER-06]
	//12-[PIXEL_SHADER-06]
	ID3DXConstantTable *mFilter1_PS_ConstantTable;
	IDirect3DPixelShader9 *mFilter1_PS_Shader;
	D3DXHANDLE mFilter1_PS_Texture0;
	D3DXCONSTANT_DESC mFilter1_PS_Texture0_DESC;
	D3DXHANDLE mFilter1_PS_Texture0PostSize;
	//13-[VERTEX_SHADER-07]
	//14-[PIXEL_SHADER-07]
	ID3DXConstantTable *mFilter2_PS_ConstantTable;
	IDirect3DPixelShader9 *mFilter2_PS_Shader;
	D3DXHANDLE mFilter2_PS_Texture0;
	D3DXCONSTANT_DESC mFilter2_PS_Texture0_DESC;
	D3DXHANDLE mFilter2_PS_Texture0PostSize;
	//15-[VERTEX_SHADER-08]
	ID3DXConstantTable *mShadow1_VS_ConstantTable;
	IDirect3DVertexShader9 *mShadow1_VS_Shader;
	D3DXHANDLE mShadow1_VS_WorldViewProjMatrix;
	//16-[PIXEL_SHADER-08]
	//--------------//
	//--------------//
	//--------------//

	DWORD m_dwEngineStartTime;

	BOOL m_bNeedReset;

	IDirect3DSurface9* m_pOriginalSurface;
	IDirect3DTexture9* m_pRenderTargetTexture;
	IDirect3DSurface9* m_pRenderTargetSurface;
	IDirect3DSurface9* m_pOriginalDepthStencilSurface;
	IDirect3DSurface9* m_pRenderTargetDepthStencilSurface;

	GXD( void );
    ~GXD( void );

	void InitForSound( void );

	BOOL Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, BOOL tUseFog, D3DXFONT_DESC *tFontInfo, int *tRESULT );
	void Free( void );

	BOOL InitForAddIn( int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, IDirect3D9 *tDirect3D, IDirect3DDevice9 *tGraphicDevice, int& tRESULT );	
	void FreeForAddIn( void );

	//--------------//
	//SHADER_PROGRAM//
	//--------------//
	BOOL MakeShaderProgram01( void );
	BOOL MakeShaderProgram02( void );
	BOOL MakeShaderProgram03( void );
	BOOL MakeShaderProgram04( void );
	BOOL MakeShaderProgram05( void );
	BOOL MakeShaderProgram06( void );
	BOOL MakeShaderProgram07( void );
	BOOL MakeShaderProgram08( void );
	BOOL MakeShaderProgram09( void );
	BOOL MakeShaderProgram10( void );
	BOOL MakeShaderProgram11( void );
	BOOL MakeShaderProgram12( void );
	BOOL MakeShaderProgram13( void );
	BOOL MakeShaderProgram14( void );
	BOOL MakeShaderProgram15( void );
	BOOL MakeShaderProgram16( void );
	//--------------//
	//--------------//
	//--------------//

	float GetRandomNumber( float tMinValue, float tMaxValue );

	float GetTotalElapsedSeconds( void );
	float GetTotalElapsedSecondsFromMMT ( void );

	BOOL SetCameraPosition( float tCameraEyeX, float tCameraEyeY, float tCameraEyeZ, float tCameraLookX, float tCameraLookY, float tCameraLookZ );
	void ChangeCameraForHorizon( float tRA );
	void ChangeCameraForVertical( float tRA );
	void ChangeCameraForForward( float tFD );

	void SetDefaultMaterial( void );

	void SetDefaultLight( void );
	void SetAmbientLight( int tAmbientSort, D3DXCOLOR tAmbientValue );
	void SetAmbientLight( int tAmbientSort, float r, float g, float b, float a );

	void SetDefaultTextureSamplerState( void );

	BOOL ReadyForDrawing( int *tRESULT );

	BOOL OnLostDevice( void );
	BOOL OnResetDevice( void );

	void BeginForDrawing( SKY_FOR_GXD* tSKY );
	void EndForDrawing( void );

	void BeginForHighShadow( void );
	void EndForHighShadow( void );

	void BeginForLowShadow( void );
	void EndForLowShadow( void );

	void BeginForPOBJECT( void );
	void EndForPOBJECT( void );

	void ProcessForFilter( void );

	void BeginFor2D( void );
	void EndFor2D( void );

	BOOL WorldCoordToScreenCoord( float tCoord[3], int *tX, int *tY );

	int GetStringLength( char *tString );
	void DrawString( char *tString, int tX, int tY, D3DXCOLOR tColor, int tOutLineSort );

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

	void UpdateForInputSystem( BOOL tApplicationActive );

	bool CreateTextureForRenderTarget( UINT width, UINT height, D3DFORMAT format );
	void DestroyTextureForRenderTarget( void );

	bool SetRenderTarget( void );
	bool SetDepthStencilSurface( void );

	IDirect3DTexture9 * GetRenderTargetTexturePtr( void );
	IDirect3DSurface9 * GetRenderTargetSurfacePtr( void );

	bool RestoreRenderTarget( void );
	bool RestoreDepthStencilSurface( void );

	VOID OnMultiDraw( ){ m_bUseMultiDraw = TRUE; }
	VOID OffMultiDraw( ){ m_bUseMultiDraw = FALSE; }
	

	void SetPresentMaterialForSpecular( float tSpecularEMV[4], float tSpecularEMP );
	void SetCameraSpecularEffect( float tSpecularAdd, float tLightAdd );
	void OffCameraSpecularEffect( void );
	void OffAmbientLight( void );


};

extern GXD mGXD;

END_NS