#pragma once

#include <cinttypes>

#include <fontio/model/otf/OtfMaxpTableVersion.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfMaxpTable : public IOtfTable
    {
    private:

        OtfMaxpTableVersion version;

        uint16_t numGlyphs;

    public:

        OtfMaxpTable(uint16_t numGlyphs)
            : version(OtfMaxpTableVersion::Version_0_5)
            , numGlyphs(numGlyphs)
        {
        }

    public:

        OtfMaxpTableVersion GetVersion() const
        {
            return this->version;
        }

        uint16_t GetNumGlyphs() const
        {
            return this->numGlyphs;
        }

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Maxp;
        }
    };
} } }
