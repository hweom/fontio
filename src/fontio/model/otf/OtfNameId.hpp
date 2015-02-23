#pragma once

namespace fontio { namespace model { namespace otf
{
    enum class OtfNameId
    {
        Copyright = 0,
        FontFamily = 1,
        FontSubfamily = 2,
        UniqueFontId = 3,
        FullFontName = 4,
        VersionString = 5,
        PostscriptName = 6,
        Trademark = 7,
        Manufacturer = 8,
        Designer = 9,
        Description = 10,
        UrlVendor = 11,
        UrlDesigner = 12,
        LicenseDescription = 13,
        LicenseInfoUrl = 14,
        PreferredFamily = 16,
        PreferredSubfamily = 17,
        CompatibleFull = 18,
        SampleText = 19,
        PostscriptCidFindfont = 20,
        WwsFamily = 21,
        WwsSubfamily = 22
    };
} } }
