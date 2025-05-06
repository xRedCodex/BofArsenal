#include <Common.hpp>

/**
 * @brief Entry point of the program.
 * 
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto Env(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    //
    // Recovering the enviroment block
    //
    LPWCH EnvStr = GetEnvironmentStringsW();
    if ( IS_NULL( EnvStr ) ) {
        BeaconPrintf( CALLBACK_ERROR, "[-] GetEnvironmentStringsW Failed With Error: %d", GetLastError() );
        return;
    }

    //
    // Running a loop to read all envs
    //
    LPWCH CurrentEnv = EnvStr;
    while ( *CurrentEnv ) {
        Printf( "%s\n", WideToUtf8( CurrentEnv ) );
        CurrentEnv += wcslen( CurrentEnv ) + 1;
    }

    //
    // Free the enviroment block
    //
    FreeEnvironmentStringsW( EnvStr );

    PrintOutput( TRUE );
    return;
}

/**
 * @brief Wrapper function to call the main logic.
 * 
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
EXTERN_C
auto go(PCHAR Args, INT Argc) -> void {
    Start();
    return Env( Args, Argc );
}