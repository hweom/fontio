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

        virtual size_t GetCount() const = 0;

        virtual CffCharstringFormat GetFormat() const = 0;
    };
} } }
