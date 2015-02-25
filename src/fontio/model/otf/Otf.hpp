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
            while (searchRange * 2 <= this->tables.size())
            {
                searchRange <<= 1;
                entrySelector++;
            }

            searchRange *= 16;

            WriteBytes<BigEndian>(out, 0x00010000U);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(this->tables.size()));
            WriteBytes<BigEndian>(out, searchRange);
            WriteBytes<BigEndian>(out, entrySelector);
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(this->tables.size() * 16 - searchRange));
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
            }

            if (globalCrcPos == 0)
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

            WriteBytes<BigEndian>(out, 0xB1B0AFBAUL - globalCrc);
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
