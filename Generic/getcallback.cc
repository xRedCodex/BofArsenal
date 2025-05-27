#include <Externs.hpp>
#include <Common.hpp>

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    ULONG Version;  // The version of the instrumentation callback information.
    ULONG Reserved; // Reserved for future use.
    PVOID Callback; // Pointer to the callback function.
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, *PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

auto GetCallback( VOID ) -> VOID {
    
    LONG   Status         = STATUS_SUCCESS;
    ULONG  LengthRet      = 0; 
    HANDLE ProcessHandle  = NtCurrentProcess();

    PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION InstCallbackInfo = { 0 };

    //
    // query the instrumentation callback information
    //
    Status = NtQueryInformationProcess(
        ProcessHandle, (PROCESSINFOCLASS)ProcessInstrumentationCallback,
        (PVOID)&InstCallbackInfo, sizeof( InstCallbackInfo ), &LengthRet
    );

    //
    // check if found callback
    // 
    if ( InstCallbackInfo.Callback ) {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Process Instrumentation Callback found at address: %p", InstCallbackInfo.Callback); 
    } else {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Process Instrumentation Callback is not set"); 
    }
}

EXTERN_C
auto go(PCHAR Args, INT Argc) -> VOID {
    Start();

    GetCallback();
}