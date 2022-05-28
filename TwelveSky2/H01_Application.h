#pragma once

#include <ShareHeader.h>
#include <GXD/Header.h>
#include <TW2AddIn/Header.h>
#include <DXHelper.h>

#define PLATFORM_NAME "TwelveSky2"
#define PLATFORM_TITLE "TwelveSky2"
#define RES_WIDTH 1600
#define RES_HEIGHT 900

#include "Resource/resource.h"
#include "H03_GDATA.h"
#include "H03_GOBJECT.h"
#include "H05_MAIN.h"


extern BOOL hFullScreen;
extern BOOL hActiveProgram;
extern BOOL hAbortProgram;
extern BOOL hRenderSobject25;
extern HINSTANCE hMainInstance;
extern HWND hMainWindow;
extern float hPresentElapsedSeconds;
extern float hPostSecondsForLogic;
extern float hPresentFrameSeconds;
extern float hPreSecondsForLogic;

extern LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm );
extern BOOL ApplicationInit( HINSTANCE hThis, HWND hWnd );
extern void ApplicationFree( void );
extern int ApplicationLoop( WNDCLASSEX wCls );
extern void ApplicationMain( void );
extern void ApplicationRender( float dTime );


static int MessageBoxA( const char* fmt, ... )
{
    char tmp[1024];

	va_list args;
	va_start( args, fmt );
	vsprintf( tmp, fmt, args );
	va_end( args );

    ::MessageBoxA( 0, tmp, PLATFORM_NAME, MB_OK | MB_ICONERROR );
    return 0;
}

static float GetNewFrame( int tTotalFrame )
{
    if ( tTotalFrame < 1 ) return 0.0f;
    return (float)( (int)( hPresentElapsedSeconds * 30.0f ) % tTotalFrame );
}
















