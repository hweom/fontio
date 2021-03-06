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

#pragma once

#include <algorithm>

#include <fontio/logic/cff/CffReader.hpp>
#include <fontio/logic/type2/Type2GlyphMetricsCalculator.hpp>
#include <fontio/model/AdobeStandardEncoding.hpp>
#include <fontio/model/cff/Cff.hpp>
#include <fontio/model/cff/CffType2Charstrings.hpp>
#include <fontio/model/otf/Otf.hpp>
#include <fontio/model/otf/OtfCffTable.hpp>
#include <fontio/model/otf/OtfCmapTable.hpp>
#include <fontio/model/otf/OtfHeadTable.hpp>
#include <fontio/model/otf/OtfHheaTable.hpp>
#include <fontio/model/otf/OtfHmtxTable.hpp>
#include <fontio/model/otf/OtfMaxpTable.hpp>
#include <fontio/model/otf/OtfNameTable.hpp>
#include <fontio/model/otf/OtfOs2Table.hpp>
#include <fontio/model/otf/OtfPostTable.hpp>
#include <fontio/model/otf/OtfUnicodeRanges.hpp>

namespace fontio { namespace logic { namespace otf
{
    using namespace fontio::logic::cff;
    using namespace fontio::logic::type2;
    using namespace fontio::model;
    using namespace fontio::model::cff;
    using namespace fontio::model::otf;

    class OtfFromCffConverter
    {
    public:

        static const int16_t DEFAULT_LINE_GAP = 90;

    public:

        std::unique_ptr<Otf> ConvertFromCff(const std::string& cffFilename, size_t fontIndex = 0)
        {
            std::ifstream stream(cffFilename, std::ios_base::binary);

            return this->ConvertFromCff(stream, fontIndex);
        }

        std::unique_ptr<Otf> ConvertFromCff(std::istream& stream, size_t fontIndex = 0)
        {
            auto start = stream.tellg();

            auto cff = CffReader().ReadCff(stream);

            stream.seekg(start);
            stream.clear();

            const auto& topDict = cff->GetTopDicts()[fontIndex];
            const auto& strings = cff->GetStringIndex();

            auto glyphMetrics =this->CalculateGlyphMetrics(*cff, topDict);

            std::vector<std::unique_ptr<IOtfTable>> tables;

            auto cmapTablePtr = this->ConvertCmapTable(*cff, topDict);
            const auto& cmapTable = *cmapTablePtr;

            tables.push_back(std::move(cmapTablePtr));
            tables.push_back(this->ConvertHeadTable(topDict));
            tables.push_back(this->ConvertHmtxTable(glyphMetrics));
            tables.push_back(this->ConvertHheaTable(topDict, glyphMetrics));
            tables.push_back(this->ConvertMaxpTable(topDict));
            tables.push_back(this->ConvertNameTable(topDict));
            tables.push_back(this->ConvertOs2Table(topDict, glyphMetrics, cmapTable));
            tables.push_back(this->ConvertPostTable(topDict, strings));
            tables.push_back(std::unique_ptr<IOtfTable>(new OtfCffTable(stream)));

            return std::unique_ptr<Otf>(new Otf(std::move(tables)));
        }

    private:

        std::unique_ptr<OtfCmapTable> ConvertCmapTable(const Cff& cff, const CffTopDict& topDict)
        {
            AdobeStandardEncoding glyphList;
            const auto& strings = cff.GetStringIndex();

            std::vector<std::pair<uint16_t, uint16_t>> cmap;
            for (const auto& pair : topDict.GetCharset().GetGidToSidMap())
            {
                auto charName = strings.GetString(pair.second);
                auto unicode = glyphList.GetCode(charName);

                if (unicode > 0)
                {
                    cmap.push_back(std::make_pair(pair.first, unicode));
                }
            }

            return std::unique_ptr<OtfCmapTable>(new OtfCmapTable(cmap));
        }

        std::unique_ptr<OtfHeadTable> ConvertHeadTable(const CffTopDict& topDict)
        {
            auto fontsPerEm = (uint16_t)(1.0 / topDict.GetFontMatrix().GetScale());
            auto currentDate = 0;
            auto bbox = topDict.GetBoundBox();

            return std::unique_ptr<OtfHeadTable>(new OtfHeadTable(
                0,
                this->GetHeadFlags(topDict),
                fontsPerEm,
                currentDate,
                currentDate,
                (int16_t)bbox.GetX0(),
                (int16_t)bbox.GetY0(),
                (int16_t)bbox.GetX1(),
                (int16_t)bbox.GetY1(),
                0,
                1));
        }

        std::unique_ptr<OtfHmtxTable> ConvertHmtxTable(const std::vector<GlyphMetrics>& glyphMetrics)
        {
            return std::unique_ptr<OtfHmtxTable>(new OtfHmtxTable(glyphMetrics));
        }

