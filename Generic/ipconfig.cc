#include <Common.hpp>

/**
 * @brief Entry point of the program.
 *
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto Ipconfig(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    //
    // Allocate memory for adapter information
    //
    ULONG OutputLen = sizeof( IP_ADAPTER_INFO ) * 32;
    IP_ADAPTER_INFO* AdapterInfo = Mem::Alloc<IP_ADAPTER_INFO>( OutputLen );
    if ( IS_NULL( AdapterInfo ) ) {
        BeaconPrintf( CALLBACK_ERROR, "[-] Failed to allocate memory for IP_ADAPTER_INFO." );
        return;
    }

    //
    // Retrieve adapter information
    //
    if ( GetAdaptersInfo( AdapterInfo, &OutputLen ) != ERROR_SUCCESS ) {
        BeaconPrintf( CALLBACK_ERROR, "[-] GetAdaptersInfo Failed With Error: %d", GetLastError() );
        return;
    }
    
    //
    // Allocate memory for network parameters
    //
    ULONG NetOutputLen = 0;
    FIXED_INFO* FixedInfo = NULL;
    if ( GetNetworkParams( FixedInfo, &NetOutputLen ) == ERROR_BUFFER_OVERFLOW ) {
        FixedInfo = Mem::Alloc<FIXED_INFO>( NetOutputLen );
        if ( IS_NULL( FixedInfo ) ) {
            Mem::Free( AdapterInfo );
            return;
        }

        if ( GetNetworkParams( FixedInfo, &NetOutputLen ) != NO_ERROR ) {
            Mem::Free( AdapterInfo );
            Mem::Free( FixedInfo );
            return;
        }
    } else {
        return;
    } 

    print( "Windows IP configuration\n" );

    //
    // Iterate through all adapters and print their details
    //
    PIP_ADAPTER_INFO P = AdapterInfo;
    while ( P ) {
        print( "\nAdapter Name: %s\n", P->AdapterName );
        
        switch ( AdapterInfo->Type ) {
            case MIB_IF_TYPE_ETHERNET: print( "Adapter Type: %s", "Ethernet\n" ); break;
            default:                   print( "Adapter Type: %s", "Unknown\n"  ); break;
        }

        print( "\tDescription: %s\n", P->Description );
        print( "\tPhysical Address: " );
        for ( INT I = 0 ; I < P->AddressLength ; I++ ) {
             print("%.2X%s", P->Address[I], (I == P->AddressLength - 1) ? "" : "-");
        }

        print( "\n\tIP Address: %s\n", P->IpAddressList.IpAddress.String );
        P = P->Next;
    }

    //
    // Print DNS details
    //
    print( "\nHost Name: \t%s\n", FixedInfo->HostName );
    print( "DNS Suffix: \t%s\n", FixedInfo->DomainName );
    print( "DNS Servers: " );

    //
    // Print primary DNS server
    //
    print( "\t%s\n", FixedInfo->DnsServerList.IpAddress.String );

    //
    //  Print additional DNS servers
    //
    PIP_ADDR_STRING IpAddr = FixedInfo->DnsServerList.Next;
    while ( IpAddr ) {
        print( "\t\t%s\n", IpAddr->IpAddress.String );
        IpAddr = IpAddr->Next;
    }

    //
    // Clean up allocated memory
    //
    if ( AdapterInfo ) Mem::Free( AdapterInfo );
    if ( FixedInfo )   Mem::Free( FixedInfo );

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
    return Ipconfig( Args, Argc );
}