#include <Windows.h>

#define CLICK_X_TO_CLOSE_WINDOW
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    //switch ( nMss )
    //{
    //case WM_ACTIVATEAPP:
    //    hActiveProgram = (BOOL)wPrm;
    //    return 0;
	//#ifndef CLICK_X_TO_CLOSE_WINDOW
    //case WM_CLOSE:
    //    return 0;
	//#endif
    //case WM_DESTROY:
	//	hAbortProgram = TRUE;
	//	return 0;
	//case WM_QUIT:
	//	return 0;
	//case WM_SYSCOMMAND:
	//	if ( !hFullScreen )
	//	{
	//		switch ((wPrm & 0xFFF0))
	//		{
	//		case SC_MOVE:
	//		case SC_MINIMIZE:
	//		case SC_MAXIMIZE:
	//		case SC_RESTORE:
	//		#ifdef CLICK_X_TO_CLOSE_WINDOW
	//		case SC_CLOSE:
	//		#endif
	//			break;
	//		default:
	//			return 0;
	//		}
	//		break;
	//	}
	//	return 0;
	//
    //case WM_KEYDOWN:
    //    //OutputDebugStringA( String( "PressDown: " ) + (int)wPrm + " \n" );
    //    return 0;
    //    
    //case WM_KEYUP:
    //    //OutputDebugStringA( String( "PressUp: " ) + (int)wPrm + " \n" );
    //    return 0;
    //}

	return DefWindowProc( hWnd, nMss, wPrm, lPrm );
}