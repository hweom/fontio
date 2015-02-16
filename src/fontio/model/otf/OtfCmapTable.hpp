#pragma once

#include <cinttypes>
#include <vector>
#include <utility>

namespace fontio { namespace model { namespace otf
{
    class OtfCmapTable
    {
    private:

        /// <gid:code> pairs.
        /// code is typically Unicode.
        std::vector<std::pair<uint16_t, uint16_t>> cmap;

    public:

        OtfCmapTable()
        {
        }

        OtfCmapTable(const std::vector<std::pair<uint16_t, uint16_t>>& cmap)
            : cmap(cmap)
        {
        }

    };
} } }
