#include "H01_Application.h"
#include "CString.h"

#pragma comment( lib, "GXD.lib" )
#pragma comment( lib, "TW2AddIn_MT.lib" )
#pragma comment( lib, "SilverLining-MT.lib" )

BOOL hFullScreen = FALSE;
BOOL hActiveProgram = FALSE;
BOOL hAbortProgram = FALSE;
BOOL hRenderSobject25 = FALSE;
HWND hMainWindow;
HINSTANCE hMainInstance;
float hPresentElapsedSeconds;
float hPostSecondsForLogic;
float hPresentFrameSeconds;
float hPreSecondsForLogic;
#define ROOT_DIR "E:\\GAME\\12SKY2\\12SKY2ELW"

#define CLICK_X_TO_CLOSE_WINDOW
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    switch ( nMss )
    {
    case WM_ACTIVATEAPP:
        hActiveProgram = (BOOL)wPrm;
        return 0;
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

    case WM_KEYDOWN:
        //OutputDebugStringA( String( "PressDown: " ) + (int)wPrm + " \n" );
        return 0;
        
    case WM_KEYUP:
        //OutputDebugStringA( String( "PressUp: " ) + (int)wPrm + " \n" );
        return 0;
    }

	return DefWindowProc( hWnd, nMss, wPrm, lPrm );
}

