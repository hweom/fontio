#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfPostTable : public IOtfTable
    {
    private:

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
            float italicAngle,
            uint16_t underlinePosition,
            uint16_t underlineThickness,
            uint32_t isFixedPitch,
            uint32_t minMemType42,
            uint32_t maxMemType42,
            uint32_t minMemType1,
            uint32_t maxMemType1)
            : italicAngle(italicAngle)
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
            throw std::logic_error("Not implemented");
        }

        virtual uint32_t GetId() const override
        {
            return 0x706f7374; // post
        }
    };
} } }
