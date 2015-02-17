#pragma once

#include <vector>

#include <fontio/logic/type2/Type2SubroutineAccessor.hpp>
#include <fontio/model/GlyphMetrics.hpp>
#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model;
    using namespace fontio::model::type2;

    class Type2GlyphMetricsCalculator
    {
    public:

        GlyphMetrics CalculateMetrics(
            const Type2Charstring& charstring,
            const std::vector<Type2Charstring>& localSubroutines,
            const std::vector<Type2Charstring>& globalSubroutines)
        {
            return this->CalculateMetrics(
                charstring,
                Type2SubroutineAccessor(localSubroutines),
                Type2SubroutineAccessor(globalSubroutines));
        }

        GlyphMetrics CalculateMetrics(
            const Type2Charstring& charstring,
            const Type2SubroutineAccessor& localSubroutines,
            const Type2SubroutineAccessor& globalSubroutines)
        {
            throw std::logic_error("Not implemented");
        }
    };
} } }
