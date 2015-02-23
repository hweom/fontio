#pragma once

#include <fontio/model/otf/OtfTableType.hpp>

namespace fontio { namespace model { namespace otf
{
    class IOtfTable
    {
    public:

        virtual ~IOtfTable()
        {
        }

    public:

        virtual OtfTableType GetType() const = 0;
    };
} } }
