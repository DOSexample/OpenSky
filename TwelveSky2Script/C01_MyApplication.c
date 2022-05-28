#include "Header.h"
#include <GXD/CHeader.h>

#define RES_WIDTH 1024
#define RES_HEIGHT 768
#define PLATFORM_NAME "TwelveSky2"
#define PLATFORM_TITLE "TwelveSky2"
BOOL hFullScreen = FALSE;
BOOL hAbortProgram = FALSE;
gxd_t* sGXD;

LRESULT CALLBACK WinMainProcedureS( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm );
BOOL ApplicationInit( HINSTANCE hThis, HWND hWnd );
void ApplicationFree( void );
void ApplicationMain( void );

#define ROOT_DIR "E:\\GAME\\12SKY2\\12SKY2ELW"
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    SetCurrentDirectory( ROOT_DIR );

    WNDCLASSEX wCls = { 0 };
	MSG nMss = { 0 };
	RECT rc;
	HWND hWnd;
	int X = 0, Y = 0, Width = 1024, Height = 768;
	DWORD dwExStyle = WS_EX_APPWINDOW;
	DWORD dwStyle = WS_POPUP;

    wCls.cbSize = sizeof( WNDCLASSEX );
    wCls.style = CS_HREDRAW | CS_VREDRAW;
    wCls.lpfnWndProc = WinMainProcedureS;
    wCls.cbClsExtra = 0;
    wCls.cbWndExtra = 0;
    wCls.hInstance = hInstance;
    //wCls.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_TWELVESKY2 ) );
    //wCls.hCursor = LoadCursor( hInstance, MAKEINTRESOURCE( IDC_CURSOR01 ) );
    wCls.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wCls.lpszMenuName = 0;
    wCls.lpszClassName = PLATFORM_NAME;
    wCls.hIconSm = 0;
    if ( !RegisterClassEx( &wCls ) )
    {
        return MessageBoxS( "[Error::RegisterClassEx()]" );
    }
    //hFullScreen = TRUE;
    if ( !hFullScreen )
    {
        dwExStyle = 0;
        dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
        //dwExStyle = WS_EX_ACCEPTFILES;
        if ( !SetRect( &rc, 0, 0, Width, Height ) )
        {
            return MessageBoxS( "[Error::SetRect()]" );
        }
        if ( !AdjustWindowRect( &rc, dwStyle, 0 ) )
        {
            return MessageBoxS( "[Error::AdjustWindowRect()]" );
        }
        Width = rc.right - rc.left;
        Height = rc.bottom - rc.top;

        #ifndef TCC_APP
        X = GetSystemMetrics( SM_CXSCREEN ) - Width + 20;
        Y = 0;
        #else
        X = GetSystemMetrics( SM_CXSCREEN ) / 2 - ( rc.right - rc.left ) / 2;
        Y = GetSystemMetrics( SM_CYSCREEN ) / 2 - ( rc.bottom - rc.top ) / 2;
        #endif
    }
    hWnd = CreateWindowEx( dwExStyle, PLATFORM_NAME, PLATFORM_TITLE, dwStyle, X, Y, Width, Height, 0, 0, hInstance, 0 );
    if ( !hWnd )
        return MessageBoxS( "[Error::CreateWindowEx()]" );

    ShowWindow( hWnd, nShowCmd );
    UpdateWindow( hWnd );
    if( !ApplicationInit( hInstance, hWnd ) )
    {
        ApplicationFree();
        return MessageBoxS( "[Error::ApplicationInit()]" );
    }
    
	if ( GetForegroundWindow () != hWnd) {
		HWND hActiveWnd = GetForegroundWindow ();
		if (hActiveWnd != NULL) {
			DWORD dwForegroundThreadId = GetWindowThreadProcessId (hActiveWnd, NULL);
			DWORD dwCurrentThreadId = GetCurrentThreadId ();

			if (dwForegroundThreadId != dwCurrentThreadId) {
				if (AttachThreadInput (dwCurrentThreadId, dwForegroundThreadId, TRUE)) {
					BringWindowToTop (hWnd);
					AttachThreadInput (dwCurrentThreadId, dwForegroundThreadId, FALSE);
				}
			}
		}
	}

	SendMessage( ImmGetDefaultIMEWnd( hWnd ), WM_IME_CONTROL, (WPARAM) IMC_CLOSESTATUSWINDOW, (LPARAM) 0 );
    
    while ( TRUE )
    {
		if( PeekMessage( &nMss, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &nMss );
			DispatchMessage( &nMss );
    	    if ( nMss.message == WM_QUIT )
    		    break;
		}
		else
		{
            ApplicationMain();
			if( hAbortProgram )
				break;
		}
        //Update Mouse Cursor
        //POINTER::Set2();
    }

	UnregisterClass( PLATFORM_NAME, wCls.hInstance );

    ApplicationFree();
    return EXIT_SUCCESS;
}

