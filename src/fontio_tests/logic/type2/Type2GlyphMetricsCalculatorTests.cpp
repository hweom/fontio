// The Modified BSD License
//
// Copyright (c) 2015, Mikhail Balakhno
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of fontio nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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

        std::unique_ptr<Cff> ReadCffFile(const std::string& filename)
        {
            std::ifstream stream(filename, std::ios_base::binary);

            return this->reader.ReadCff(stream);
        }
    };

    TEST_F(Type2GlyphMetricsCalculatorTests, CanCalculateMetrics)
    {
        auto cff = this->ReadCffFile("test_data/cff/bare.cff");

        const auto& charstrings = static_cast<const CffType2Charstrings&>(cff->GetTopDicts()[0].GetCharstrings()).GetCharstrings();

        auto metrics = this->calculator.CalculateMetrics(
            charstrings[10],
            Type2SubroutineAccessor(),
            Type2SubroutineAccessor(),
            472,
            220);

        ASSERT_EQ(328, metrics.GetAdvanceWidth());
        ASSERT_EQ(12, metrics.GetBoundBox().GetX0());
        ASSERT_EQ(-120, metrics.GetBoundBox().GetY0());
        ASSERT_EQ(273, metrics.GetBoundBox().GetX1());
        ASSERT_EQ(739, metrics.GetBoundBox().GetY1());
        ASSERT_EQ(12, metrics.GetLeftSideBearings());
    }

    TEST_F(Type2GlyphMetricsCalculatorTests, CanCalculateSpaceWidth)
    {
        auto cff = this->ReadCffFile("test_data/cff/test_font_width.cff");

        const auto& topDict = cff->GetTopDicts()[0];
        const auto& charstrings = static_cast<const CffType2Charstrings&>(topDict.GetCharstrings()).GetCharstrings();

        auto metrics = this->calculator.CalculateMetrics(
            charstrings[0],
            Type2SubroutineAccessor(),
            Type2SubroutineAccessor(),
            topDict.GetNominalWidthX(),
            topDict.GetDefaultWidthX());

        ASSERT_EQ(227, metrics.GetAdvanceWidth());
    }

} } }
