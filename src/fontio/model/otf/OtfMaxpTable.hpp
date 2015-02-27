#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/OtfMaxpTableVersion.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

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

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0x00005000UL), crc);

            WriteBytes<BigEndian>(out, this->numGlyphs, crc);
        }

        virtual uint32_t GetId() const override
        {
            return 0x6d617870; // maxp
        }
    };
} } }