#define MB_INIT_ERROR( initFunction ) \
if ( !initFunction.Init() ) \
    return MessageBox( "[Error::"#initFunction".Init()]" ); \

BOOL ApplicationInit( HINSTANCE hThis, HWND hWnd )
{
    SetCurrentDirectory( ROOT_DIR );

    srand( (unsigned int)time(NULL) );
    mGXD.InitForSound();

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

    hMainWindow = hWnd;
    hMainInstance = hThis;
    if ( !mGXD.Init( hFullScreen, hMainInstance, hMainWindow, mMYINFO.mScreenXSize, mMYINFO.mScreenYSize, 1.0f, 10000.0f, FALSE, &tFont, &tResult ) )
    {
        return MessageBox( "[Error::mGXD.Init(%d)]", tResult );
    }
    if ( !TW2AddIn::mGXD.InitForAddIn( mMYINFO.mScreenXSize, mMYINFO.mScreenYSize, 1.0f, 10000.0f, mGXD.mDirect3D, mGXD.mGraphicDevice, tResult ) )
    {
        return MessageBox( "[Error::TW2AddIn::mGXD.InitForAddIn(%d)]", tResult );
    }

    MB_INIT_ERROR( mFONTDATA );
    MB_INIT_ERROR( mFONTCOLOR );
    MB_INIT_ERROR( mPOINTER );
    MB_INIT_ERROR( mGDATA );
    MB_INIT_ERROR( mMYINFO );

    MB_INIT_ERROR( mMAIN );
    mMAIN.Start();
    
    hPresentElapsedSeconds = mGXD.GetTotalElapsedSeconds();
    hPostSecondsForLogic = hPresentElapsedSeconds;
    hPresentFrameSeconds = hPresentElapsedSeconds;
    hPreSecondsForLogic = 0.033333335f;

    mGXD.mCameraEye = D3DXVECTOR3( 0, 5, -28 );
    mGXD.mCameraLook = D3DXVECTOR3( 0, 10, 0 );
    return TRUE;
}
#undef MB_INIT_ERROR

void ApplicationFree( void )
{
    TW2AddIn::mGXD.Free();
    mGXD.Free();
}

int ApplicationLoop( WNDCLASSEX wCls )
{
    MSG nMss = { 0 };
    while ( TRUE )
    {
		if( PeekMessage( &nMss, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &nMss );
			DispatchMessage( &nMss );
    	    if ( nMss.message == WM_QUIT )
    	    {
    		    break;
    	    }
		}
		else
		{
            ApplicationMain();
			if( hAbortProgram )
				break;
		}
        //Update Mouse Cursor
        mPOINTER.Set();
    }

	UnregisterClass( PLATFORM_NAME, wCls.hInstance );

    ApplicationFree();
    return EXIT_SUCCESS;
}

#define DWFPS
#ifdef DWFPS
DWORD dwOldCount = 0L;
DWORD dwFPS = 0L;
CString strFPS;
#endif
void ApplicationMain( void )
{
    float tFrameSeconds;

    #ifdef DWFPS
    if ( GetTickCount() - dwOldCount > 1000 )
    {
        dwOldCount = GetTickCount();
        SetWindowText( ::hMainWindow, strFPS.Sprintf( "%s | FPS : %d ", PLATFORM_NAME, dwFPS ) );
        dwFPS = 0;
    }
    dwFPS++;
    #endif

    hPresentElapsedSeconds = mGXD.GetTotalElapsedSeconds();
    if ( ( hPresentElapsedSeconds - hPostSecondsForLogic ) < hPreSecondsForLogic )
    {
        return;
    }

    //XTrap/GameGuard TickCount
    //if (GetTickCount() - dword_7949D8 > 2000)
    //{
    // dword_7949D8 = GetTickCount();
    // sub_6C6C60(2000);
    //}
   
    mGXD.UpdateForInputSystem( hActiveProgram ); //update d3d input
    //mTS_INPUT.KEYBOARD();//update game input for key board
    tFrameSeconds = 0.0f;
    while ( TRUE )
    {
        mMAIN.Logic( hPreSecondsForLogic );//update game logic
        tFrameSeconds = tFrameSeconds + hPreSecondsForLogic;
        hPostSecondsForLogic = hPostSecondsForLogic + hPreSecondsForLogic;
        if ( ( hPresentElapsedSeconds - hPostSecondsForLogic ) < hPreSecondsForLogic )
        {
            break;
        }
        
    }
	if( hAbortProgram )
	{
		return;
	}
    if ( hActiveProgram )
    {
        ApplicationRender( tFrameSeconds );//render it
    }
    if ( hPresentElapsedSeconds - hPresentFrameSeconds >= 60.0f )
    {
        hPresentFrameSeconds = hPresentElapsedSeconds;
        //mGDATA.ProcessForMemory( hPresentElapsedSeconds, 300.0f );
    }
}

void ApplicationRender( float dTime )
{
    if( mMAIN.mMainMode < 1 || mMAIN.mMainMode > MAX_MAIN_CLICK_NUM )
        return;

    int tResult;
    if( !mGXD.ReadyForDrawing( &tResult ) )
    {
        if( tResult == 1 )
            TW2AddIn::mGXD.OnLostDevice();
        return;
    }

    //SetCamera
    {
        mGXD.mCameraEye = D3DXVECTOR3( 0, 5, -48 );
        mGXD.mCameraLook = D3DXVECTOR3( 0, 10, 0 );
    }

    //SetLight
    {
        mGXD.mLight.Type = D3DLIGHT_DIRECTIONAL;
        mGXD.mLight.Diffuse.r = 0.80000001f;
        mGXD.mLight.Diffuse.g = 0.80000001f;
        mGXD.mLight.Diffuse.b = 0.80000001f;
        mGXD.mLight.Diffuse.a = 1.0f;
        mGXD.mLight.Specular.r = 0.0f;
        mGXD.mLight.Specular.g = 0.0f;
        mGXD.mLight.Specular.b = 0.0f;
        mGXD.mLight.Specular.a = 1.0f;
        mGXD.mLight.Ambient.r = 0.80000001f;
        mGXD.mLight.Ambient.g = 0.80000001f;
        mGXD.mLight.Ambient.b = 0.80000001f;
        mGXD.mLight.Ambient.a = 1.0f;
        mGXD.mLight.Position.x = 0.0f;
        mGXD.mLight.Position.y = 0.0f;
        mGXD.mLight.Position.z = 0.0f;
        mGXD.mLight.Direction.x = -1.0f;
        mGXD.mLight.Direction.y = -1.0f;
        mGXD.mLight.Direction.z = -1.0f;
        D3DXVec3Normalize( &mGXD.mLight.Direction, &mGXD.mLight.Direction );
        mGXD.mLight.Range = 0.0f;
        mGXD.mLight.Falloff = 0.0f;
        mGXD.mLight.Attenuation0 = 0.0f;
        mGXD.mLight.Attenuation1 = 0.0f;
        mGXD.mLight.Attenuation2 = 0.0f;
        mGXD.mLight.Theta = 0.0f;
        mGXD.mLight.Phi = 0.0f;
    }

    TW2AddIn::mGXD.OnResetDevice();
    mGXD.BeginForDrawing( 0 );
    mGXD.mGraphicDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1.0f, 0 );
    mGXD.mGraphicDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );
    mGXD.mGraphicDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
    mGXD.mGraphicDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    TW2AddIn::mGXD.SetDefaultTextureSamplerState();
    if ( TW2AddIn::mGXD.mPresentShaderProgramNumber )
    {
        TW2AddIn::mGXD.mPresentShaderProgramNumber = 0;
        TW2AddIn::mGXD.mGraphicDevice->SetVertexShader( 0 );
        TW2AddIn::mGXD.mGraphicDevice->SetPixelShader( 0 );
    }
    TW2AddIn::mGXD.mCameraEye = mGXD.mCameraEye;
    TW2AddIn::mGXD.mCameraLook = mGXD.mCameraLook;
    TW2AddIn::mGXD.mCameraForward = mGXD.mCameraForward;
    TW2AddIn::mGXD.mViewMatrix = mGXD.mViewMatrix;
    TW2AddIn::mGXD.mPerspectiveMatrix = mGXD.mPerspectiveMatrix;
    TW2AddIn::mGXD.mWorldMatrix = mGXD.mWorldMatrix;
    TW2AddIn::mGXD.mLight = mGXD.mLight;
    TW2AddIn::mGXD.mMaterial = mGXD.mMaterial;
    TW2AddIn::mGXD.mDRAW_POLYGON_NUM = 0;

    mMAIN.Draw( dTime );

    mGXD.EndForDrawing();
}
