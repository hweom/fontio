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

#include <stdexcept>
#include <vector>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/GlyphMetrics.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class OtfHmtxTable : public IOtfTable
    {
    private:

        std::vector<GlyphMetrics> metrics;

    public:

        OtfHmtxTable(const std::vector<GlyphMetrics>& metrics)
            : metrics(metrics)
        {
        }

    public:

        const std::vector<GlyphMetrics>& GetMetrics() const
        {
            return this->metrics;
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Hmtx;
        }

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            for (const auto& metric : this->metrics)
            {
                WriteBytes<BigEndian>(out, static_cast<uint16_t>(metric.GetAdvanceWidth()), crc);
                WriteBytes<BigEndian>(out, static_cast<int16_t>(metric.GetLeftSideBearings()), crc);
            }
        }

        virtual uint32_t GetId() const override
        {
            return 0x686d7478; // hmtx
        }
    };
} } }
