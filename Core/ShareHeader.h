
//-------------------------------------------------------------------------------------------------
//_WIN32_WINDOWS
//-------------------------------------------------------------------------------------------------
#define _WIN32_WINDOWS												0x0500
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WIN32_LEAN_AND_MEAN
//-------------------------------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DIRECTINPUT_VERSION
//-------------------------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION											0x0800
//-------------------------------------------------------------------------------------------------

#ifdef _DEBUG
    #define D3D_DEBUG_INFO
#endif

#ifndef SAFE_RELEASE
    #define SAFE_RELEASE(p) { if(p) { p->Release(); p = NULL; } }
#endif

#ifndef SAFE_DELETE
    #define SAFE_DELETE(p)  { if(p) { delete p; p = NULL; } }
#endif

#ifndef HEAP_ALLOC
	#define HEAP_ALLOC( type, ptr, size ) ( ptr = (type)HeapAlloc( GetProcessHeap(), 0, size ) )
	#define HEAP_FREE( ptr ) if( ptr ){ HeapFree( GetProcessHeap(), 0, ptr ); ptr = NULL; }
#endif

#ifdef _DEBUG
	#define DEBUGMSG(x) printf x
	#define TRACEMSG() printf( "[%s](%s:%d) TRACE\n", __FUNCTION__, __FILE__, __LINE__  )
#else
	#define DEBUGMSG(x)
	#define TRACEMSG()
#endif

//#include "Atmosphere.h"
//#include "RenderStateMgr.h"
//#include "TextureStageStateMgr.h"
//#include "BillboardStringMgr.h"
//#include "Frustum.h"
//#include "MiniMap.h"
//#include "WorldMobjectScale.h"

//-------------------------------------------------------------------------------------------------
//DEFINE_GXD_VERSION
//-------------------------------------------------------------------------------------------------
#define GXD_VERSION													"VER3.0"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_MACRO
//-------------------------------------------------------------------------------------------------
#define F_EPSILON													0.0001f
#define FLOAT_EQUAL( a, b )											( ( ( ( b) - F_EPSILON ) < ( a) ) && ( ( a) < ( ( b) + F_EPSILON ) ) )
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#include <Ole2.h>
#include <io.h>
#include <fcntl.h>
#include <ddraw.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include <dinput.h>
#ifdef __cplusplus
#include <map>
#include <string>
#endif
#include <shellapi.h>
#include <shlwapi.h>
#include <vorbis\\vorbisfile.h>

#ifdef __cplusplus
#pragma comment( lib, "d3d9.lib" )
#ifndef _DEBUG
	#pragma comment( lib, "d3dx9.lib" )
#else
	#pragma comment( lib, "d3dx9d.lib" )
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dsound.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "Shlwapi.lib" )
#pragma comment( lib, "ogg_static.lib" )
#pragma comment( lib, "vorbisfile_static.lib" )
#endif



