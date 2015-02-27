#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>
#include <fontio/model/otf/OtfPostTableVersion.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfPostTable : public IOtfTable
    {
    private:

        OtfPostTableVersion version;

        float italicAngle;

        uint16_t underlinePosition;

        uint16_t underlineThickness;

        uint32_t isFixedPitch;

        uint32_t minMemType42;

        uint32_t maxMemType42;

        uint32_t minMemType1;

        uint32_t maxMemType1;

    public:

        OtfPostTable(
            OtfPostTableVersion version,
            float italicAngle,
            uint16_t underlinePosition,
            uint16_t underlineThickness,
            uint32_t isFixedPitch,
            uint32_t minMemType42,
            uint32_t maxMemType42,
            uint32_t minMemType1,
            uint32_t maxMemType1)
            : version(version)
            , italicAngle(italicAngle)
            , underlinePosition(underlinePosition)
            , underlineThickness(underlineThickness)
            , isFixedPitch(isFixedPitch)
            , minMemType42(minMemType42)
            , maxMemType42(maxMemType42)
            , minMemType1(minMemType1)
            , maxMemType1(maxMemType1)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Post;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(this->version), crc);
            WriteBytes<BigEndian>(out, static_cast<int32_t>(this->italicAngle * 65536), crc);
            WriteBytes<BigEndian>(out, this->underlinePosition, crc);
            WriteBytes<BigEndian>(out, this->underlineThickness, crc);
            WriteBytes<BigEndian>(out, this->isFixedPitch, crc);
            WriteBytes<BigEndian>(out, this->minMemType42, crc);
            WriteBytes<BigEndian>(out, this->maxMemType42, crc);
            WriteBytes<BigEndian>(out, this->minMemType1, crc);
            WriteBytes<BigEndian>(out, this->maxMemType1, crc);
        }

        virtual uint32_t GetId() const override
        {
            return 0x706f7374; // post
        }
    };
} } }