        std::unique_ptr<OtfNameTable> ConvertNameTable(const CffTopDict& topDict)
        {
            return std::unique_ptr<OtfNameTable>(new OtfNameTable(
                std::map<OtfNameId, std::wstring>(
                {
                    { OtfNameId::Copyright, this->ToWString(topDict.GetCopyright()) },
                    { OtfNameId::FontFamily, this->ToWString(topDict.GetFamilyName()) },
                    { OtfNameId::UniqueFontId, this->ToWString(topDict.GetFullName()) },
                    { OtfNameId::FullFontName, this->ToWString(topDict.GetFullName()) },
                    { OtfNameId::VersionString, this->ToWString(topDict.GetVersion()) }
                })));
        }

        std::unique_ptr<OtfHheaTable> ConvertHheaTable(const CffTopDict& topDict, const std::vector<GlyphMetrics>& glyphMetrics)
        {
            int16_t ascent = 0;
            int16_t descent = 0;
            int16_t advanceWidthMax = 0;
            int16_t	minLeftSideBearing = 0;
            int16_t minRightSideBearing = 0;
            int16_t maxExtent = 0;

            for (const auto& metrics : glyphMetrics)
            {
                auto rightSideBearing = static_cast<int16_t>(metrics.GetAdvanceWidth() - metrics.GetLeftSideBearings() - metrics.GetBoundBox().GetWidth());
                auto extent = static_cast<int16_t>(metrics.GetLeftSideBearings() + metrics.GetBoundBox().GetWidth());

                ascent = std::max(ascent, static_cast<int16_t>(metrics.GetBoundBox().GetY1()));
                descent = std::min(descent, static_cast<int16_t>(metrics.GetBoundBox().GetY0()));
                advanceWidthMax = std::max(advanceWidthMax, static_cast<int16_t>(metrics.GetAdvanceWidth()));
                minLeftSideBearing = std::min(minLeftSideBearing, static_cast<int16_t>(metrics.GetLeftSideBearings()));
                minRightSideBearing = std::min(minRightSideBearing, rightSideBearing);
                maxExtent = std::max(maxExtent, extent);
            }

            return std::unique_ptr<OtfHheaTable>(new OtfHheaTable(
                ascent,
                descent,
                DEFAULT_LINE_GAP,
                advanceWidthMax,
                minLeftSideBearing,
                minRightSideBearing,
                maxExtent,
                1,
                0,
                0,
                static_cast<uint16_t>(glyphMetrics.size())));
        }

        std::unique_ptr<OtfMaxpTable> ConvertMaxpTable(const CffTopDict& topDict)
        {
            return std::unique_ptr<OtfMaxpTable>(new OtfMaxpTable(
                static_cast<uint16_t>(topDict.GetCharstrings().GetCount())));
        }

        std::unique_ptr<OtfOs2Table> ConvertOs2Table(
            const CffTopDict& topDict,
            const std::vector<GlyphMetrics>& glyphMetrics,
            const OtfCmapTable& cmapTable)
        {
            size_t nonZeroGlyphs = 0;
            int16_t avgWidth = 0;
            int16_t ymax = 0;
            int16_t ymin = 0;
            int16_t sxHeight = 0;
            int16_t scapHeight = 0;
            uint16_t firstChar = 0xFFFF;
            uint16_t lastChar = 0;

            for (auto& metric : glyphMetrics)
            {
                if (metric.GetAdvanceWidth() > 0)
                {
                    avgWidth += metric.GetAdvanceWidth();
                    ymax = std::max(ymax, static_cast<int16_t>(metric.GetBoundBox().GetY1()));
                    ymin = std::min(ymin, static_cast<int16_t>(metric.GetBoundBox().GetY0()));

                    nonZeroGlyphs++;
                }
            }

            for (const auto& pair : cmapTable.GetCmap())
            {
                if ((pair.second == 0) || (pair.first >= glyphMetrics.size()))
                {
                    continue;
                }

                firstChar = std::min(firstChar, pair.second);
                lastChar = std::max(lastChar, pair.second);

                if (pair.second == 'x')
                {
                    sxHeight = glyphMetrics[pair.first].GetBoundBox().GetY1();
                }
                else if (pair.second == 'H')
                {
                    scapHeight = glyphMetrics[pair.first].GetBoundBox().GetY1();
                }
            }

            int heightUnit = static_cast<int>(1.0 / topDict.GetFontMatrix().GetScale());

            int subscriptW = static_cast<int>(heightUnit * 0.65);
            int subscriptH = static_cast<int>(heightUnit * 0.70);
            int subscriptYOffset = static_cast<int>(heightUnit * 0.2);

            return std::unique_ptr<OtfOs2Table>(new OtfOs2Table(
                avgWidth,
                this->GetWeightClass(topDict.GetWeight()),
                5, // Normal width
                0, // No embedding flags
                subscriptW,
                subscriptH,
                0, // Subscript X offset
                subscriptYOffset,
                subscriptW,
                subscriptH,
                0, // Superscript X offset
                subscriptH - subscriptYOffset,
                static_cast<int16_t>(heightUnit * 0.05), // Strikeout size
                static_cast<int16_t>(heightUnit * 0.25), // Strikeout pos
                0, // Family class,
                OtfOs2Table::Panose(),
                this->CalculateUsedUnicodeRanges(cmapTable),
                "ftio",
                (1 << 6), // Regular font
                firstChar,
                lastChar,
                static_cast<int16_t>(heightUnit * 0.8), // Typographic ascender
                static_cast<int16_t>(-heightUnit * 0.2), // Typographic descender
                static_cast<int16_t>(heightUnit * 0.09), // Typographic line gap
                ymax,
                ymin,
                1, // Codepage ranges
                sxHeight,
                scapHeight,
                0, // Default char
                ' ', // Break char
                1 // Max context
            ));
        }

