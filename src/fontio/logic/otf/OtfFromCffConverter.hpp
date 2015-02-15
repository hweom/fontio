#pragma once

#include <fontio/model/cff/Cff.hpp>
#include <fontio/model/otf/Otf.hpp>

namespace fontio { namespace logic { namespace otf
{
    using namespace fontio::model::cff;
    using namespace fontio::model::otf;

    class OtfFromCffConverter
    {
    public:

        std::unique_ptr<Otf> ConvertFromCff(const Cff& cff, size_t fontIndex = 0)
        {
            auto headTable = this->ConvertHeadTable(cff);
        }

    private:

        std::unique_ptr<OtfCmapTable> ConvertCmapTable(const CffTopDict& topDict)
        {
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

        uint16_t GetHeadFlags(const CffTopDict& topDict)
        {
            return 0;
        }
    };
} } }
