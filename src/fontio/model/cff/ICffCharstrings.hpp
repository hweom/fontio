#pragma once

#include <fontio/model/cff/CffCharstringFormat.hpp>

namespace fontio { namespace model { namespace cff
{
    class ICffCharstrings
    {
    public:

        virtual ~ICffCharstrings()
        {
        }

    public:

        virtual CffCharstringFormat GetFormat() const = 0;
    };
} } }
