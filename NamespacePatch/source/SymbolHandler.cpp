#include <Windows.h>
#include <DbgHelp.h>
#include <PathCch.h>
#include "SymbolHandler.h"

static ULONG g_SymbolHandlerRef = 0;

void InitSymbolHandler()
{
    if (InterlockedIncrement(&g_SymbolHandlerRef) == 1)
    {
        WCHAR UserSearchPath[MAX_PATH];
        GetModuleFileNameW(GetModuleHandle(NULL), UserSearchPath, MAX_PATH);
        PathCchRemoveFileSpec(UserSearchPath, MAX_PATH);
        SymSetOptions(SYMOPT_IGNORE_CVREC);
        SymInitializeW(GetCurrentProcess(), UserSearchPath, TRUE);
    }
}

void ReleaseSymbolHandler()
{
    if (InterlockedDecrement(&g_SymbolHandlerRef) == 0)
    {
        SymCleanup(GetCurrentProcess());
    }
}
