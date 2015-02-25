#pragma once

#include <map>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/OtfNameId.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfNameTable : public IOtfTable
    {
    private:

        std::map<OtfNameId, std::wstring> names;

    public:

        OtfNameTable(const std::map<OtfNameId, std::wstring>& names)
            : names(names)
        {
        }

        OtfNameTable(std::initializer_list<std::pair<const OtfNameId, std::wstring>>& names)
            : names(names)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Name;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            throw std::logic_error("Not implemented");
        }

        virtual uint32_t GetId() const override
        {
            return 0x6e616d65; // name
        }
    };
} } }
