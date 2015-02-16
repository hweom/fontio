#pragma once

#include <fontio/model/cff/CffCharstringFormat.hpp>

namespace fontio { namespace model { namespace cff
{
    class ICffCharstring
    {
    public:

        virtual ~ICffCharstring()
        {
        }

    public:

        virtual CffCharstringFormat GetFormat() const = 0;
    };
} } }
