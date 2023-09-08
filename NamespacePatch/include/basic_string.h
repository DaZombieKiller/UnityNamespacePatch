#pragma once
#include "MemLabelId.h"
#include "StringStorageDefault.h"

namespace core
{
    template<class T, class TStorage = StringStorageDefault<T>>
    class basic_string : TStorage
    {
    public:
        basic_string() = default;
        const T* c_str() const;
        size_t length() const;
        basic_string& operator=(const T* copyStr);
        static basic_string create_from_external(const T* referenceStr, const MemLabelId& label);
        static basic_string create_from_external(const T* referenceStr, size_t referenceStrLen, const MemLabelId& label);
    };

    using string = basic_string<char>;
};
