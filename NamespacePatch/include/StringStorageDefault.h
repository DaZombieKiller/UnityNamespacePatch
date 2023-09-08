#pragma once
#include "MemLabelId.h"

namespace core
{
    template<class T>
    class StringStorageDefault
    {
        enum
        {
            kInternalBufferCapacity = 0xF,
        };
    protected:
        T* m_data;

        union
        {
            size_t m_capacity;
            T m_internal[(kInternalBufferCapacity + 1) / sizeof(T)];
        };

        size_t m_size;
        MemLabelId m_label;
    };
};
