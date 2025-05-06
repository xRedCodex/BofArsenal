#pragma once

#include <Common.hpp>
#include <lmaccess.h>
#include <lmerr.h>

EXTERN_C {
    DFR( NETAPI32, NetUserAdd )
}

#define NetUserAdd NETAPI32$NetUserAdd
