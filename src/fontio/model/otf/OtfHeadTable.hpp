#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfHeadTable : public IOtfTable
    {
    private:

        uint32_t fontRevision;

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

    public:

        OtfHeadTable()
        {
        }

        OtfHeadTable(
            uint32_t fontRevision,
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
            : fontRevision(fontRevision),
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
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0x0001000UL), crc);       // Version 1.0
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0x0001000UL), crc);       // Font revision.
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0), crc);                 // Placeholder for global CRC.
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0x5F0F3CF5UL), crc);      // Magic number.

            WriteBytes<BigEndian>(out, this->flags, crc);
            WriteBytes<BigEndian>(out, this->unitsPerEm, crc);
            WriteBytes<BigEndian>(out, this->created, crc);
            WriteBytes<BigEndian>(out, this->modified, crc);
            WriteBytes<BigEndian>(out, this->xmin, crc);
            WriteBytes<BigEndian>(out, this->ymin, crc);
            WriteBytes<BigEndian>(out, this->xmax, crc);
            WriteBytes<BigEndian>(out, this->ymax, crc);
            WriteBytes<BigEndian>(out, this->macStyle, crc);
            WriteBytes<BigEndian>(out, this->lowestRecPpem, crc);

            WriteBytes<BigEndian>(out, static_cast<int16_t>(2), crc);                  // Font direction hint.
            WriteBytes<BigEndian>(out, static_cast<int16_t>(0), crc);                  // Index to loc format.
            WriteBytes<BigEndian>(out, static_cast<int16_t>(0), crc);                  // Glyph data format.
        }

        virtual uint32_t GetId() const override
        {
            return 0x68656164; // head
        }
    };
} } }