        std::unique_ptr<OtfPostTable> ConvertPostTable(const CffTopDict& topDict, const CffStringIndex& strings)
        {
            int heightUnit = static_cast<int>(1.0 / topDict.GetFontMatrix().GetScale());

            const auto& gidToSidMap = topDict.GetCharset().GetGidToSidMap();

            std::vector<std::string> glyphNames;
            for (uint16_t i = 0; i < topDict.GetCharstrings().GetCount(); i++)
            {
                auto gid = i + 1;
                auto name = std::string(".notdef");

                auto pos = gidToSidMap.find(gid);
                if (pos != gidToSidMap.end())
                {
                    name = strings.GetString(pos->second);
                }

                glyphNames.push_back(name);
            }

            return std::unique_ptr<OtfPostTable>(new OtfPostTable(
                0.0f,
                static_cast<int16_t>(-heightUnit * 0.125),
                static_cast<int16_t>(heightUnit * 0.05),
                0,
                0,
                0,
                0,
                0,
                std::move(glyphNames)));
        }

        std::vector<GlyphMetrics> CalculateGlyphMetrics(const Cff& cff, const CffTopDict& topDict)
        {
            auto localSubroutines = topDict.HasLocalSubroutines()
                ? Type2SubroutineAccessor(static_cast<const CffType2Charstrings&>(topDict.GetLocalSubroutines()).GetCharstrings())
                : Type2SubroutineAccessor();

            auto globalSubroutines = cff.HasGlobalSubroutines()
                ? Type2SubroutineAccessor(static_cast<const CffType2Charstrings&>(cff.GetGlobalSubroutines()).GetCharstrings())
                : Type2SubroutineAccessor();

            return this->CalculateType2GlyphMetrics(
                topDict,
                static_cast<const CffType2Charstrings&>(topDict.GetCharstrings()).GetCharstrings(),
                localSubroutines,
                globalSubroutines);
        }

        std::vector<GlyphMetrics> CalculateType2GlyphMetrics(
            const CffTopDict& topDict,
            const std::vector<Type2Charstring>& charstrings,
            Type2SubroutineAccessor localSubroutines,
            Type2SubroutineAccessor globalSubroutines)
        {
            std::vector<GlyphMetrics> result;

            Type2GlyphMetricsCalculator calculator;

            for (const auto& charstring : charstrings)
            {
                auto metrics = calculator.CalculateMetrics(
                    charstring,
                    localSubroutines,
                    globalSubroutines,
                    topDict.GetNominalWidthX(),
                    topDict.GetDefaultWidthX());

                result.push_back(metrics);
            }

            return result;
        }

        uint16_t GetHeadFlags(const CffTopDict& topDict)
        {
            return 0;
        }

        std::wstring ToWString(const std::string& string)
        {
            return std::wstring(string.begin(), string.end());
        }

        uint16_t GetWeightClass(const std::string& weight)
        {
            std::string lowercaseWeight = weight;
            std::transform(lowercaseWeight.begin(), lowercaseWeight.end(), lowercaseWeight.begin(), tolower);

            if (lowercaseWeight == "regular")
            {
                return 400;
            }
            if (lowercaseWeight == "bold")
            {
                return 700;
            }
            else
            {
                return 400;
            }
        }

        std::bitset<128> CalculateUsedUnicodeRanges(const OtfCmapTable& cmap)
        {
            std::bitset<128> result;

            OtfUnicodeRanges unicodeRanges;

            for (const auto& pair : cmap.GetCmap())
            {
                auto rangeId = unicodeRanges.GetRangeId(pair.second);

                if (rangeId != OtfUnicodeRanges::UNKNOWN_RANGE)
                {
                    result[rangeId] = true;
                }
            }

            return result;
        }
    };
} } }
