#pragma once

#include <cinttypes>
#include <cstring>
#include <bitset>

#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    class OtfOs2Table : public IOtfTable
    {
    public:

        struct Panose
        {
            uint8_t bFamilyType = 2;
            uint8_t bSerifStyle = 0;
            uint8_t bWeight = 5;
            uint8_t bProportion = 3;
            uint8_t bContrast = 0;
            uint8_t bStrokeVariation = 0;
            uint8_t bArmStyle = 0;
            uint8_t bLetterform = 0;
            uint8_t bMidline = 0;
            uint8_t bXHeight = 0;
        };

    private:

        int16_t xAvgcharWidth;
        uint16_t usWeightClass;
        uint16_t usWidthClass;
        uint16_t fsType;
        int16_t ySubscriptXSize;
        int16_t ySubscriptYSize;
        int16_t ySubscriptXOffset;
        int16_t ySubscriptYOffset;
        int16_t ySuperscriptXSize;
        int16_t ySuperscriptYSize;
        int16_t ySuperscriptXOffset;
        int16_t ySuperscriptYOffset;
        int16_t yStrikeoutSize;
        int16_t yStrikeoutPosition;
        int16_t sFamilyClass;
        Panose panose;
        std::bitset<128> unicodeRanges;
        char achVendID[4];
        uint16_t fsSelection;
        uint16_t usFirstcharIndex;
        uint16_t usLastcharIndex;
        int16_t sTypoAscender;
        int16_t sTypoDescender;
        int16_t sTypoLineGap;
        uint16_t usWinAscent;
        uint16_t usWinDescent;
        uint64_t ulCodePageRange;
        int16_t sxHeight;
        int16_t sCapHeight;
        uint16_t usDefaultchar;
        uint16_t usBreakchar;
        uint16_t usMaxContext;

    public:

        OtfOs2Table(
            int16_t xAvgcharWidth,
            uint16_t usWeightClass,
            uint16_t usWidthClass,
            uint16_t fsType,
            int16_t ySubscriptXSize,
            int16_t ySubscriptYSize,
            int16_t ySubscriptXOffset,
            int16_t ySubscriptYOffset,
            int16_t ySuperscriptXSize,
            int16_t ySuperscriptYSize,
            int16_t ySuperscriptXOffset,
            int16_t ySuperscriptYOffset,
            int16_t yStrikeoutSize,
            int16_t yStrikeoutPosition,
            int16_t sFamilyClass,
            const Panose& panose,
            std::bitset<128> unicodeRanges,
            const char achVendID[4],
            uint16_t fsSelection,
            uint16_t usFirstcharIndex,
            uint16_t usLastcharIndex,
            int16_t sTypoAscender,
            int16_t sTypoDescender,
            int16_t sTypoLineGap,
            uint16_t usWinAscent,
            uint16_t usWinDescent,
            uint64_t ulCodePageRange,
            int16_t sxHeight,
            int16_t sCapHeight,
            uint16_t usDefaultchar,
            uint16_t usBreakchar,
            uint16_t usMaxContext)
            : xAvgcharWidth(xAvgcharWidth)
            , usWeightClass(usWeightClass)
            , usWidthClass(usWidthClass)
            , fsType(fsType)
            , ySubscriptXSize(ySubscriptXSize)
            , ySubscriptYSize(ySubscriptYSize)
            , ySubscriptXOffset(ySubscriptXOffset)
            , ySubscriptYOffset(ySubscriptYOffset)
            , ySuperscriptXSize(ySuperscriptXSize)
            , ySuperscriptYSize(ySuperscriptYSize)
            , ySuperscriptXOffset(ySuperscriptXOffset)
            , ySuperscriptYOffset(ySuperscriptYOffset)
            , yStrikeoutSize(yStrikeoutSize)
            , yStrikeoutPosition(yStrikeoutPosition)
            , sFamilyClass(sFamilyClass)
            , panose(panose)
            , unicodeRanges(unicodeRanges)
            , fsSelection(fsSelection)
            , usFirstcharIndex(usFirstcharIndex)
            , usLastcharIndex(usLastcharIndex)
            , sTypoAscender(sTypoAscender)
            , sTypoDescender(sTypoDescender)
            , sTypoLineGap(sTypoLineGap)
            , usWinAscent(usWinAscent)
            , usWinDescent(usWinDescent)
            , ulCodePageRange(ulCodePageRange)
            , sxHeight(sxHeight)
            , sCapHeight(sCapHeight)
            , usDefaultchar(usDefaultchar)
            , usBreakchar(usBreakchar)
            , usMaxContext(usMaxContext)
        {
            memcpy(this->achVendID, achVendID, 4);
        }

    public:

        virtual OtfTableType GetType() const override
        {
            return OtfTableType::Os2;
        }
    };
} } }
