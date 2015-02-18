#include <fstream>

#include <gtest/gtest.h>

#include <fontio/logic/cff/CffReader.hpp>
#include <fontio/logic/type2/Type2GlyphMetricsCalculator.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::logic::cff;
    using namespace fontio::model;
    using namespace fontio::model::cff;
    using namespace fontio::model::type2;

    class Type2GlyphMetricsCalculatorTests : public testing::Test
    {
    protected:

        CffReader reader;

        Type2GlyphMetricsCalculator calculator;

    protected:

        Cff ReadCffFile(const std::string& filename)
        {
            std::ifstream stream(filename, std::ios_base::binary);

            return this->reader.ReadCff(stream);
        }
    };

    TEST_F(Type2GlyphMetricsCalculatorTests, CanCalculateMetrics)
    {
        auto cff = this->ReadCffFile("test_data/cff/bare.cff");

        const auto& charstrings = static_cast<const CffType2Charstrings&>(cff.GetTopDicts()[0].GetCharstrings()).GetCharstrings();

        auto metrics = this->calculator.CalculateMetrics(charstrings[10], Type2SubroutineAccessor(), Type2SubroutineAccessor());

        ASSERT_EQ(0, metrics.GetAdvanceWidth());
        ASSERT_EQ(0, metrics.GetBoundBox().GetX0());
        ASSERT_EQ(0, metrics.GetBoundBox().GetY0());
        ASSERT_EQ(0, metrics.GetBoundBox().GetX1());
        ASSERT_EQ(0, metrics.GetBoundBox().GetY1());
        ASSERT_EQ(0, metrics.GetLeftSideBearings());
    }

} } }
