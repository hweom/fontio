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
