#pragma once
#include "MemLabelId.h"

struct dynamic_array_detail
{
    void* m_ptr;
    MemLabelId m_label;
    size_t m_size;
    size_t m_capacity;
};

template<typename T, int = 0>
struct dynamic_array : dynamic_array_detail
{
};
