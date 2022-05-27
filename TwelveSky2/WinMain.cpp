#include "H01_Application.h"

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
    WNDCLASSEX wCls = { 0 };
	MSG nMss = { 0 };
	RECT rc;
	HWND hWnd;
	int X = 0, Y = 0, Height = 0, Width = 0;
	DWORD dwExStyle = WS_EX_APPWINDOW;
	DWORD dwStyle = WS_POPUP;

    wCls.cbSize = sizeof( WNDCLASSEX );
    wCls.style = CS_HREDRAW | CS_VREDRAW;
    wCls.lpfnWndProc = WinMainProcedure;
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
        return MessageBox( "[Error::RegisterClassEx()]" );
    }
    if ( !hFullScreen )
    {
        dwExStyle = 0;
        dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
        dwExStyle = WS_EX_ACCEPTFILES;
        if ( !SetRect( &rc, 0, 0, RES_WIDTH, RES_HEIGHT ) )
        {
            return MessageBox( "[Error::SetRect()]" );
        }
        if ( !AdjustWindowRect( &rc, dwStyle, 0 ) )
        {
            return MessageBox( "[Error::AdjustWindowRect()]" );
        }
        Width = rc.right - rc.left;
        Height = rc.bottom - rc.top;
        X = GetSystemMetrics( SM_CXSCREEN ) / 2 - ( rc.right - rc.left ) / 2;
        Y = GetSystemMetrics( SM_CYSCREEN ) / 2 - ( rc.bottom - rc.top ) / 2;
    }
    hWnd = CreateWindowEx( dwExStyle, PLATFORM_NAME, PLATFORM_TITLE, dwStyle, X, Y, Width, Height, 0, 0, hInstance, 0 );
    if ( !hWnd )
        return MessageBoxA( "[Error::CreateWindowEx()]" );
    if( !ApplicationInit( hInstance, hWnd ) )
    {
        ApplicationFree();
        return MessageBoxA( "[Error::ApplicationInit()]" );
    }

    ShowWindow( hWnd, nShowCmd );
    UpdateWindow( hWnd );

    return ApplicationLoop( wCls );
}
