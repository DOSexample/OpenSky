#include "Header.h"

#include <windows.h>
#include <Winbase.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_DIRS 25
#define MAX_FILES 255
#define MAX_BUFFER 4096

extern "C" {
    WINBASEAPI BOOL WINAPI
        ReadDirectoryChangesW(HANDLE hDirectory,
            LPVOID lpBuffer, DWORD nBufferLength,
            BOOL bWatchSubtree, DWORD dwNotifyFilter,
            LPDWORD lpBytesReturned,
            LPOVERLAPPED lpOverlapped,
            LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
        );
}

// all purpose structure to contain directory information and provide
// the input buffer that is filled with file change data

typedef struct _DIRECTORY_INFO {
    HANDLE hDir;
    WCHAR lpszDirName[MAX_PATH];
    CHAR lpBuffer[MAX_BUFFER];
    DWORD dwBufLength;
    OVERLAPPED Overlapped;
}DIRECTORY_INFO, * PDIRECTORY_INFO, * LPDIRECTORY_INFO;


//Method to start watching a directory. Call it on a separate thread so it wont block the main thread.  

typedef struct read_param_t {
    OVERLAPPED PollingOverlap;
    DIRECTORY_INFO DirInfo[MAX_DIRS];   // Buffer for all of the directories
    WCHAR FileList[MAX_FILES * MAX_PATH]; // Buffer for all of the files
    DWORD numDirs;
    HANDLE thHandle;
    DWORD thID;
} read_param_t;

DWORD WatchDirectoryThread( void* arg )
{
    read_param_t* prm = (read_param_t*)arg;
    wprintf( L"WatchDirectoryThread() :: %s\n", prm->DirInfo[0].lpszDirName );

    BOOL modified_file = FALSE;
    BOOL result = TRUE;
    FILE_NOTIFY_INFORMATION* pNotify;
    int offset;
    char buf[2048];
    DWORD nRet;
    char filename[MAX_PATH];
    prm->PollingOverlap.OffsetHigh = 0;
    prm->PollingOverlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    while ( result )
    {
        result = ReadDirectoryChangesW(
            prm->DirInfo[0].hDir,// handle to the directory to be watched
            &buf,// pointer to the buffer to receive the read results
            sizeof(buf),// length of lpBuffer
            TRUE,// flag for monitoring directory or directory tree
            FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_SIZE,
            //FILE_NOTIFY_CHANGE_LAST_WRITE |
            //FILE_NOTIFY_CHANGE_LAST_ACCESS |
            //FILE_NOTIFY_CHANGE_CREATION,
            &nRet,// number of bytes returned
            &prm->PollingOverlap,// pointer to structure needed for overlapped I/O
            NULL);

        WaitForSingleObject( prm->PollingOverlap.hEvent, INFINITE );
        offset = 0;
        //int rename = 0;
        //char oldName[260];
        //char newName[260];
        do
        {
            pNotify = (FILE_NOTIFY_INFORMATION*)((char*)buf + offset);
            strcpy(filename, "");
            int filenamelen = WideCharToMultiByte(CP_ACP, 0, pNotify->FileName, pNotify->FileNameLength / 2, filename, sizeof(filename), NULL, NULL);
            filename[filenamelen] = '\0';
            switch (pNotify->Action)
            {
            case FILE_ACTION_ADDED:
                //printf("The file is added to the directory: [%s] \n", filename);
                break;
            case FILE_ACTION_REMOVED:
                //printf("The file is removed from the directory: [%s] \n", filename);
                break;
            case FILE_ACTION_MODIFIED:
                //printf("The file is modified. This can be a change in the time stamp or attributes: [%s]\n", filename);
                break;
            case FILE_ACTION_RENAMED_OLD_NAME:
                //printf("The file was renamed and this is the old name: [%s]\n", filename);
                break;
            case FILE_ACTION_RENAMED_NEW_NAME:
                //don't care .TMP file
                if ( strstr( filename, ".TMP" ) )
                    break;
                printf( "The file was renamed and this is the new name: [%s]\n", filename );
                modified_file = TRUE;
                break;
            default:
                printf("Default error.\n");
                break;
            }

            offset += pNotify->NextEntryOffset;

            if( modified_file )
                break;
        } while (pNotify->NextEntryOffset); //(offset != 0);

        if ( modified_file )
            break;
    }

    CloseHandle( prm->DirInfo[0].hDir );
    printf( "stoped thread...\n" );

    if (modified_file)
    {
        HostReload();
    }

    return 0;
}

read_param_t readPrm;
void WatchDirectory( LPCWSTR path )
{
    readPrm.DirInfo[0].hDir = CreateFileW(path, GENERIC_READ | FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        NULL);

    if (readPrm.DirInfo[0].hDir == INVALID_HANDLE_VALUE)
    {
        fprintf( stderr, "WatchDirectory:: cannot open folder\n" );
        return;
    }

    lstrcpyW( readPrm.DirInfo[0].lpszDirName, path );

    printf( "creating thread...\n" );
    readPrm.thHandle = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)WatchDirectoryThread, &readPrm, 0, &readPrm.thID );
    printf( "%p...%d\n", readPrm.thHandle, readPrm.thID );
    if ( !readPrm.thHandle )
    {
        printf( "create thread error...\n" );
    }
}

void UnWatchDirectory()
{
    printf( "stoping thread...\n" );
    {
        //TerminateThread( readPrm.thHandle, 0 );
        //CloseHandle( readPrm.thHandle );
    }
}