#pragma once
#include <windows.h>

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

#define DATA_STORE_TYPE_EMPTY 0
#define DATA_STORE_TYPE_GENERAL_FILE 1

typedef struct {
	int type;
	DWORD64 hash;
	BOOL masked;
	char* buffer;
	size_t length;
} DATA_STORE_OBJECT, *PDATA_STORE_OBJECT;

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

    DECLSPEC_IMPORT BOOL  BeaconAddValue(PCCH Key, PVOID Ptr);
    DECLSPEC_IMPORT PVOID BeaconGetValue(PCCH Key);
    DECLSPEC_IMPORT BOOL  BeaconRemoveValue(PCCH Key);

    DECLSPEC_IMPORT PDATA_STORE_OBJECT BeaconDataStoreGetItem(SIZE_T Index);
    DECLSPEC_IMPORT VOID   BeaconDataStoreProtectItem(SIZE_T Index);
    DECLSPEC_IMPORT VOID   BeaconDataStoreUnprotectItem(SIZE_T Index);
    DECLSPEC_IMPORT SIZE_T BeaconDataStoreMaxEntries();

    DECLSPEC_IMPORT PVOID  BeaconVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
    DECLSPEC_IMPORT PVOID  BeaconVirtualAllocEx(HANDLE processHandle, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
    DECLSPEC_IMPORT BOOL   BeaconVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
    DECLSPEC_IMPORT BOOL   BeaconVirtualProtectEx(HANDLE processHandle, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
    DECLSPEC_IMPORT BOOL   BeaconVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
    DECLSPEC_IMPORT BOOL   BeaconGetThreadContext(HANDLE threadHandle, PCONTEXT threadContext);
    DECLSPEC_IMPORT BOOL   BeaconSetThreadContext(HANDLE threadHandle, PCONTEXT threadContext);
    DECLSPEC_IMPORT DWORD  BeaconResumeThread(HANDLE threadHandle);
    DECLSPEC_IMPORT HANDLE BeaconOpenProcess(DWORD desiredAccess, BOOL inheritHandle, DWORD processId);
    DECLSPEC_IMPORT HANDLE BeaconOpenThread(DWORD desiredAccess, BOOL inheritHandle, DWORD threadId);
    DECLSPEC_IMPORT BOOL   BeaconCloseHandle(HANDLE object);
    DECLSPEC_IMPORT BOOL   BeaconUnmapViewOfFile(LPCVOID baseAddress);
    DECLSPEC_IMPORT SIZE_T BeaconVirtualQuery(LPCVOID address, PMEMORY_BASIC_INFORMATION buffer, SIZE_T length);
    DECLSPEC_IMPORT BOOL   BeaconDuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions);
    DECLSPEC_IMPORT BOOL   BeaconReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
    DECLSPEC_IMPORT BOOL   BeaconWriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
}

