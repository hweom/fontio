#include <fstream>

#include <gtest/gtest.h>

#include <fontio/logic/cff/CffReader.hpp>
#include <fontio/logic/otf/OtfFromCffConverter.hpp>

namespace fontio { namespace logic { namespace otf
{
    using namespace fontio::logic::cff;
    using namespace fontio::model;
    using namespace fontio::model::cff;
    using namespace fontio::model::otf;

    class OtfFromCffConverterTests : public testing::Test
    {
    protected:

        CffReader reader;

        OtfFromCffConverter converter;

    protected:

        std::unique_ptr<Otf> ConvertFile(const std::string& filename)
        {
            return this->converter.ConvertFromCff(filename);
        }
    };

    TEST_F(OtfFromCffConverterTests, CanConvertCffAndSaveIt)
    {
        auto cff = this->ConvertFile("test_data/cff/bare.cff");

        std::ofstream stream("bare.otf", std::ios_base::binary);

        cff->Save(stream);
    }
} } }
