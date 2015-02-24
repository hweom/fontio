#pragma once

#include <cinttypes>
#include <stdexcept>
#include <vector>
#include <utility>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfCmapTable : public IOtfTable
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

    public:

        const std::vector<std::pair<uint16_t, uint16_t>>& GetCmap() const
        {
            return this->cmap;
        }

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Cmap;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            throw std::logic_error("Not implemented");
        }

        virtual uint32_t GetId() const override
        {
            return 0x636d6170; // cmap
        }
    };
} } }
