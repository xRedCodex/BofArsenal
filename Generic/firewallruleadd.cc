#include <Externs.hpp>
#include <Common.hpp>
#include <Strings.cc>

auto AddRule(
    _In_ CHAR* DirectOpt,
    _In_ BSTR  RuleName,
    _In_ BSTR  RuleDesc,
    _In_ BSTR  RuleGroup,
    _In_ BSTR  LocalPort
) -> VOID {
    LONG Protocol  = NET_FW_IP_PROTOCOL_TCP;
    LONG Direction = 0;
    LONG Result    = S_OK;

    INetFwPolicy2* Policy = nullptr;
    INetFwRules*   Rules  = nullptr;
    INetFwRule*    Rule   = nullptr;

    GUID CLSID_NET_FW_POLICY = {0xe2b3c97f, 0x6ae1, 0x41ac, {0x81, 0x7a, 0xf6, 0xf9, 0x21, 0x66, 0xd7, 0xdd}};
    IID  RIID_NET_FW_POLICY  = {0x98325047, 0xc671, 0x4174, {0x8d, 0x81, 0xde, 0xfc, 0xd3, 0xf0, 0x31, 0x86}};

    if ( Str::CompareA( DirectOpt, "in" ) == 0 ) {
        Direction = NET_FW_RULE_DIR_IN;
    } else if ( Str::CompareA( DirectOpt, "out" ) == 0 ) {
        Direction = NET_FW_RULE_DIR_OUT;
    }

    Result = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
    if ( FAILED( Result ) ) goto _BF_END;

    Result = CoCreateInstance( CLSID_NET_FW_POLICY, nullptr, CLSCTX_INPROC_SERVER, RIID_NET_FW_POLICY, (PVOID*)&Policy );
    if ( FAILED( Result ) ) goto _BF_END;

    

_BF_END:
    if ( RuleName  ) SysFreeString( RuleName  );
    if ( RuleDesc  ) SysFreeString( RuleDesc  );
    if ( RuleGroup ) SysFreeString( RuleGroup );
    if ( LocalPort ) SysFreeString( LocalPort );
}

EXTERN_C 
auto go( 
    _In_ PCHAR Args, 
    _In_ INT   Argc
) -> void {
    Start();

    Data* Parser = { 0 };

    BeaconDataParse( Parser, Args, Argc );

    CHAR* DirectOpt = BeaconDataExtract( Parser, 0 );
    CHAR* RuleName  = BeaconDataExtract( Parser, 0 );
    CHAR* RuleDesc  = BeaconDataExtract( Parser, 0 );
    CHAR* RuleGroup = BeaconDataExtract( Parser, 0 );
    CHAR* LocalPort = BeaconDataExtract( Parser, 0 );

    WCHAR wRuleName[MAX_PATH*2] = { 0 };
    WCHAR wRuleDesc[MAX_PATH*2] = { 0 };
    WCHAR wRuleGroup[MAX_PATH*2] = { 0 };
    WCHAR wLocalPort[MAX_PATH*2] = { 0 };

    Str::CharToWChar( wRuleName, RuleName, MAX_PATH*2 );
    Str::CharToWChar( wRuleDesc, RuleDesc, MAX_PATH*2 );
    Str::CharToWChar( wRuleGroup, RuleGroup, MAX_PATH*2 );
    Str::CharToWChar( wLocalPort, LocalPort, MAX_PATH*2 );
    
    BSTR sRuleName  = SysAllocString( wRuleName );
    BSTR sRuleDesc  = SysAllocString( wRuleDesc );
    BSTR sRuleGroup = SysAllocString( wRuleGroup );
    BSTR sLocalPort = SysAllocString( wLocalPort );

    AddRule( DirectOpt, sRuleName, sRuleDesc, sRuleGroup, sLocalPort );
}