#include <Externs.hpp>
#include <Common.hpp>
#include <Strings.cc>

#define BUFF_RETURN_LENGTH 0x10000

auto WsMan(
    _In_ PCHAR Host,
    _In_ PCHAR Port,
    _In_ PCHAR Protocol,
    _In_ PCHAR Command,
    _In_ PCHAR User,
    _In_ PCHAR Pass
) -> VOID {
    // set to use default value if not retrieved
    if ( !Protocol ) Protocol = "http";
    if ( !Port     ) Port     = "5985";

    HRESULT Result = S_OK;

    // declare the COM objects
    IDispatch*      Service   = { 0 };
    IDispatch*      Options   = { 0 };
    IWSManSession*  WsManSess = { 0 };
    IWSMan*         WsManObj  = { 0 };

    // buffers in the stack
    CHAR  TmpConn[MAX_PATH];
    WCHAR Connection[MAX_PATH*2];
    WCHAR wCommand[MAX_PATH*2];
    WCHAR Parameters[MAX_PATH*2];

    // allocating memory to winrm command response
    PWCHAR RawResponse  = Mem::Alloc( BUFF_RETURN_LENGTH * 2 );
    PCHAR  CharResponse = Mem::Alloc( BUFF_RETURN_LENGTH * 1 );

    // resource variant
    VARIANT Resource      = (VARIANT)L"http://schemas.microsoft.com/wbem/wsman/1/wmi/root/cimv2/Win32_Process";

    // parameters to concat with the command
    BSTR    TmpParamBegin = L"<p:Create_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wmi/root/cimv2/Win32_Process\"><p:CommandLine>";
    BSTR    TmpParamEnd   = L"</p:CommandLine></p:Create_INPUT>";

    // concat the connection data
    Str::ConcatA( TmpConn, Protocol );
    Str::ConcatA( TmpConn, "://" );
    Str::ConcatA( TmpConn, Host );
    Str::ConcatA( TmpConn, ":" );
    Str::ConcatA( TmpConn, Port );
    Str::ConcatA( TmpConn, "/wsman" );

    // convert char command to wchar
    Str::CharToWChar( wCommand, Command, MAX_PATH * 2 );

    // concat the schema with command
    Str::ConcatW( Parameters, TmpParamBegin );
    Str::ConcatW( Parameters, wCommand );
    Str::ConcatW( Parameters, TmpParamEnd );

    // converte char connection to wchar
    Str::CharToWChar( Connection, TmpConn, ( MAX_PATH * 2 ) );

    // initialize COM
    Result = CoInitializeEx( 0, COINIT_MULTITHREADED );
    if ( FAILED( Result ) ) return;

    // create the instance of the (WSMAN WinRM) COM object
    Result = CoCreateInstance( CLSID_WSMan, 0, CLSCTX_INPROC_SERVER, IID_IWSMan, (PVOID*)&WsManObj );
    if ( FAILED( Result ) ) return;

    // create the WinRM session
    Result = WsManObj->CreateSession( Connection, 0, NULL, &Service );
    if ( FAILED( Result ) ) return;

    // reinterpret object to IWSManSession
    WsManSess = reinterpret_cast<IWSManSession*>( Service );

    // invoke the command and receiving the response
    WsManSess->Invoke( (BSTR)L"Create", (VARIANT)Resource, Parameters, 0, &RawResponse );

    // convert wchar response to char
    Str::WCharToChar( CharResponse, RawResponse, MAX_PATH );

    Printf( CharResponse );

_WS_END:
    if ( Service      ) Service->Release();
    if ( WsManSess    ) WsManSess->Release();
    if ( WsManObj     ) WsManObj->Release();
    if ( RawResponse  ) Mem::Free( RawResponse );
    if ( CharResponse ) Mem::Free( CharResponse );
    CoUninitialize();
}

auto go(PCHAR Args, INT Argc) -> void {
    Start();

    Data* Parser = { 0 };

    BeaconDataParse( Parser, Args, Argc );

    PCHAR Host     = BeaconDataExtract( Parser, 0 );
    PCHAR Port     = BeaconDataExtract( Parser, 0 );
    PCHAR Protocol = BeaconDataExtract( Parser, 0 );
    PCHAR Command  = BeaconDataExtract( Parser, 0 );
    PCHAR User     = BeaconDataExtract( Parser, 0 );
    PCHAR Pass     = BeaconDataExtract( Parser, 0 );

    return WsMan( Host, Port, Protocol, Command, User, Pass );
}