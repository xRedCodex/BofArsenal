#pragma once

#include <Macros.hpp>
#include <iphlpapi.h>

EXTERN_C {
    DFR( IPHLPAPI, GetNetworkParams )
    DFR( IPHLPAPI, GetAdaptersInfo )
    DFR( IPHLPAPI, GetIpForwardTable)
}

#define GetNetworkParams  IPHLPAPI$GetNetworkParams
#define GetAdaptersInfo   IPHLPAPI$GetAdaptersInfo
#define GetIpForwardTable IPHLPAPI$GetIpForwardTable
