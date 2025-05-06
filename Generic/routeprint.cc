#include <Common.hpp>

/**
 * @brief Print active IPv4 routes in a structured format.
 */
auto PrintActiveRoutes(
    _In_ PMIB_IPFORWARDTABLE IpForward
) -> void {
    print("IPv4 Route Table\n");
    print("===========================================================================\n");
    print("Active Routes:\n");
    print("%-20s %-15s %-20s %-15s %-6s\n", "Network Address", "Mask", "Gateway", "Interface", "Metric");

    for (DWORD i = 0; i < IpForward->dwNumEntries; ++i) {
        MIB_IPFORWARDROW Row = IpForward->table[i];
        struct in_addr Dest, Mask, Gateway;

        Dest.S_un.S_addr    = Row.dwForwardDest;
        Mask.S_un.S_addr    = Row.dwForwardMask;
        Gateway.S_un.S_addr = Row.dwForwardNextHop;

        print("%-20s %-15s %-20s %-15lu %-6lu\n",
            inet_ntoa(Dest), inet_ntoa(Mask), inet_ntoa(Gateway), Row.dwForwardIfIndex, Row.dwForwardMetric1);
    }

    print("===========================================================================\n");
}

/**
 * @brief Print network interfaces in a structured format.
 */
auto PrintInterfaceList(
    _In_ PIP_ADAPTER_INFO AdapterInfo
) -> void {
    print( "Interface List\n");
    print( "===========================================================================\n");

    PIP_ADAPTER_INFO P = AdapterInfo;
    while (P) {
        print( "0x%lu ........................... %s\n", P->Index, P->Description );
        P = P->Next;
    }

    print("===========================================================================\n");
}

/**
 * @brief Entry point of the program.
 * 
 * @param Args Pointer to the arguments passed to the program (as a string).
 * @param Argc Count of arguments passed to the program.
 */
auto RoutePrint(
    _In_ PCHAR Args,
    _In_ INT   Argc
) -> void {
    ULONG AdapterSize = 0;
    ULONG ForwardSize = 0;

    PIP_ADAPTER_INFO    AdapterInfo = NULL;
    PMIB_IPFORWARDTABLE IpForward   = NULL;

    //
    // Get adapter info buffer size
    //
    if ( GetAdaptersInfo( NULL, &AdapterSize ) == ERROR_BUFFER_OVERFLOW ) {
        AdapterInfo = Mem::Alloc<IP_ADAPTER_INFO>( AdapterSize );
        if ( ! AdapterInfo ) return;
    }

    //
    // Get IP forward table buffer size
    //
    if ( GetIpForwardTable( NULL, &ForwardSize, TRUE ) == ERROR_INSUFFICIENT_BUFFER ) {
        IpForward = Mem::Alloc<MIB_IPFORWARDTABLE>( ForwardSize );
        if ( ! IpForward ) return;
    }

    //
    // Retrieve adapter and route table information
    //
    if ( GetAdaptersInfo( AdapterInfo, &AdapterSize ) == NO_ERROR 
        && GetIpForwardTable( IpForward, &ForwardSize, TRUE ) == NO_ERROR
    ) {
        print( "Default Gateway: %s\n", AdapterInfo->GatewayList.IpAddress.String );
        PrintInterfaceList(AdapterInfo);
        PrintActiveRoutes(IpForward);
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
auto go(PCHAR Args, INT Argc) -> void {
    Start();
    return RoutePrint( Args, Argc );
}