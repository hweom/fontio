#include <fstream>

#include <gtest/gtest.h>

#include <fontio/logic/cff/CffReader.hpp>

namespace fontio { namespace logic { namespace cff
{
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
    };

    TEST_F(CffReaderTests, CanReadHeader)
    {
        auto cff = this->ReadFile("test_data/cff/bare.cff");

        ASSERT_EQ(1, cff.GetHeader().GetVersionMajor());
        ASSERT_EQ(0, cff.GetHeader().GetVersionMinor());
        ASSERT_EQ(4, cff.GetHeader().GetHeaderSize());
        ASSERT_EQ(2, cff.GetHeader().GetOffsetSize());
    }
} } }
