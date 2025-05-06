#include <Common.hpp>

/**
 * @brief Entry point of the program.
 *
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto EnumHandles(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    //
    // Define the file name to be analyzed
    //
    Data Parser = { 0 };
    BeaconDataParse( &Parser, Args, Argc );
    PCHAR FileName = BeaconDataExtract( &Parser, NULL );
    Printf( "Enumerating handles for the %s\n", FileName );

    //
    // Open the specified file with sharing permissions for read, write, and delete
    //
    HANDLE HFile = CreateFileA(
        FileName, 
        0, 
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, 
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    //
    // Check if the file handle was successfully opened
    //
    if ( HFile == INVALID_HANDLE_VALUE ) {
        ULONG Error = GetLastError();
        if ( Error == ERROR_FILE_NOT_FOUND || Error == ERROR_PATH_NOT_FOUND ) 
            BeaconPrintf( CALLBACK_ERROR, "[-] File Not Found: %s", FileName );
        else
            BeaconPrintf( CALLBACK_ERROR, "[-] CreateFile Failed With Error %d", Error );
        return;
    }

    //
    // Initialize buffer size and allocate memory
    // 
    NTSTATUS        Status   = STATUS_UNSUCCESSFUL;
    SIZE_T          Size     = 1 << 12;
    PVOID           Buffer   = Mem::Alloc<PVOID>( Size );
    IO_STATUS_BLOCK IoStatus = { 0 };
    
    //
    // Perform repeated calls to NtQueryInformationFile to ensure the buffer is large enough
    //
    do {
        Size   *= 2;
        Buffer = Mem::ReAlloc( Buffer, Size );
        Status = NtQueryInformationFile( HFile, &IoStatus, Buffer, Size, FileProcessIdsUsingFileInformation );
    } while ( Status == STATUS_INFO_LENGTH_MISMATCH );

    //
    // Close the file handle after retrieving the necessary information
    //
    CloseHandle( HFile );

    //
    // Verify if NtQueryInformationFile call was successful
    //
    if ( ! NT_SUCCESS( Status ) ) {
        BeaconPrintf( CALLBACK_ERROR, "[-] NtQueryInformationFile Failed With NTSTATUS: 0x%08X", Status );
        Mem::Free( Buffer );
        return;
    }

    //
    // Retrieve the number of processes and the array of PIDs from the buffer
    //
    LONG64  Pids     = *( PLONG64 )(Buffer);
    PLONG64 PidArray = ( PLONG64 )Buffer + 1;
    INT     Index    = 1;

    //
    // Iterate over PIDs and try to open associated processes to retrieve their names
    //
    for ( INT I = 0; I < Pids; I++ ) {
        LONG64 Pid      = PidArray[ I ];
        HANDLE HProcess = OpenProcess( PROCESS_QUERY_LIMITED_INFORMATION, FALSE, ( ULONG )Pid );
        
        //
        // Check if the process handle was successfully opened
        //
        if ( ! IS_NULL( HProcess ) ) {
            CHAR  ImageName[ MAX_PATH ] = { 0 };
            ULONG ImageLen = MAX_PATH;

            if ( QueryFullProcessImageNameA( HProcess, 0, ImageName, &ImageLen ) )  {
                Printf( "%d. PID %d - %s\n", Index, Pid, ImageName );
            } else {
                Printf( "%d. Failed to resolve filename with PID %d\n", Index, Pid );
            }

            CloseHandle( HProcess );
        } else {
            Printf( "%d. Failed to open process for PID: %d\n", Index, Pid );
        }

        Index += 1;
    }

    //
    //  Clean up allocated memory
    //
    if ( Buffer ) Mem::Free( Buffer );

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
    return EnumHandles( Args, Argc );
}