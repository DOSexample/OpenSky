#include <GXD/Header.h>
#include <GXD/CHeader.h>

#define CLASS MOTION_FOR_GXD

#define CALL( func, ... ) \
	CLASS* tMotion = reinterpret_cast<CLASS*>(motion); \
	tMotion->func( __VA_ARGS__ );

#define CALL_RET( func, ret, ... ) \
	CLASS* tMotion = reinterpret_cast<CLASS*>(motion); \
	ret = tMotion->func( __VA_ARGS__ );

void gxd_motion_Init( gxd_motion_t* motion )
{
	CALL( Init );
}

void gxd_motion_Free( gxd_motion_t* motion )
{
	CALL( Free );
}

BOOL gxd_motion_LoadFromG3M( gxd_motion_t* motion, const char *tFileName, int tLoadSort )
{
	BOOL ret;
	CALL_RET( LoadFromG3M, ret, (char*)tFileName, tLoadSort );
	return ret;
}

BOOL gxd_motion_Save( gxd_motion_t* motion, const char *tFileName )
{
	BOOL ret;
	CALL_RET( Save, ret, (char*)tFileName );
	return ret;
}

BOOL gxd_motion_Save2( gxd_motion_t* motion, HANDLE hFile )
{
	BOOL ret;
	CALL_RET( Save, ret, hFile );
	return ret;
}

BOOL gxd_motion_Load( gxd_motion_t* motion, const char *tFileName )
{
	BOOL ret;
	CALL_RET( Load, ret, (char*)tFileName );
	return ret;
}

//BOOL gxd_motion_SaveToMOTION2( gxd_motion_t* motion, const char *tFileName )
//{
//	BOOL ret;
//	CALL_RET( SaveToMOTION2, ret, (char*)tFileName );
//	return ret;
//}