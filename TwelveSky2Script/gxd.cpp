#include <GXD/Header.h>
#include <GXD/CHeader.h>

#define CALL( func, ... ) mGXD.func( __VA_ARGS__ );

#define CALL_RET( func, ret, ... ) ret = mGXD.func( __VA_ARGS__ );

void gxd_InitForSound( void )
{
	printf( ", %p\n",  &mGXD );
	CALL( InitForSound );
}

BOOL gxd_Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, BOOL tUseFog, D3DXFONT_DESC *tFontInfo, int *tRESULT )
{
	printf( "from\n" );
	BOOL ret;
	CALL_RET( Init, ret, tCheckFullScreen, tInstanceHandle, tWindowHandle, tScreenXSize, tScreenYSize, tNearPlane, tFarPlane, tUseFog, tFontInfo, tRESULT );
	printf( "end\n" );
	return ret;
}

void gxd_Free( void )
{
	CALL( InitForSound );
}

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
BOOL gxd_ReadyForDrawing( int *tRESULT )
{
	BOOL ret;
	CALL_RET( ReadyForDrawing, ret, tRESULT );
	return ret;
}
void gxd_BeginForDrawing( gxd_sky_t* tSKY )
{
	CALL( BeginForDrawing, (SKY_FOR_GXD*)tSKY );
}
void gxd_EndForDrawing( void )
{
	CALL( EndForDrawing );
}
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
void gxd_BeginFor2D( void )
{
	CALL( BeginFor2D );
}

void gxd_EndFor2D( void )
{
	CALL( EndFor2D );
}

int gxd_GetStringLength( const char *tString )
{
	int ret;
	CALL_RET( GetStringLength, ret, (char*)tString );
	return ret;
}

void gxd_DrawString( const char *tString, int tX, int tY, D3DCOLOR tColor, int tOutLineSort )
{
	CALL( DrawString, (char*)tString, tX, tY, tColor, tOutLineSort );
}

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


