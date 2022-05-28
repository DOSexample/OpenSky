#include "Header.h"
#include "tcc-0.9.27/tcc.h"

ts2_script_t* script_new( int argc, char** argv )
{
    int i;
    ts2_script_t* newScript = (ts2_script_t*)GlobalAlloc( 0, sizeof(ts2_script_t) );
    newScript->argc = argc;
    newScript->argv = (char**)GlobalAlloc( 0, sizeof(char**) * MAX_ARGUMENT_FOR_SCRIPT );
    newScript->startupDir = (char*)GlobalAlloc( 0, MAX_CMD_LENGTH_FOR_SCRIPT );
    GetCurrentDirectoryA(MAX_CMD_LENGTH_FOR_SCRIPT, newScript->startupDir);

    for ( i = 0; i < MAX_ARGUMENT_FOR_SCRIPT; i++ )
    {
        newScript->argv[i] = (char*)GlobalAlloc( 0, MAX_CMD_LENGTH_FOR_SCRIPT );
        newScript->argv[i][0] = '\0';
    }
    for ( i = 0; i < argc; i++ )
    //for ( i = 0; i < 1 && argc >= 1; i++ )
    {
        int len = strlen(argv[i]);
        memcpy( newScript->argv[i], argv[i], len );
        newScript->argv[i][len] = '\0';
    }
    newScript->tcc_state = tcc_new();
    return newScript;
}

void script_destroy( ts2_script_t** arg )
{
    int i;
    ts2_script_t* newScript = *arg;
    GlobalFree( newScript->argv );
    GlobalFree( newScript->startupDir );
    for ( i = 0; i < MAX_ARGUMENT_FOR_SCRIPT; i++ )
    {
        GlobalFree( newScript->argv[i] );
    }
    GlobalFree( newScript->argv );
}

int script_add_library( ts2_script_t* s, const char* libraryname )
{
    return tcc_add_library( (TCCState*)s->tcc_state, libraryname );
}

int scrip_add_library_path( ts2_script_t *s, const char *pathname )
{
    return tcc_add_library_path( (TCCState*)s->tcc_state, pathname );
}
