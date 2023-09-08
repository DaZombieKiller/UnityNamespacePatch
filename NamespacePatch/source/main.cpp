#include <Windows.h>
#include <DbgHelp.h>
#include <detours.h>
#include "CSharpHelper.h"
#include "CSharpParser.h"
#include "SymbolHandler.h"
#include <string>

BOOL AttachGetClassAndNamespaceDetour()
{
    static decltype(&CSharpParser::GetClassAndNamespace) Pointer;
    static decltype(Pointer) Detour = [](const core::string& text, core::string& className, core::string& namespaceName, int& errorLine, const dynamic_array<core::string> *defines)
    {
        errorLine = -1;

        GetClassNamespace(text.c_str(), text.length(), className.c_str(), &namespaceName, [](auto namespaceName, auto state)
        {
            *(core::string*)state = namespaceName;
        });

        // Return value is an error message string.
        return core::string{};
    };

    SYMBOL_INFO Symbol{};
    Symbol.SizeOfStruct = sizeof(Symbol);

    if (!SymFromName(GetCurrentProcess(), "?GetClassAndNamespace@CSharpParser@@YA?AV?$basic_string@DV?$StringStorageDefault@D@core@@@core@@AEBV23@AEAV23@1AEAHPEBU?$dynamic_array@V?$basic_string@DV?$StringStorageDefault@D@core@@@core@@$0A@@@@Z", &Symbol))
        return FALSE;

    *(ULONG64*)&Pointer = Symbol.Address;
    DetourAttach((void**)&Pointer, Detour);
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    InitSymbolHandler();
    DetourTransactionBegin();
    AttachGetClassAndNamespaceDetour();
    DetourTransactionCommit();
    ReleaseSymbolHandler();
	return TRUE;
}
