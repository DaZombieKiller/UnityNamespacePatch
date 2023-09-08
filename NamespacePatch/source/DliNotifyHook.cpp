#include <Windows.h>
#include <DbgHelp.h>
#include <delayimp.h>
#include "SymbolHandler.h"

FARPROC WINAPI DliNotifyHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
    switch (dliNotify)
    {
    case dliNoteStartProcessing:
        InitSymbolHandler();
        break;
    case dliNotePreGetProcAddress:
        if (pdli->dlp.fImportByName)
        {
            SYMBOL_INFO Symbol{};
            Symbol.SizeOfStruct = sizeof(Symbol);

            if (SymFromName(GetCurrentProcess(), pdli->dlp.szProcName, &Symbol))
            {
                return (FARPROC)Symbol.Address;
            }
        }
        break;
    case dliNoteEndProcessing:
        ReleaseSymbolHandler();
        break;
    }

    return nullptr;
}

ExternC const PfnDliHook __pfnDliNotifyHook2 = DliNotifyHook;
