#pragma once

#include <Windows.h>
#include <Macros.hpp>
#include <iphlpapi.h>
#include <stdio.h>
#include <lmaccess.h>
#include <lmerr.h>
#include <Native.hpp>

EXTERN_C DECLSPEC_IMPORT INT WINAPI DNSAPI$DnsGetCacheDataTable(PVOID Data);
EXTERN_C {
    DFR(KERNEL32, VirtualAlloc)
    DFR(KERNEL32, LoadLibraryW)
    DFR(KERNEL32, VirtualProtect)
    DFR(KERNEL32, GetEnvironmentStringsW)
    DFR(KERNEL32, FreeEnvironmentStringsW)
    DFR(KERNEL32, GetLastError)
    DFR(KERNEL32, GetProcessHeap)
    DFR(KERNEL32, HeapAlloc)
    DFR(KERNEL32, HeapFree)
    DFR(KERNEL32, WideCharToMultiByte)
    DFR(KERNEL32, OpenProcess)
    DFR(KERNEL32, CreateFileA)
    DFR(KERNEL32, HeapReAlloc)
    DFR(KERNEL32, QueryFullProcessImageNameA)
    DFR(KERNEL32, CloseHandle)
    
    DFR(IPHLPAPI, GetNetworkParams)
    DFR(IPHLPAPI, GetAdaptersInfo)
    DFR(IPHLPAPI, GetIpForwardTable)
    DFR(IPHLPAPI, GetNetworkParams)
    DFR(IPHLPAPI, GetAdaptersInfo)
    DFR(IPHLPAPI, GetIpForwardTable)
    
    DFR(MSVCRT, printf)
    DFR(MSVCRT, wprintf)
    DFR(MSVCRT, wcslen)
    DFR(MSVCRT, vsnprintf)
    DFR(MSVCRT, wcscmp)

    DFR(NETAPI32, NetUserAdd)

    DFR(NTDLL, NtOpenSection)
    DFR(NTDLL, NtCreateSection)
    DFR(NTDLL, NtMapViewOfSection)
    DFR(NTDLL, NtUnmapViewOfSection)
    DFR(NTDLL, NtQueryInformationFile)
}

#define GetNetworkParams           IPHLPAPI$GetNetworkParams
#define GetAdaptersInfo            IPHLPAPI$GetAdaptersInfo
#define GetIpForwardTable          IPHLPAPI$GetIpForwardTable
#define DnsGetCacheDataTable       DNSAPI$DnsGetCacheDataTable

#define VirtualProtect             KERNEL32$VirtualProtect
#define LoadLibraryW               KERNEL32$LoadLibraryW
#define VirtualAlloc               KERNEL32$VirtualAlloc
#define GetEnvironmentStringsW     KERNEL32$GetEnvironmentStringsW
#define FreeEnvironmentStringsW    KERNEL32$FreeEnvironmentStringsW         
#define GetLastError               KERNEL32$GetLastError
#define GetProcessHeap             KERNEL32$GetProcessHeap
#define HeapAlloc                  KERNEL32$HeapAlloc 
#define HeapFree                   KERNEL32$HeapFree
#define WideCharToMultiByte        KERNEL32$WideCharToMultiByte
#define OpenProcess                KERNEL32$OpenProcess
#define CreateFileA                KERNEL32$CreateFileA
#define HeapReAlloc                KERNEL32$HeapReAlloc
#define QueryFullProcessImageNameA KERNEL32$QueryFullProcessImageNameA
#define CloseHandle                KERNEL32$CloseHandle

#define wcscmp                     MSVCRT$wcscmp
#define printf                     MSVCRT$printf
#define wprintf                    MSVCRT$wprintf
#define wcslen                     MSVCRT$wcslen
#define vsnprintf                  MSVCRT$vsnprintf
#define NetUserAdd                 NETAPI32$NetUserAdd

#define NtOpenSection              NTDLL$NtOpenSection
#define NtCreateSection            NTDLL$NtCreateSection
#define NtMapViewOfSection         NTDLL$NtMapViewOfSection
#define NtUnmapViewOfSection       NTDLL$NtUnmapViewOfSection
#define NtQueryInformationFile     NTDLL$NtQueryInformationFile