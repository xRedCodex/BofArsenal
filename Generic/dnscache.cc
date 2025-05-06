#include <Common.hpp>

/// @struct Represents an entry in the DNS cache.
struct DNS_CACHE_ENTRY {
    /// Pointer to the next entry in the DNS cache.
    struct DNS_CACHE_ENTRY* Next;

    /// Wide string containing the DNS name.
    PWSTR Name;

    /// Type of the DNS entry.
    USHORT Type;

    /// Length of the associated data.
    USHORT DataLength;

    /// Flags for additional information.
    ULONG Flags;
};

/**
 * @brief Entry point of the program.
 *
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto DnsCache(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    //
    // Call DnsGetCacheDataTable to retrieve the DNS cache table.
    // The result is stored in the Entry pointer.
    //
    DNS_CACHE_ENTRY* Entry = NULL;
    DnsGetCacheDataTable( &Entry );
    if ( IS_NULL( Entry ) || IS_NULL( Entry->Next ) ) {
        BeaconPrintf( CALLBACK_ERROR, "[-] DNS cache entry is null or invalid" );
        return;
    }

    //
    // Iterate through all the entries in the DNS cache table.
    //
    Entry = Entry->Next;
    while ( Entry ) {
        switch ( Entry->Type ) {
            case 1:   print( "A: "     ); break;
            case 2:   print( "NS: "    ); break;
            case 5:   print( "CNAME: " ); break;
            case 6:   print( "SOA: "   ); break;
            case 12:  print( "PTR: "   ); break;
            case 15:  print( "MX: "    ); break;
            case 16:  print( "TXT: "   ); break;
            case 28:  print( "AAAA: "  ); break;
            case 33:  print( "SRV: "   ); break;
            case 255: print( "*: "     ); break;
            default:  print( "%d:", Entry->Type );
        }

        print( "%s\n", WideToUtf8(Entry->Name) );

        //
        // Move to the next entry in the DNS cache table.
        //
        Entry = Entry->Next;
    }
    
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
    _In_ INT Argc
) -> void {
    Start();
    return DnsCache( Args, Argc );
}