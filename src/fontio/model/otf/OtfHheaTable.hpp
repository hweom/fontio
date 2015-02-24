#pragma once

#include <cinttypes>
#include <stdexcept>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfHheaTable : public IOtfTable
    {
    private:

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
            int16_t	lineGap,
            uint16_t advanceWidthMax,
            int16_t	minLeftSideBearing,
            int16_t	minRightSideBearing,
            int16_t	xMaxExtent,
            int16_t	caretSlopeRise,
            int16_t	caretSlopeRun,
            int16_t	caretOffset,
            uint16_t numberOfHMetrics)
            : lineGap(lineGap)
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
            throw std::logic_error("Not implemented");
        }

        virtual uint32_t GetId() const override
        {
            return 0x68686561; // hhea
        }
    };
} } }
