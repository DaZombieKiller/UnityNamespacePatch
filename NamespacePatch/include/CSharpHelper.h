#pragma once
#include <Windows.h>

extern "C" HRESULT GetClassNamespace(const char* text, int textLen, const char* className, void* state, void(*callback)(const char*, void*));
