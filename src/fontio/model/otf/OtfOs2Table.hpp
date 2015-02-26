#pragma once

#include <cinttypes>
#include <cstring>
#include <bitset>
#include <stdexcept>

#include <fontio/infrastructure/ByteIo.hpp>
#include <fontio/model/otf/IOtfTable.hpp>

namespace fontio { namespace model { namespace otf
{
    using namespace fontio::infrastructure;

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

        virtual void Save(std::ostream& out, OtfTableCrc& crc) const override
        {
            WriteBytes<BigEndian>(out, static_cast<uint16_t>(4), crc);          // Version.

            WriteBytes<BigEndian>(out, this->xAvgcharWidth, crc);
            WriteBytes<BigEndian>(out, this->usWeightClass, crc);
            WriteBytes<BigEndian>(out, this->usWidthClass, crc);
            WriteBytes<BigEndian>(out, this->fsType, crc);
            WriteBytes<BigEndian>(out, this->ySubscriptXSize, crc);
            WriteBytes<BigEndian>(out, this->ySubscriptYSize, crc);
            WriteBytes<BigEndian>(out, this->ySubscriptXOffset, crc);
            WriteBytes<BigEndian>(out, this->ySubscriptYOffset, crc);
            WriteBytes<BigEndian>(out, this->ySuperscriptXSize, crc);
            WriteBytes<BigEndian>(out, this->ySuperscriptYSize, crc);
            WriteBytes<BigEndian>(out, this->ySuperscriptXOffset, crc);
            WriteBytes<BigEndian>(out, this->ySuperscriptYOffset, crc);
            WriteBytes<BigEndian>(out, this->yStrikeoutSize, crc);
            WriteBytes<BigEndian>(out, this->yStrikeoutPosition, crc);
            WriteBytes<BigEndian>(out, this->sFamilyClass, crc);

            WriteBytes<BigEndian>(out, this->panose.bFamilyType, crc);
            WriteBytes<BigEndian>(out, this->panose.bSerifStyle, crc);
            WriteBytes<BigEndian>(out, this->panose.bWeight, crc);
            WriteBytes<BigEndian>(out, this->panose.bProportion, crc);
            WriteBytes<BigEndian>(out, this->panose.bContrast, crc);
            WriteBytes<BigEndian>(out, this->panose.bStrokeVariation, crc);
            WriteBytes<BigEndian>(out, this->panose.bArmStyle, crc);
            WriteBytes<BigEndian>(out, this->panose.bLetterform, crc);
            WriteBytes<BigEndian>(out, this->panose.bMidline, crc);
            WriteBytes<BigEndian>(out, this->panose.bXHeight, crc);

            this->SaveBitset(out, this->unicodeRanges, crc);

            WriteBytes<BigEndian>(out, *reinterpret_cast<const uint32_t*>(&this->achVendID), crc);
            WriteBytes<BigEndian>(out, this->fsSelection, crc);
            WriteBytes<BigEndian>(out, this->usFirstcharIndex, crc);
            WriteBytes<BigEndian>(out, this->usLastcharIndex, crc);
            WriteBytes<BigEndian>(out, this->sTypoAscender, crc);
            WriteBytes<BigEndian>(out, this->sTypoDescender, crc);
            WriteBytes<BigEndian>(out, this->sTypoLineGap, crc);
            WriteBytes<BigEndian>(out, this->usWinAscent, crc);
            WriteBytes<BigEndian>(out, this->usWinDescent, crc);
            WriteBytes<BigEndian>(out, this->ulCodePageRange, crc);
            WriteBytes<BigEndian>(out, this->sxHeight, crc);
            WriteBytes<BigEndian>(out, this->sCapHeight, crc);
            WriteBytes<BigEndian>(out, this->usDefaultchar, crc);
            WriteBytes<BigEndian>(out, this->usBreakchar, crc);
            WriteBytes<BigEndian>(out, this->usMaxContext, crc);
        }

        virtual uint32_t GetId() const override
        {
            return 0x4f532f32; // OS/2
        }

    private:

        template<size_t N>
        void SaveBitset(std::ostream& out, const std::bitset<N>& bits, OtfTableCrc& crc) const
        {
            assert ((N % 8) == 0);

            uint8_t byte = 0;
            size_t bitsInByte = 0;
            for (int i = N - 1; i >= 0; i--)
            {
                byte = (byte << 1) | (bits[static_cast<size_t>(i)] ? 1 : 0);

                if (++bitsInByte == 8)
                {
                    WriteBytes<BigEndian>(out, byte, crc);
                    byte = 0;
                    bitsInByte = 0;
                }
            }
        }
    };
} } }
