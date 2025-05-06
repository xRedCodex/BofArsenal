#pragma once

#include <Common.hpp>
#include <Native.hpp>

EXTERN_C {
    DFR( NTDLL, NtOpenSection )
    DFR( NTDLL, NtCreateSection )
    DFR( NTDLL, NtMapViewOfSection )
    DFR( NTDLL, NtUnmapViewOfSection )
    DFR( NTDLL, NtQueryInformationFile)
}

#define NtOpenSection           NTDLL$NtOpenSection
#define NtCreateSection         NTDLL$NtCreateSection
#define NtMapViewOfSection      NTDLL$NtMapViewOfSection
#define NtUnmapViewOfSection    NTDLL$NtUnmapViewOfSection
#define NtQueryInformationFile  NTDLL$NtQueryInformationFile
