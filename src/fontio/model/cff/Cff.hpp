#pragma once

#include <fontio/model/cff/CffHeader.hpp>

namespace fontio { namespace model { namespace cff
{
    class Cff
    {
    private:

        CffHeader header;

    public:

        Cff()
        {
        }

        Cff(const CffHeader& header)
            : header(header)
        {
        }

    public:

        const CffHeader& GetHeader() const
        {
            return this->header;
        }
    };
} } }
