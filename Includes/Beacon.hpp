#pragma once
#include <Windows.h>

#define CALLBACK_OUTPUT      0x0
#define CALLBACK_OUTPUT_OEM  0x1e
#define CALLBACK_ERROR       0x0d
#define CALLBACK_OUTPUT_UTF8 0x20

/// @struct Represents a managed data buffer with additional metadata.
struct Data {
    /// Pointer to the original buffer.
    PCHAR Original;

    /// Pointer to the current position in the buffer.
    PCHAR Buffer;

    /// Remaining length of the buffer.
    INT Length;

    /// Total size of the buffer.
    INT Size;
};

/// @struct Represents a managed data buffer with metadata for tracking its state.
struct Format {
    /// Pointer to the original buffer.
    PCHAR Original;

    /// Pointer to the current position in the buffer.
    PCHAR Buffer;

    /// Remaining length in the buffer.
    INT Length;

    /// Total size of the buffer.
    INT Size;
};

EXTERN_C {
    DECLSPEC_IMPORT VOID  BeaconPrintf         (INT Type, const char* Fmt, ...);
    DECLSPEC_IMPORT VOID  BeaconOutput         (INT Type, PCHAR Data, INT Len);
    DECLSPEC_IMPORT BOOL  BeaconUseToken       (HANDLE Token);
    DECLSPEC_IMPORT VOID  BeaconRevertToken    ();
    DECLSPEC_IMPORT BOOL  BeaconIsAdmin        ();

    DECLSPEC_IMPORT VOID  BeaconDataParse      (Data* Parser, PCHAR Buffer, INT Size);
    DECLSPEC_IMPORT INT   BeaconDataInt        (Data* Parser);
    DECLSPEC_IMPORT SHORT BeaconDataShort      (Data* Parser);
    DECLSPEC_IMPORT INT   BeaconDataLength     (Data* Parser);
    DECLSPEC_IMPORT PCHAR BeaconDataExtract    (Data* Parser, PINT Size);

    DECLSPEC_IMPORT VOID  BeaconFormatAlloc    (Format* Format, INT Maxsz);
    DECLSPEC_IMPORT VOID  BeaconFormatReset    (Format* Format);
    DECLSPEC_IMPORT VOID  BeaconFormatFree     (Format* Format);
    DECLSPEC_IMPORT VOID  BeaconFormatAppend   (Format* Format, PCHAR Text, INT Len);
    DECLSPEC_IMPORT VOID  BeaconFormatPrintf   (Format* Format, PCHAR Fmt, ...);
    DECLSPEC_IMPORT PCHAR BeaconFormatToString (Format* Format, PINT Size);
    DECLSPEC_IMPORT VOID  BeaconFormatInt      (Format* Format, INT Value);
}

