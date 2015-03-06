// The Modified BSD License
//
// Copyright (c) 2015, Mikhail Balakhno
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of fontio nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
