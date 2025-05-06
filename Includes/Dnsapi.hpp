#pragma once

#include <Common.hpp>

EXTERN_C DECLSPEC_IMPORT INT WINAPI DNSAPI$DnsGetCacheDataTable(PVOID Data);

#define DnsGetCacheDataTable DNSAPI$DnsGetCacheDataTable
