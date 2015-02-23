#pragma once

#include <vector>

#include <fontio/model/GlyphMetrics.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
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
    };
} } }
