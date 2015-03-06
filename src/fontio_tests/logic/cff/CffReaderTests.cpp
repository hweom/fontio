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

namespace fontio { namespace logic { namespace cff
{
    using namespace fontio::model;
    using namespace fontio::model::cff;

    class CffReaderTests : public testing::Test
    {
    protected:

        CffReader reader;

    protected:

        std::unique_ptr<Cff> ReadFile(const std::string& filename)
        {
            std::ifstream stream(filename, std::ios_base::binary);

            return this->reader.ReadCff(stream);
        }

        void AssertFontMatrixEqual(const CffFontMatrix& expect, const CffFontMatrix& matrix) const
        {
            ASSERT_FLOAT_EQ(expect.GetData()[0][0], matrix.GetData()[0][0]);
            ASSERT_FLOAT_EQ(expect.GetData()[0][1], matrix.GetData()[0][1]);
            ASSERT_FLOAT_EQ(expect.GetData()[1][0], matrix.GetData()[1][0]);
            ASSERT_FLOAT_EQ(expect.GetData()[1][1], matrix.GetData()[1][1]);
            ASSERT_FLOAT_EQ(expect.GetData()[2][0], matrix.GetData()[2][0]);
            ASSERT_FLOAT_EQ(expect.GetData()[2][1], matrix.GetData()[2][1]);
        }

        void AssertFontBBoxEqual(const BoundBox& expect, const BoundBox& box) const
        {
            ASSERT_EQ(expect.GetX0(), box.GetX0());
            ASSERT_EQ(expect.GetY0(), box.GetY0());
            ASSERT_EQ(expect.GetX1(), box.GetX1());
            ASSERT_EQ(expect.GetY1(), box.GetY1());
        }

    };

    TEST_F(CffReaderTests, CanReadHeader)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff->GetHeader().GetVersionMajor());
        ASSERT_EQ(0, cff->GetHeader().GetVersionMinor());
        ASSERT_EQ(4, cff->GetHeader().GetHeaderSize());
        ASSERT_EQ(2, cff->GetHeader().GetOffsetSize());
    }

    TEST_F(CffReaderTests, CanReadNameIndex)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff->GetNameIndex().GetNames().size());
        ASSERT_EQ("GuardianSans-Regular", cff->GetNameIndex().GetNames()[0]);
    }

    TEST_F(CffReaderTests, CanReadTopDict)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff->GetTopDicts().size());

        const auto& topDict = cff->GetTopDicts()[0];

        this->AssertFontMatrixEqual(CffFontMatrix(0.001, 0.0, 0.0, 0.001, 0.0, 0.0), topDict.GetFontMatrix());

        this->AssertFontBBoxEqual(BoundBox(-175, -217, 1194, 1061), topDict.GetBoundBox());

        ASSERT_EQ("Regular", topDict.GetWeight());
    }

    TEST_F(CffReaderTests, CanReadCharset)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        const auto& strings = cff->GetStringIndex();
        const auto& topDict = cff->GetTopDicts()[0];

        const auto& charset = topDict.GetCharset();

        ASSERT_EQ(".notdef", strings.GetString(charset[0]));
        ASSERT_EQ("zero", strings.GetString(charset[17]));
        ASSERT_EQ("bracketright", strings.GetString(charset[62]));
        ASSERT_EQ("sterling", strings.GetString(charset[98]));
    }

    TEST_F(CffReaderTests, CanReadAnotherCff)
    {
        auto cff = this->ReadFile("test_data/cff/test_font_8.cff");

        const auto& topDict = cff->GetTopDicts()[0];

        topDict.GetCharset();
    }
} } }
