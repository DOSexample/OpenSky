#include "H01_Application.h"
#include "CString.h"
#include "test_mobject.h"
#include "test_sobject.h"
#include "test_sobject_old.h"

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
float hPreSecondsForLogic;
float hPresentFrameSeconds;
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
			switch ((wPrm & 0xFFF0))
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

BOOL ApplicationInit( HINSTANCE hThis, HWND hWnd )
{
    SetCurrentDirectory( ROOT_DIR );

    mGXD.InitForSound();

    D3DXFONT_DESC tFont;
    char tString[100];
    int tResult;
    
    memset( &tFont, 0, sizeof(D3DXFONT_DESC) );
    tFont.Height = 16;
    tFont.Width = 5;
    tFont.Weight = 0;
    tFont.MipLevels = 1;
    tFont.Italic = 0;
    tFont.CharSet = 1;
    tFont.OutputPrecision = 0;
    tFont.Quality = 5;
    tFont.PitchAndFamily = 0;
    strcpy( tFont.FaceName, "MS Sans Serif" );

    hMainWindow = hWnd;
    hMainInstance = hThis;
    if ( !mGXD.Init( hFullScreen, hMainInstance, hMainWindow, RES_WIDTH, RES_HEIGHT, 1.0f, 10000.0f, FALSE, &tFont, &tResult ) )
    {
        sprintf( tString, "[Error::mGXD.Init(%d)]", tResult );
        return MessageBoxA( tString );
    }
    if ( !TW2AddIn::mGXD.InitForAddIn( RES_WIDTH, RES_HEIGHT, 1.0f, 10000.0f, mGXD.mDirect3D, mGXD.mGraphicDevice, tResult ) )
    {
        sprintf( tString, "[Error::TW2AddIn::mGXD.InitForAddIn(%d)]", tResult );
        return MessageBoxA( tString );
    }
    
    hPresentElapsedSeconds = mGXD.GetTotalElapsedSeconds();
    hPostSecondsForLogic = hPresentElapsedSeconds;
    hPresentFrameSeconds = hPresentElapsedSeconds;
    hPreSecondsForLogic = 0.033333335f;

    mGXD.mCameraEye = D3DXVECTOR3( 0, 5, -28 );
    mGXD.mCameraLook = D3DXVECTOR3( 0, 10, 0 );
    return TRUE;
}

void ApplicationFree( void )
{
    mGXD.Free();
}

void ApplicationMain( void )
{
    float tFrameSeconds;

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
   
    //mGXD.UpdateForInputSystem( hActiveProgram ); //update d3d input
    //mTS_INPUT.KEYBOARD();//update game input for key board
    tFrameSeconds = 0.0f;
    while ( TRUE )
    {
        //mMAIN.Logic( hPreSecondsForLogic );//update game logic
        tFrameSeconds = tFrameSeconds + hPreSecondsForLogic;
        hPostSecondsForLogic = hPostSecondsForLogic + hPreSecondsForLogic;
        if ( ( hPresentElapsedSeconds - hPostSecondsForLogic ) < hPreSecondsForLogic )
        {
            break;
        }
        
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
        //POINTER::Set2();
    }

	UnregisterClass( PLATFORM_NAME, wCls.hInstance );

    ApplicationFree();
    return EXIT_SUCCESS;
}

void ApplicationRender( float dTime )
{

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

    test_mobject_func();
    test_sobject_func();
    test_sobject_old_func();
    test_mobject_sobject_func();

    mGXD.BeginFor2D();
    {
        mGXD.DrawString( CString( "LEFT: " ), 10, 10, D3DCOLOR_RGBA(255, 255, 0, 255), 0);
        mGXD.DrawString( CString( "RIGHT: " ), RES_WIDTH-50, 10, D3DCOLOR_RGBA(255, 255, 0, 255), 0);
    }
    mGXD.EndFor2D();

    mGXD.EndForDrawing();
}
