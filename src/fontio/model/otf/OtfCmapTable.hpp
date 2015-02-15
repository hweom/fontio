#pragma once

#include <memory>
#include <vector>

#include <fontio/model/otf/OtfEncodingSubtable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfCmapTable
    {
    private:

        std::vector<std::unique_ptr<OtfEncodingSubtable>> subtables;
    };
} } }
