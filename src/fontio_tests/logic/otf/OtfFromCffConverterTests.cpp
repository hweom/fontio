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

    TEST_F(OtfFromCffConverterTests, CanConvertCff6)
    {
        auto cff = this->ConvertFile("test_data/cff/test_font_6.cff");

        std::ofstream stream("test_font_6.otf", std::ios_base::binary);

        cff->Save(stream);
    }

    TEST_F(OtfFromCffConverterTests, CanConvertCff31)
    {
        auto cff = this->ConvertFile("test_data/cff/symbol.cff");

        std::ofstream stream("symbol.otf", std::ios_base::binary);

        cff->Save(stream);
    }

    TEST_F(OtfFromCffConverterTests, CanConvertCffWithAdobeCharset)
    {
        auto otf = this->ConvertFile("test_data/cff/iso_adobe_charset.cff");

        std::ofstream stream("iso_adobe_charset.otf", std::ios_base::binary);

        otf->Save(stream);
    }
} } }
