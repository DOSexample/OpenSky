#ifndef MyHeader_H
#define MyHeader_H


#include <Windows.h>
#include <Imm.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ARGUMENT_FOR_SCRIPT         100
#define MAX_CMD_LENGTH_FOR_SCRIPT       260
typedef struct ts2_script_t {
    int argc;
    char** argv;
    void* tcc_state;
    void* hInstance;
    void* hWnd;
    char* startupDir;
} ts2_script_t;


int tcc_main( ts2_script_t* script_instance );
void add_symbol_app( void* tcc_state );

ts2_script_t* script_new( int argc, char** argv );
void script_destroy( ts2_script_t** arg );
int script_add_library( ts2_script_t* s, const char* libraryname );
int scrip_add_library_path( ts2_script_t *s, const char *pathname );

int MessageBoxS( const char* fmt, ... );
void* GetGXDInstanceForScript();
void* GetTW2InstanceForScript();
void* GetHostInstanceForScript();
void* SetHostHINSTANCE( void* );
void* SetHostHWND( void* );
void HostReload();


#ifdef __cplusplus
}
#endif



#endif //MyHeader_H



