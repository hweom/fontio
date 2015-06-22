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

#include <memory>
#include <ostream>
#include <vector>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>
#include <fontio/model/otf/OtfTableCrc.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

    class Otf
    {
    private:

        std::vector<std::unique_ptr<IOtfTable>> tables;

    public:

        Otf(std::vector<std::unique_ptr<IOtfTable>>&& tables)
            : tables(std::move(tables))
        {
        }

    public:

        bool HasTable(OtfTableType type) const
        {
            for (const auto& t : this->tables)
            {
                if (t->GetType() == type)
                {
                    return true;
                }
            }

            return false;
        }

        const IOtfTable& GetTable(OtfTableType type) const
        {
            for (const auto& t : this->tables)
            {
                if (t->GetType() == type)
                {
                    return *t;
                }
            }

            throw std::logic_error("No such table");
        }

        void Save(std::ostream& out) const
        {
            OtfTableCrc globalCrc;

            auto startPos = out.tellp();

            this->WriteSfnt(out, globalCrc);

            this->WriteTableRecords(out, startPos, globalCrc);
        }

    private:

        void WriteSfnt(std::ostream& out, OtfTableCrc& globalCrc) const
        {
            auto searchRange = static_cast<uint16_t>(this->tables.size());
            auto entrySelector = static_cast<uint16_t>(0);
            while (static_cast<size_t>(searchRange * 2) <= this->tables.size())
            {
                searchRange <<= 1;
                entrySelector++;
            }

            searchRange *= 16;

            out.write("OTTO", 4);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(this->tables.size()));
            WriteBytes<BigEndian>(out, searchRange);
            WriteBytes<BigEndian>(out, entrySelector);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(this->tables.size() * 16 - searchRange));

            // Write placeholders for table headers.
            for (size_t i = 0; i < this->tables.size() * 16; i++)
            {
                out.put(0);
            }
        }

        void WriteTableRecords(std::ostream& out, std::ostream::pos_type fileStart, OtfTableCrc& globalCrc) const
        {
            std::ostream::pos_type globalCrcPos = 0;

            size_t tableIndex = 0;
            for (const auto& table : this->tables)
            {
                OtfTableCrc crc;

                auto tableStart = out.tellp();

                if (table->GetType() == OtfTableType::Head)
                {
                    globalCrcPos = tableStart + static_cast<std::streamoff>(8);
                }

                table->Save(out, crc);

                this->PadTable(out, crc);

                auto tableEnd = out.tellp();
                auto tableLength = tableEnd - tableStart;

                this->WriteTableIndices(
                    out,
                    fileStart,
                    tableIndex,
                    table->GetId(),
                    crc.GetCrc(),
                    static_cast<uint32_t>(tableStart),
                    static_cast<uint32_t>(tableLength),
                    globalCrc);

                tableIndex++;

                globalCrc.Adjust(crc.GetCrc());

                out.seekp(tableEnd);
            }

            if (static_cast<size_t>(globalCrcPos) == 0)
            {
                throw std::runtime_error("No head table in OTF!");
            }

            this->WriteGlobalCrc(out, globalCrcPos, globalCrc.GetCrc());
        }

        void PadTable(std::ostream& out, OtfTableCrc& crc) const
        {
            while (crc.GetPadBytes() > 0)
            {
                WriteBytes<BigEndian>(out, static_cast<uint8_t>(0), crc);
            }
        }

        void WriteGlobalCrc(std::ostream& out, std::ostream::pos_type globalCrcPos, uint32_t globalCrc) const
        {
            out.seekp(globalCrcPos);

            WriteBytes<BigEndian>(out, static_cast<uint32_t>(0xB1B0AFBAUL - globalCrc));
        }

        void WriteTableIndices(
            std::ostream& out,
            std::ostream::pos_type fileStart,
            size_t tableIndex,
            uint32_t tableId,
            uint32_t tableCrc,
            uint32_t tableOffset,
            uint32_t tableLength,
            OtfTableCrc& globalCrc) const
        {
            out.seekp(fileStart + static_cast<std::streamoff>(12 + 16 * tableIndex));

            WriteBytes<BigEndian>(out, tableId, globalCrc);
            WriteBytes<BigEndian>(out, tableCrc, globalCrc);
            WriteBytes<BigEndian>(out, tableOffset, globalCrc);
            WriteBytes<BigEndian>(out, tableLength, globalCrc);
        }
    };
} } }
