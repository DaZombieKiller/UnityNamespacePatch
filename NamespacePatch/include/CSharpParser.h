#pragma once
#include "basic_string.h"
#include "dynamic_array.h"

namespace CSharpParser
{
    core::string GetClassAndNamespace(const core::string& text, core::string& className, core::string& namespaceName, int& errorLine, const dynamic_array<core::string>* defines);
};
