#pragma once

#include <vector>

#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model::type2;

    class Type2SubroutineAccessor
    {
    private:

        const std::vector<Type2Charstring>& subroutines;

    public:

        Type2SubroutineAccessor(const std::vector<Type2Charstring>& subroutines)
            : subroutines(subroutines)
        {
        }

    public:

        const Type2Charstring& operator [] (size_t index)
        {
            throw std::logic_error("Not implemented");
        }
    };
} } }
