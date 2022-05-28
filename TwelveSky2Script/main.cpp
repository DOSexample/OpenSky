#include "Header.h"
#include <GXD/Header.h>
#include <GXD/CHeader.h>
#include <TW2AddIn/Header.h>
#include "tcc-0.9.27/tcc.h"

#pragma comment( lib, "GXD.lib" )
#pragma comment( lib, "TW2AddIn_MT.lib" )
#pragma comment( lib, "SilverLining-MT.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "imm32.lib" )

extern void WatchDirectory( LPCWSTR path );
extern void UnWatchDirectory();

ts2_script_t* newScript;
bool reload = false;

#include <vector>
void HostReload()
{
    reload = true;

    std::string str = "";
    for (int i = 0; i < newScript->argc; i++ ) {
        str += newScript->argv[i];
        if ( i != (newScript->argc-1) )
        {
            str += " ";
        }
    }
    
    SetCurrentDirectory( newScript->startupDir );

    printf( "%s\n", newScript->startupDir );
    printf( "%s\n", str.c_str() );
    
    SendMessageA((HWND)newScript->hWnd, WM_DESTROY, 0, 0);
    UnWatchDirectory();
    //system(str.c_str());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Start the child process. 
    BOOL val = CreateProcessA(
        NULL,           // No module name (use command line)
        (LPSTR)str.c_str(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        newScript->startupDir,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
        );
    if( !val )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }
}

#include <exception>
int main( int argc, char** argv )
{
    WatchDirectory( L"..\\TwelveSky2Script\\" );

    newScript = script_new( argc, argv );

    int ret = tcc_main( newScript );
    //return MyWinMain( NULL, NULL, newScript->argv[0], SW_SHOW );

    if (!reload)
        UnWatchDirectory();

    script_destroy( &newScript );

    return ret;
}

int MessageBoxS( const char* fmt, ... )
{
    char tmp[1024];

	va_list args;
	va_start( args, fmt );
	vsprintf( tmp, fmt, args );
	va_end( args );

    MessageBoxA( 0, tmp, "Application", MB_OK | MB_ICONERROR );
    return 0;
}

void* GetGXDInstanceForScript()
{
	return reinterpret_cast<GXD*>( &mGXD );
}

void* GetTW2InstanceForScript()
{
	return reinterpret_cast<TW2AddIn::GXD*>( &TW2AddIn::mGXD );
}

void* GetHostInstanceForScript()
{
    return reinterpret_cast<ts2_script_t*>( newScript );
}

void* SetHostHINSTANCE( void* hInstance )
{
    newScript->hInstance = hInstance;
    return hInstance;
}

void* SetHostHWND( void* hWnd )
{
    newScript->hWnd = hWnd;
    return hWnd;
}

