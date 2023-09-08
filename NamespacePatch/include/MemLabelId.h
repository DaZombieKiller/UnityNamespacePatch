#pragma once

enum MemLabelIdentifier
{
};

struct AllocationRootWithSalt
{
    unsigned m_Salt;
    unsigned m_RootReferenceIndex;
};

struct MemLabelId
{
    AllocationRootWithSalt m_RootReferenceWithSalt;
    MemLabelIdentifier identifier;
};