#ifndef SHARE_HEADER1_H
#define SHARE_HEADER1_H
//-------------------------------------------------------------------------------------------------
//DEFINE_WORLD_FVF
//-------------------------------------------------------------------------------------------------
const static DWORD WORLD_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
}
SKINVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINWEIGHT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mBoneIndex[4];
	float mBlendValue[4];
}
SKINWEIGHT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckTwoSide;
	BOOL mCheckRadiation;
	float mRadiationSpeed;
	float mRadiationLowLimit[4];
	float mRadiationHighLimit[4];
	BOOL mCheckLightBright;
	BOOL mCheckCameraSpecularEffect;
	int mCameraSpecularEffectSort;
	float mCameraSpecularEffectMaterialValue[4];
	float mCameraSpecularEffectMaterialPower;
	float mCameraSpecularEffectLightAddValue;
	BOOL mCheckTextureAnimation;
	float mTextureAnimationSpeed;
	BOOL mCheckUVScroll1;
	int mUVScrollSort1;
	float mUVScrollSpeed1;
	BOOL mCheckBillboard;
	int mBillboardSort;
	BOOL mCheckUVScroll2;
	int mUVScrollSort2;
	float mUVScrollSpeed2;
}
SKINEFFECT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINSIZE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	float mCenter[3];
	float mRadius;
}
SKINSIZE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINLODVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
	float mBoneIndex[4];
	float mBlendValue[4];
}
SKINLODVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
}
MESHVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckTwoSide;
	BOOL mCheckRadiation;
	float mRadiationSpeed;
	float mRadiationLowLimit[4];
	float mRadiationHighLimit[4];
	BOOL mCheckLightBright;
	BOOL mCheckCameraSpecularEffect;
	int mCameraSpecularEffectSort;
	float mCameraSpecularEffectMaterialValue[4];
	float mCameraSpecularEffectMaterialPower;
	float mCameraSpecularEffectLightAddValue;
	BOOL mCheckTextureAnimation;
	float mTextureAnimationSpeed;
	BOOL mCheckUVScroll1;
	int mUVScrollSort1;
	float mUVScrollSpeed1;
	BOOL mCheckBillboard;
	int mBillboardSort;
	BOOL mCheckUVScroll2;
	int mUVScrollSort2;
	float mUVScrollSpeed2;
}
MESHEFFECT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHSIZE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mAxis[3][3];
	float mExtent[3];
	float mCenter[3];
	float mRadius;
}
MESHSIZE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_PARTICLEVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	DWORD mC;
	float mT[2];
}
PARTICLEVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_PARTICLE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckValidState;
	float mOneLifeTime;
	float mLocation[3];
	float mVelocity[3];
	float mWeight;
	float mSize;
	float mColor[4];
}
PARTICLE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_DRAWSHADOWVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
    float mV[3];
}
DRAWSHADOWVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_DRAWSHADOWVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
    float mV[3];
    float mN[3];
	DWORD mC;
}
DRAWSHADOWVERTEX2_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_WORLDVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT1[2];
	float mT2[2];
}
WORLDVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF__WORLDINTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct _WORLDINTEX_FOR_GXD
{
	DWORD w1, w2, w3;
	#ifdef __cplusplus
	_WORLDINTEX_FOR_GXD( )
		:w1( 0), w2( 0), w3( 0)
	{
	}
	#endif
}
WORLDINTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_G3WTRIS_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mTextureIndex;
	int mVertexIndex[3];
	int mUVIndex[3];
}
G3WTRIS_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_G3WMESH_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	char mName[256];
	int mVertexNum;
	int mUVNum;
	int mTrisNum;
	float *mVertex;
	float *mUV;
	G3WTRIS_FOR_GXD *mTris;
}
G3WMESH_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_WORLDTRIS_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mTextureIndex;
	WORLDVERTEX_FOR_GXD mVertex[3];
	float mPlaneInfo[4];
	float mSphereInfo[4];
}
WORLDTRIS_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_QUADTREENODE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	int mTrisNum;
	int *mTrisIndex;
	int mChildNodeIndex[4];
}
QUADTREENODE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MOBJECTINFO_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	float mCoord[3];
	float mAngle[3];
	float mFrame;
	float mPostTimeForEffect;
}
MOBJECTINFO_FOR_GXD;
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKYBOXVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mT[2];
}
SKYBOXVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_LENSFLAREVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[4];
	float mT[2];
}
LENSFLAREVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_COMPRESS_FUNCTION_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef DWORD ( * FCompressBound )( DWORD tSourceLength );
typedef int ( * FCompress )( BYTE *tDest, DWORD *tDestLength, BYTE *tSource, DWORD tSourceLength, int tLevel );
typedef int ( * FUncompress )( BYTE *tDest, DWORD *tDestLength, BYTE *tSource, DWORD tSourceLength );
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_GXD
//-------------------------------------------------------------------------------------------------
//MAX_SAVE_SHADOW_VERTEX_NUM
#define MAX_SAVE_SHADOW_VERTEX_NUM									10000
//MAX_DRAW_SHADOW_TRIS_NUM
#define MAX_DRAW_SHADOW_TRIS_NUM									10000
//MAX_DRAW_SHADOW_VERTEX_NUM
#define MAX_DRAW_SHADOW_VERTEX_NUM									100000

extern D3DVERTEXELEMENT9 mVertexElementForSKIN2[];
//extern D3DVERTEXELEMENT9 mVertexElementForSKIN2SHADOW[];



#endif //SHARE_HEADER1_H