#pragma once

#include <cinttypes>

namespace fontio { namespace model { namespace cff
{
    class CffPrivateDict
    {
    private:

        uint32_t subrsOffset;

        int32_t defaultWidthX;

        int32_t nominalWidthX;

    public:

        CffPrivateDict(
            uint32_t subrsOffset,
            int32_t defaultWidthX,
            int32_t nominalWidthX)
            : subrsOffset(subrsOffset)
            , defaultWidthX(defaultWidthX)
            , nominalWidthX(nominalWidthX)
        {
        }

    public:

        uint32_t GetSubrsOffset() const
        {
            return this->subrsOffset;
        }

        int32_t GetDefaultWidthX() const
        {
            return this->defaultWidthX;
        }

        int32_t GetNominalWidthX() const
        {
            return this->nominalWidthX;
        }
    };
} } }
