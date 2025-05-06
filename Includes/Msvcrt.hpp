#pragma once

#include <Common.hpp>
#include <stdio.h>

EXTERN_C {
    DFR( MSVCRT, printf );
    DFR( MSVCRT, wprintf );
    DFR( MSVCRT, wcslen );
    DFR( MSVCRT, vsnprintf );
    DFR( MSVCRT, wcscmp );
}

#define wcscmp    MSVCRT$wcscmp
#define printf    MSVCRT$printf
#define wprintf   MSVCRT$wprintf
#define wcslen    MSVCRT$wcslen
#define vsnprintf MSVCRT$vsnprintf
