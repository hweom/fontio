#pragma once

#include <cinttypes>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <utility>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

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
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(0), crc);  // Table version
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(1), crc);  // Number of encodings

            WriteBytes<BigEndian>(out, static_cast<uint16_t>(3), crc);  // Platform ID (Windows).
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(1), crc);  // Encoding ID (Unicode BMP (UCS-2)).
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(12), crc);  // Offset to subtable.

            this->SaveFormat4Subtable(out, crc, this->GetFormat4SubtableSize());
        }

        virtual uint32_t GetId() const override
        {
            return 0x636d6170; // cmap
        }

    private:

        size_t GetFormat4SubtableSize() const
        {
            return
                7 * 2 +                             // Subtable header
                4 * 2 * (this->cmap.size() + 1) +   // Four arrays of shorts
                2;                                  // Pad.
        }

        void SaveFormat4Subtable(std::ostream& out, OtfTableCrc& crc, size_t tableLength) const
        {
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(4), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(tableLength), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(0), crc);

            auto segCount = this->cmap.size() + 1;
            auto searchRange = (1 << static_cast<unsigned>(log2(segCount))) * 2;
            auto entrySelector = static_cast<unsigned>(log2(segCount / 2));
            auto rangeShift = 2 * segCount - searchRange;

            WriteBytes<BigEndian>(out, static_cast<uint16_t>(segCount * 2), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(searchRange), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(entrySelector), crc);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(rangeShift * 2), crc);

            std::vector<std::pair<uint16_t, uint16_t>> pairs(this->cmap.begin(), this->cmap.end());

            std::sort(pairs.begin(), pairs.end(), [](const std::pair<uint16_t, uint16_t>& p1, const std::pair<uint16_t, uint16_t>& p2)
            {
                return p1.second < p2.second;
            });

            pairs.emplace_back(0xffff, 0xffff);

            // Write 'endCount' array
            for (const auto& pair : pairs)
            {
                WriteBytes<BigEndian>(out, pair.second, crc);
            }

            // Write pad.
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(0), crc);

            // Write 'startCount' array
            for (const auto& pair : pairs)
            {
                WriteBytes<BigEndian>(out, pair.second, crc);
            }

            // Write 'idDelta' array
            for (const auto& pair : pairs)
            {
                auto delta = static_cast<int16_t>(pair.first) - static_cast<int16_t>(pair.second);
                WriteBytes<BigEndian>(out, static_cast<int16_t>(delta), crc);
            }

            // Write 'idRangeOffset' array
            for (const auto& pair : pairs)
            {
                WriteBytes<BigEndian>(out, static_cast<uint16_t>(0), crc);
            }
        }
    };
} } }
