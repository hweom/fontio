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
