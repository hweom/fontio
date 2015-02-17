#pragma once

#include <vector>

#include <fontio/model/GlyphMetrics.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfHmtxTable
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
    };
} } }
