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
