#pragma once

#include <istream>

#include <fontio/model/cff/Cff.hpp>

namespace fontio { namespace logic { namespace cff
{
    using namespace fontio::model::cff;

    class CffReader
    {
    public:

        Cff ReadCff(std::istream& stream)
        {
            CffHeader header(stream);

            return Cff(header);
        }
    };
} } }
