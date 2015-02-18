#pragma once

#include <fontio/logic/type2/Type2GlyphMetricsCalculator.hpp>
#include <fontio/model/AdobeGlyphList.hpp>
#include <fontio/model/cff/Cff.hpp>
#include <fontio/model/cff/CffType2Charstrings.hpp>
#include <fontio/model/otf/Otf.hpp>

namespace fontio { namespace logic { namespace otf
{
    using namespace fontio::logic::type2;
    using namespace fontio::model;
    using namespace fontio::model::cff;
    using namespace fontio::model::otf;

    class OtfFromCffConverter
    {
    public:

        static const int16_t DEFAULT_LINE_GAP = 90;

    public:

        std::unique_ptr<Otf> ConvertFromCff(const Cff& cff, size_t fontIndex = 0)
        {
            const auto& topDict = cff.GetTopDicts()[fontIndex];

            auto glyphMetrics =this->CalculateGlyphMetrics(topDict);

            auto cmapTable = this->ConvertCmapTable(cff, topDict);
            auto headTable = this->ConvertHeadTable(topDict);
            auto hmtxTable = this->ConvertHmtxTable(glyphMetrics);
            auto hheaTable = this->ConvertHheaTable(topDict, glyphMetrics);
        }

    private:

        std::unique_ptr<OtfCmapTable> ConvertCmapTable(const Cff& cff, const CffTopDict& topDict)
        {
            if (topDict.GetCharsetType() == CffCharsetType::Custom)
            {
                AdobeGlyphList glyphList;
                const auto& strings = cff.GetStringIndex();

                std::vector<std::pair<uint16_t, uint16_t>> cmap;
                for (const auto& pair : topDict.GetCharset().GetGidToSidMap())
                {
                    auto charName = strings.GetString(pair.second);
                    auto unicode = glyphList.GetUnicode(charName);

                    cmap.push_back(std::make_pair(pair.first, unicode));
                }

                return std::unique_ptr<OtfCmapTable>(new OtfCmapTable(cmap));
            }
            else
            {
                throw std::logic_error("Not implemented");
            }
        }

        std::unique_ptr<OtfHeadTable> ConvertHeadTable(const CffTopDict& topDict)
        {
            auto fontsPerEm = (uint16_t)(1.0 / topDict.GetFontMatrix().GetScale());
            auto currentDate = 0;
            auto bbox = topDict.GetBoundBox();

            return std::unique_ptr<OtfHeadTable>(new OtfHeadTable(
                1,
                0,
                1,
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
            return std::unique_ptr<OtfHmtxTable>(glyphMetrics);
        }

        std::unique_ptr<OtfHheaTable> ConvertHheaTable(const CffTopDict& topDict, const std::vector<GlyphMetrics>& glyphMetrics)
        {
            uint16_t advanceWidthMax = 0;
            int16_t	minLeftSideBearing = 0;
            int16_t minRightSideBearing = 0;
            int16_t maxExtent = 0;

            for (const auto& metrics : glyphMetrics)
            {
                auto rightSideBearing = static_cast<int16_t>(metrics.GetAdvanceWidth() - metrics.GetLeftSideBearings() - metrics.GetBoundBox().GetWidth());
                auto extent = static_cast<int16_t>(metrics.GetLeftSideBearings() + metrics.GetBoundBox().GetWidth());

                advanceWidthMax = std::max(advanceWidthMax, metrics.GetAdvanceWidth());
                minLeftSideBearing = std::min(minLeftSideBearing, metrics.GetLeftSideBearings());
                minRightSideBearing = std::min(minRightSideBearing, rightSideBearing);
                maxExtent = std::max(maxExtent, extent);
            }

            return std::unique_ptr<OtfHheaTable>(new OtfHheaTable(
                DEFAULT_LINE_GAP,
                advanceWidthMax,
                minLeftSideBearing,
                minRightSideBearing,
                maxExtent,
                1,
                0,
                0,
                glyphMetrics.size()));
            ));
        }

        std::vector<GlyphMetrics> CalculateGlyphMetrics(const Cff& cff, const CffTopDict& topDict)
        {
            if (topDict.GetCharstringFormat() == CffCharstringFormat::Type2)
            {
                auto localSubroutines = topDict.HasLocalSubroutines()
                    ? Type2SubroutineAccessor(static_cast<const CffType2Charstrings&>(topDict.GetLocalSubroutines()).GetCharstrings())
                    : Type2SubroutineAccessor();

                auto globalSubroutines = cff.HasGlobalSubroutines()
                    ? Type2SubroutineAccessor(static_cast<const CffType2Charstrings&>(cff.GetGlobalSubroutines()).GetCharstrings())
                    : Type2SubroutineAccessor();

                return this->CalculateType2GlyphMetrics(
                    static_cast<const CffType2Charstrings&>(*topDict.GetCharstrings()).GetCharstrings(),
                    localSubroutines,
                    globalSubroutines);
            }
            else
            {
                throw std::logic_error("Not implemented");
            }
        }

        std::vector<GlyphMetrics> CalculateType2GlyphMetrics(
            const std::vector<Type2Charstring>& charstrings,
            Type2SubroutineAccessor localSubroutines,
            Type2SubroutineAccessor globalSubroutines)
        {
            std::vector<GlyphMetrics> result;

            Type2GlyphMetricsCalculator calculator;

            for (const auto& charstring : charstrings)
            {
                assert (charstring->GetFormat() == CffCharstringFormat::Type2);

                auto metrics = calculator.CalculateMetrics(charstrings, localSubroutines, globalSubroutines);

                result.push_back(metrics);
            }

            return result;
        }

        uint16_t GetHeadFlags(const CffTopDict& topDict)
        {
            return 0;
        }
    };
} } }
