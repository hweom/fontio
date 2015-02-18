#pragma once

#include <vector>

#include <fontio/model/cff/ICffCharstrings.hpp>
#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace model { namespace cff
{
    using namespace fontio::model::type2;

    class CffType2Charstrings : public ICffCharstrings
    {
    private:

        std::vector<Type2Charstring> charstrings;

    public:

        CffType2Charstrings(std::vector<Type2Charstring>&& charstrings)
            : charstrings(std::move(charstrings))
        {
        }

    public:

        const std::vector<Type2Charstring>& GetCharstrings() const
        {
            return this->charstrings;
        }

        virtual CffCharstringFormat GetFormat() const override
        {
            return CffCharstringFormat::Type2;
        }
    };
} } }
