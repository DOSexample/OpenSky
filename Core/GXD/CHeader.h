#ifndef GXDC_HEADER_H
#define GXDC_HEADER_H

//-------------------------------------------------------------------------------------------------
//DEFINE_FOR_C_CLANGUAGE
//-------------------------------------------------------------------------------------------------

#include <ShareHeader.h>

#ifdef __cplusplus
//for c++ compiler
extern "C" {
#endif

typedef struct gxd_texture_t {
	BOOL mCheckValidState;
	DWORD mFileDataSize;
	BYTE* mFileData;
	D3DXIMAGE_INFO mTextureInfo;
	int mProcessModeCase;
	int mAlphaModeCase;
	int mOrgAlphaModeCase;
	IDirect3DTexture9* mTexture;
} gxd_texture_t;

//-------------------------------------------------------------------------------------------------
typedef struct gxd_motion_t {
	BOOL mCheckValidState;
	int mFrameNum;
	int mBoneNum;
	D3DXMATRIX* mKeyMatrix;
} gxd_motion_t;
void gxd_motion_Init( gxd_motion_t* motion );
void gxd_motion_Free( gxd_motion_t* motion );
BOOL gxd_motion_LoadFromG3M( gxd_motion_t* motion, const char* tFileName, int tLoadSort );
BOOL gxd_motion_Save( gxd_motion_t* motion, const char* tFileName );
BOOL gxd_motion_Save2( gxd_motion_t* motion, HANDLE hFile );
BOOL gxd_motion_Load( gxd_motion_t* motion, const char* tFileName );
//BOOL gxd_motion_SaveToMOTION2( gxd_motion_t* motion, const char* tFileName );
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
typedef struct gxd_sky_t
{
	BOOL mCheckValidState;
	gxd_texture_t mTextureForSkyBox[6];
	float mLensFlareShapeRatio;
	gxd_texture_t mTextureForLensFlare[10];
	float mPostFarPlane;
	SKYBOXVERTEX_FOR_GXD mSkyBoxVertexBuffer[24];
	LENSFLAREVERTEX_FOR_GXD mLensFlareVertexBuffer[4];


} gxd_sky_t;
void gxd_sky_Init( gxd_sky_t* sky );
BOOL gxd_sky_Free( gxd_sky_t* sky );
BOOL gxd_sky_Save( gxd_sky_t* sky, char* tFileName );
BOOL gxd_sky_Load( gxd_sky_t* sky, char* tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
void gxd_sky_DrawForSkyBox( gxd_sky_t* sky );
void gxd_sky_DrawForLensFlare( gxd_sky_t* sky, void* tWorld );
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
typedef struct gxd_t {

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

	IDirectInput8A *mDirectInput;
	IDirectInputDevice8A *mKeyboard;
	BYTE mKeyboardImmediateData[256];
	DWORD mKeyboardBufferedDataNum;
	DIDEVICEOBJECTDATA mKeyboardBufferedData[32];


	HINSTANCE mCompressLibrary;
	FCompressBound mFCompressBound;
	FCompress mFCompress;
	FUncompress mFUncompress;


} gxd_t;

void gxd_InitForSound( void );
BOOL gxd_Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, BOOL tUseFog, D3DXFONT_DESC *tFontInfo, int *tRESULT );
void gxd_Free( void );
//float GetRandomNumber( float tMinValue, float tMaxValue );
//float GetTotalElapsedSeconds( void );
//void ChangeViewLength( float tNearPlane, float tFarPlane );
//BOOL SetCameraPosition( float tCameraEyeX, float tCameraEyeY, float tCameraEyeZ, float tCameraLookX, float tCameraLookY, float tCameraLookZ );
//void ChangeCameraForHorizon( float tRA );
//void ChangeCameraForVertical( float tRA );
//void ChangeCameraForForward( float tFD );
//void SetDefaultMaterial( void );
//void SetPresentMaterial( D3DXCOLOR tColor );
//void SetPresentMaterialForSpecular( float* a2, float a3 );
//void ChangeLight( D3DVECTOR a2, D3DXCOLOR a3, D3DCOLORVALUE a4 );
////void SetDefaultLight( void );
//void SetAmbientLight( int tAmbientSort, D3DXCOLOR tAmbientValue );
////void SetAmbientLight( int tAmbientSort, float r, float g, float b, float a );
////void SetAmbientLight( int tAmbientSort, int z );
//void OffAmbientLight( void );
//void SetCameraSpecularEffect( float a2, float a3 );
//void OffCameraSpecularEffect();
//BYTE GetShadowIntensityValueForWorld( void );
//BYTE GetShadowIntensityValueForObject( void );
//void ChangeFogEffect( BYTE* a2, float a3 );
//void ChangeTextureFilter( DWORD a2, DWORD a3, DWORD a4 );
BOOL gxd_ReadyForDrawing( int *tRESULT );
void gxd_BeginForDrawing( gxd_sky_t* tSKY );
void gxd_EndForDrawing( void );
//
////void BeginForHighShadow( void );
////void EndForHighShadow( void );
//
//void BeginForLowShadow( void );
//void EndForLowShadow( void );
//
//void BeginForPOBJECT( void );
//void EndForPOBJECT( void );
//
//void ProcessForFilter( void );
//
void gxd_BeginFor2D( void );
void gxd_EndFor2D( void );
//
//
int gxd_GetStringLength( const char *tString );
void gxd_DrawString( const char *tString, int tX, int tY, D3DCOLOR tColor, int tOutLineSort );
//
//void SaveScreenToBMP( char *tFileName );
//void SaveScreenToJPG( char *tFileName );
//
//
//
//void CalculateFrustum( void );
//BOOL CheckPointInFrustum( float tPoint[3] );
//BOOL CheckPointInFrustumWithoutFarPlane( float tPoint[3] );
//BOOL CheckSphereInFrustum( float tCenter[3], float tRadius );
//BOOL CheckSphereInFrustum( D3DXVECTOR3 *tCenter, float tRadius );
//BOOL CheckSphereInFrustumForWorld( float tCenter[3], float tRadius );
//BOOL CheckBoxInFrustum( float tBoxMin[3], float tBoxMax[3] );
//
//void TrisProjection( float rkD[3], float akV[3][3], float *rfMin, float *rfMax );
//void BoxProjection( float rkAxis[3], float rkOrigin[3], float akAxis[3][3], float afExtent[3], float *rfMin, float *rfMax );
//
//BOOL CheckCollisionForRayBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
//BOOL CheckCollisionForSegmentBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
//BOOL CheckCollisionForWorldTrisBox( WORLDTRIS_FOR_GXD *tWorldTris, float tBoxMin[3], float tBoxMax[3] );
//BOOL CheckCollisionForBoxBox( float tBoxMin01[3], float tBoxMax01[3], float tBoxMin02[3], float tBoxMax02[3] );
//BOOL CheckCollisionForMouseBox( int tX, int tY, float tBoxMin[3], float tBoxMax[3] );
//BOOL CheckCollisionForRayMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
//BOOL CheckCollisionForSegmentMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
//BOOL CheckCollisionForWorldTrisMS( WORLDTRIS_FOR_GXD *tWorldTris, MESHSIZE_FOR_GXD *tMeshSize );
//BOOL CheckCollisionForMSMS( MESHSIZE_FOR_GXD *tMeshSize01, MESHSIZE_FOR_GXD *tMeshSize02 );
//BOOL CheckCollisionForMouseMS( int tX, int tY, MESHSIZE_FOR_GXD *tMeshSize );
//BOOL CheckCollisionForSphereSphere( float tCenter01[3], float tRadius01, float tCenter02[3], float tRadius02 );
//
//BOOL GetCompressSize( DWORD tOriginalSize, BYTE *tOriginal, DWORD *tCompressSize );
//BOOL Compress( DWORD tOriginalSize, BYTE *tOriginal, DWORD tCompressSize, BYTE *tCompress );
//BOOL Decompress( DWORD tCompressSize, BYTE *tCompress, DWORD tOriginalSize, BYTE *tOriginal );
//
//void ChangeFilterTextureSize(int Width, int Height);
//void ProcessForFilter(float a6, float a7, float a8, int a9, float a10, int a11, int a12, float a13);
//
//void UpdateForInputSystem( BOOL tApplicationActive );
//
//BOOL WorldCoordToScreenCoord( float tCoord[3], int *tX, int *tY );





#ifdef __cplusplus
}
#endif

#endif //GXDC_HEADER_H