#pragma once

#include <vector>

#include <fontio/logic/type2/Type2GlyphMetricsContext.hpp>
#include <fontio/logic/type2/Type2OperatorExecutor.hpp>
#include <fontio/logic/type2/Type2SubroutineAccessor.hpp>
#include <fontio/model/GlyphMetrics.hpp>
#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model;
    using namespace fontio::model::type2;

    class Type2GlyphMetricsCalculator
    {
    private:


    public:

        GlyphMetrics CalculateMetrics(
            const Type2Charstring& charstring,
            const Type2SubroutineAccessor& localSubroutines,
            const Type2SubroutineAccessor& globalSubroutines,
            int nominalWidth,
            int defaultWidth)
        {
            Type2GlyphMetricsContext context;

            Type2OperatorExecutor executor;

            executor.Execute(context, charstring, localSubroutines, globalSubroutines, nominalWidth, defaultWidth);

            return context.GetMetrics();
        }
    };
} } }
