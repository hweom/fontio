#pragma once

#include <cinttypes>
#include <istream>
#include <stdexcept>
#include <vector>

namespace fontio { namespace model { namespace cff
{
    class CffIndex
    {
    private:

        std::vector<uint32_t> offsets;

    public:

        CffIndex(const std::vector<uint32_t>& offsets)
            : offsets(offsets)
        {
        }

    public:

        const std::vector<uint32_t>& GetOffsets() const
        {
            return this->offsets;
        }
    };
} } }
