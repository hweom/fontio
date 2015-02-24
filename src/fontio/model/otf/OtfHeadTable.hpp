#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfHeadTable : public IOtfTable
    {
    private:

        uint16_t versionMajor;

        uint16_t versionMinor;

        uint16_t fontRevisionMajor;

        uint16_t fontRevisionMinor;

        uint16_t flags;

        uint16_t unitsPerEm;

        int64_t created;

        int64_t modified;

        int16_t xmin;

        int16_t ymin;

        int16_t xmax;

        int16_t ymax;

        uint16_t macStyle;

        uint16_t lowestRecPpem;

        int16_t fontDirectionHint = 2;

    public:

        OtfHeadTable()
        {
        }

        OtfHeadTable(
            uint16_t versionMajor,
            uint16_t versionMinor,
            uint16_t fontRevisionMajor,
            uint16_t fontRevisionMinor,
            uint16_t flags,
            uint16_t unitsPerEm,
            int64_t created,
            int64_t modified,
            int16_t xmin,
            int16_t ymin,
            int16_t xmax,
            int16_t ymax,
            uint16_t macStyle,
            uint16_t lowestRecPpem)
            : versionMajor(versionMajor),
              versionMinor(versionMinor),
              fontRevisionMajor(fontRevisionMajor),
              fontRevisionMinor(fontRevisionMinor),
              flags(flags),
              unitsPerEm(unitsPerEm),
              created(created),
              modified(modified),
              xmin(xmin),
              ymin(ymin),
              xmax(xmax),
              ymax(ymax),
              macStyle(macStyle),
              lowestRecPpem(lowestRecPpem)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Head;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            throw std::logic_error("Not implemented");
        }

        virtual uint32_t GetId() const override
        {
            return 0x68656164; // head
        }
    };
} } }
