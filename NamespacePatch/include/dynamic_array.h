#pragma once
#include "MemLabelId.h"

namespace dynamic_array_detail
{
    struct dynamic_array_data
    {
        void* m_ptr;
        MemLabelId m_label;
        size_t m_size;
        size_t m_capacity;
    };
};

template<typename T, size_t ALIGN = 0>
struct dynamic_array : dynamic_array_detail::dynamic_array_data
{
};
