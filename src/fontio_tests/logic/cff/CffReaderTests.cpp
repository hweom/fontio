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

        Cff ReadFile(const std::string& filename)
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

        ASSERT_EQ(1, cff.GetHeader().GetVersionMajor());
        ASSERT_EQ(0, cff.GetHeader().GetVersionMinor());
        ASSERT_EQ(4, cff.GetHeader().GetHeaderSize());
        ASSERT_EQ(2, cff.GetHeader().GetOffsetSize());
    }

    TEST_F(CffReaderTests, CanReadNameIndex)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff.GetNameIndex().GetNames().size());
        ASSERT_EQ("GuardianSans-Regular", cff.GetNameIndex().GetNames()[0]);
    }

    TEST_F(CffReaderTests, CanReadTopDict)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff.GetTopDicts().size());

        const auto& topDict = cff.GetTopDicts()[0];

        this->AssertFontMatrixEqual(CffFontMatrix(0.001, 0.0, 0.0, 0.001, 0.0, 0.0), topDict.GetFontMatrix());

        this->AssertFontBBoxEqual(BoundBox(-175, -217, 1194, 1061), topDict.GetBoundBox());

        ASSERT_EQ("Regular", topDict.GetWeight());
    }

    TEST_F(CffReaderTests, CanReadCharset)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        const auto& strings = cff.GetStringIndex();
        const auto& topDict = cff.GetTopDicts()[0];

        const auto& charset = topDict.GetCharset();

        ASSERT_EQ(".notdef", strings.GetString(charset[0]));
        ASSERT_EQ("zero", strings.GetString(charset[17]));
        ASSERT_EQ("bracketright", strings.GetString(charset[62]));
        ASSERT_EQ("sterling", strings.GetString(charset[98]));
    }

    TEST_F(CffReaderTests, CanReadAnotherCff)
    {
        auto cff = this->ReadFile("test_data/cff/test_8.cff");

        const auto& topDict = cff.GetTopDicts()[0];

        topDict.GetCharset();
    }
} } }
