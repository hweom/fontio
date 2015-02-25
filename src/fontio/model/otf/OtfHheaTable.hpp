#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfHheaTable : public IOtfTable
    {
    private:

        uint16_t ascender;

        uint16_t descender;

        int16_t	lineGap;

        uint16_t advanceWidthMax;

        int16_t	minLeftSideBearing;

        int16_t	minRightSideBearing;

        int16_t	xMaxExtent;

        int16_t	caretSlopeRise;

        int16_t	caretSlopeRun;

        int16_t	caretOffset;

        uint16_t numberOfHMetrics;

    public:

        OtfHheaTable(
            uint16_t ascender,
            uint16_t descender,
            int16_t	lineGap,
            uint16_t advanceWidthMax,
            int16_t	minLeftSideBearing,
            int16_t	minRightSideBearing,
            int16_t	xMaxExtent,
            int16_t	caretSlopeRise,
            int16_t	caretSlopeRun,
            int16_t	caretOffset,
            uint16_t numberOfHMetrics)
            : ascender(ascender)
            , descender(descender)
            , lineGap(lineGap)
            , advanceWidthMax(advanceWidthMax)
            , minLeftSideBearing(minLeftSideBearing)
            , minRightSideBearing(minRightSideBearing)
            , xMaxExtent(xMaxExtent)
            , caretSlopeRise(caretSlopeRise)
            , caretSlopeRun(caretSlopeRun)
            , caretOffset(caretOffset)
            , numberOfHMetrics(numberOfHMetrics)
        {
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Hhea;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0x0001000UL), crc);       // Version 1.0

            WriteBytes<BigEndian>(out, this->ascender, crc);
            WriteBytes<BigEndian>(out, this->descender, crc);
            WriteBytes<BigEndian>(out, this->lineGap, crc);
            WriteBytes<BigEndian>(out, this->advanceWidthMax, crc);
            WriteBytes<BigEndian>(out, this->minLeftSideBearing, crc);
            WriteBytes<BigEndian>(out, this->minRightSideBearing, crc);
            WriteBytes<BigEndian>(out, this->xMaxExtent, crc);
            WriteBytes<BigEndian>(out, this->caretSlopeRise, crc);
            WriteBytes<BigEndian>(out, this->caretSlopeRun, crc);
            WriteBytes<BigEndian>(out, this->caretOffset, crc);

            WriteBytes<BigEndian>(out, static_cast<uint64_t>(0), crc);
            WriteBytes<BigEndian>(out, static_cast<int16_t>(0), crc);

            WriteBytes<BigEndian>(out, this->numberOfHMetrics, crc);
        }

        virtual uint32_t GetId() const override
        {
            return 0x68686561; // hhea
        }
    };
} } }
