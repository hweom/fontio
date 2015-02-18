#pragma once

#include <ostream>
#include <functional>

namespace fontio { namespace model { namespace cff
{
    enum class CffOperatorType
    {
        Version = 0x0000,
        Notice = 0x0001,
        FullName = 0x0002,
        FamilyName = 0x0003,
        Weight = 0x0004,
        FontBBox = 0x0005,

        IsFixedPitch = 0x0c01,
        ItalicAngle = 0x0c02,
        UnderlinePosition = 0x0c03,
        UnderlineThickness = 0x0c04,
        PaintType = 0x0c05,
        CharstringType = 0x0c06,
        FontMatrix = 0x0c07,
        StrokeWidth = 0x0c08,
        SyntheticBase = 0x0c14,
        PostScript = 0x0c15,
        BaseFontName = 0x0c16,
        BaseFontBlend = 0x0c17,

        Ros = 0x0c1e,
        CidFontVersion = 0x0c1f,
        CidFontRevision = 0x0c20,
        CidFontType = 0x0c21,
        CidCount = 0x0c22,
        UidBase = 0x0c23,
        FdArray = 0x0c24,
        FdSelect = 0x0c25,
        FontName = 0x0c26,

        UniqueID = 0x000d,
        XUid = 0x000e,
        Charset = 0x000f,
        Encoding = 0x0010,
        CharStrings = 0x0011,
        Private = 0x0012,

        BlueValues = 0x0006,
        OtherBlues  = 0x0007,
        FamilyBlues  = 0x0008,
        FamilyOtherBlues  = 0x0009,
        BlueScale = 0x0c09,
        BlueShift = 0x0c0a,
        BlueFuzz = 0x0c0b,
        StdHW = 0x000a,
        StdVW = 0x000b,
        StemSnapH = 0x0c0c,
        StemSnapV = 0x0c0d,
        ForceBold = 0x0c0e,
        LanguageGroup = 0x0c11,
        ExpansionFactor = 0x0c12,
        InitialRandomSeed = 0x0c13,
        Subrs = 0x00013,
        DefaultWidthX = 0x0014,
        NominalWidthX = 0x0015
    };

    std::ostream& operator << (std::ostream& out, CffOperatorType type)
    {

        switch (type)
        {
        case CffOperatorType::Version:
            return out << "Version";
        case CffOperatorType::Notice:
            return out << "Notice";
        case CffOperatorType::FullName:
            return out << "FullName";
        case CffOperatorType::FamilyName:
            return out << "FamilyName";
        case CffOperatorType::Weight:
            return out << "Weight";
        case CffOperatorType::FontBBox:
            return out << "FontBBox";
        case CffOperatorType::IsFixedPitch:
            return out << "IsFixedPitch";
        case CffOperatorType::ItalicAngle:
            return out << "ItalicAngle";
        case CffOperatorType::UnderlinePosition:
            return out << "UnderlinePosition";
        case CffOperatorType::UnderlineThickness:
            return out << "UnderlineThickness";
        case CffOperatorType::PaintType:
            return out << "PaintType";
        case CffOperatorType::CharstringType:
            return out << "CharstringType";
        case CffOperatorType::FontMatrix:
            return out << "FontMatrix";
        case CffOperatorType::StrokeWidth:
            return out << "StrokeWidth";
        case CffOperatorType::SyntheticBase:
            return out << "SyntheticBase";
        case CffOperatorType::PostScript:
            return out << "PostScript";
        case CffOperatorType::BaseFontName:
            return out << "BaseFontName";
        case CffOperatorType::BaseFontBlend:
            return out << "BaseFontBlend";
        case CffOperatorType::Ros:
            return out << "Ros";
        case CffOperatorType::CidFontVersion:
            return out << "CidFontVersion";
        case CffOperatorType::CidFontRevision:
            return out << "CidFontRevision";
        case CffOperatorType::CidFontType:
            return out << "CidFontType";
        case CffOperatorType::CidCount:
            return out << "CidCount";
        case CffOperatorType::UidBase:
            return out << "UidBase";
        case CffOperatorType::FdArray:
            return out << "FdArray";
        case CffOperatorType::FdSelect:
            return out << "FdSelect";
        case CffOperatorType::FontName:
            return out << "FontName";
        case CffOperatorType::UniqueID:
            return out << "UniqueID";
        case CffOperatorType::XUid:
            return out << "XUid";
        case CffOperatorType::Charset:
            return out << "Charset";
        case CffOperatorType::Encoding:
            return out << "Encoding";
        case CffOperatorType::CharStrings:
            return out << "CharStrings";
        case CffOperatorType::Private:
            return out << "Private";
        default:
            return out << "<???>";
        }
    }
} } }

namespace std
{
    template<>
    struct hash<fontio::model::cff::CffOperatorType>
    {
        size_t operator () (fontio::model::cff::CffOperatorType type) const
        {
            return (size_t)type;
        }
    };
}