#define CLICK_X_TO_CLOSE_WINDOW
LRESULT CALLBACK WinMainProcedureS( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    switch ( nMss )
    {
    //case WM_ACTIVATEAPP:
    //    hActiveProgram = (BOOL)wPrm;
    //    return 0;
	#ifndef CLICK_X_TO_CLOSE_WINDOW
    case WM_CLOSE:
        return 0;
	#endif
    case WM_DESTROY:
		hAbortProgram = TRUE;
		return 0;
	case WM_QUIT:
		return 0;
	case WM_SYSCOMMAND:
		if ( !hFullScreen )
		{
			switch ( ( wPrm & 0xFFF0 ) )
			{
			case SC_MOVE:
			case SC_MINIMIZE:
			case SC_MAXIMIZE:
			case SC_RESTORE:
			#ifdef CLICK_X_TO_CLOSE_WINDOW
			case SC_CLOSE:
			#endif
				break;
			default:
				return 0;
			}
			break;
		}
		return 0;
	//
    //case WM_KEYDOWN:
    //    //OutputDebugStringA( String( "PressDown: " ) + (int)wPrm + " \n" );
    //    return 0;
    //    
    //case WM_KEYUP:
    //    //OutputDebugStringA( String( "PressUp: " ) + (int)wPrm + " \n" );
    //    return 0;
    }

	return DefWindowProcA( hWnd, nMss, wPrm, lPrm );
}

BOOL ApplicationInit( HINSTANCE hThis, HWND hWnd )
{
    srand( (unsigned int)time(NULL) );
        
    #ifndef TCC_APP
    sGXD = GetGXDInstanceForScript();

    SetHostHINSTANCE(hThis);
    SetHostHWND(hWnd);
    #endif

    gxd_InitForSound();

    D3DXFONT_DESC tFont;
    int tResult;
    
    memset( &tFont, 0, sizeof(D3DXFONT_DESC) );
    tFont.Height = 16;
    tFont.Width = 5;
    tFont.Weight = FW_DONTCARE;
    tFont.MipLevels = 1;
    tFont.Italic = 0;
    tFont.CharSet = DEFAULT_CHARSET;
    tFont.OutputPrecision = OUT_DEFAULT_PRECIS;
    tFont.Quality = CLEARTYPE_QUALITY;
    tFont.PitchAndFamily = DEFAULT_PITCH;
    strcpy( tFont.FaceName, "MS Sans Serif" );

    if ( !gxd_Init( 0, hThis, hWnd, 1024, 768, 1.0f, 10000.0f, FALSE, &tFont, &tResult ) )
    {
        return MessageBoxS( "[Error::mGXD.Init(%d)]", tResult );
    }

    //if ( !sTW2_GXD.InitForAddIn( 1024, 768, 1.0f, 10000.0f, mGXD.mDirect3D, mGXD.mGraphicDevice, tResult ) )
    //{
    //    return MessageBoxS( "[Error::TW2AddIn::mGXD.InitForAddIn(%d)]", tResult );
    //}

    //mGXD.mCameraEye = D3DXVECTOR3( 0, 5, -28 );
    //mGXD.mCameraLook = D3DXVECTOR3( 0, 10, 0 );
    return TRUE;
}

void ApplicationFree( void )
{
    gxd_Free();
}

void ApplicationMain( void )
{
    int tResult;
    if( !gxd_ReadyForDrawing( &tResult ) )
    {
        if( tResult == 1 )
        {
            //tw2_OnLostDevice();
        }
        return;
    }
    gxd_BeginForDrawing(0);

    gxd_BeginFor2D();
    gxd_DrawString( "2", 100, 30, 0xFFFF0000, 2 );
    gxd_EndFor2D();

    gxd_EndForDrawing();
}
