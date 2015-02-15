#pragma once

#include <memory>
#include <vector>

namespace fontio { namespace model { namespace otf
{
    class OtfEncodingSubtable
    {
    private:

        uint16_t platformId;

        uint16_t encodingId;

    public:

        virtual uint16_t GetFormat() const = 0;
    };
} } }
