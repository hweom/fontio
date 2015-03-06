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

#include <fontio/model/AdobeGlyphList.hpp>
#include <fontio/model/cff/ICffCharset.hpp>
#include <fontio/model/cff/CffStandardStrings.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffIsoAdobeCharset : public ICffCharset
    {
    public:

        virtual const std::unordered_map<uint16_t, uint16_t>& GetGidToSidMap() const override
        {
            return GetMap();
        }

    private:

        static const std::unordered_map<uint16_t, uint16_t>& GetMap()
        {
            static std::unordered_map<uint16_t, uint16_t> map = CreateMap();

            return map;
        }

        static std::unordered_map<uint16_t, uint16_t> CreateMap()
        {
            std::unordered_map<uint16_t, uint16_t> map =
            {
                {1, SidFromName("space")},
                {2, SidFromName("exclam")},
                {3, SidFromName("quotedbl")},
                {4, SidFromName("numbersign")},
                {5, SidFromName("dollar")},
                {6, SidFromName("percent")},
                {7, SidFromName("ampersand")},
                {8, SidFromName("quoteright")},
                {9, SidFromName("parenleft")},
                {10, SidFromName("parenright")},
                {11, SidFromName("asterisk")},
                {12, SidFromName("plus")},
                {13, SidFromName("comma")},
                {14, SidFromName("hyphen")},
                {15, SidFromName("period")},
                {16, SidFromName("slash")},
                {17, SidFromName("zero")},
                {18, SidFromName("one")},
                {19, SidFromName("two")},
                {20, SidFromName("three")},
                {21, SidFromName("four")},
                {22, SidFromName("five")},
                {23, SidFromName("six")},
                {24, SidFromName("seven")},
                {25, SidFromName("eight")},
                {26, SidFromName("nine")},
                {27, SidFromName("colon")},
                {28, SidFromName("semicolon")},
                {29, SidFromName("less")},
                {30, SidFromName("equal")},
                {31, SidFromName("greater")},
                {32, SidFromName("question")},
                {33, SidFromName("at")},
                {34, SidFromName("A")},
                {35, SidFromName("B")},
                {36, SidFromName("C")},
                {37, SidFromName("D")},
                {38, SidFromName("E")},
                {39, SidFromName("F")},
                {40, SidFromName("G")},
                {41, SidFromName("H")},
                {42, SidFromName("I")},
                {43, SidFromName("J")},
                {44, SidFromName("K")},
                {45, SidFromName("L")},
                {46, SidFromName("M")},
                {47, SidFromName("N")},
                {48, SidFromName("O")},
                {49, SidFromName("P")},
                {50, SidFromName("Q")},
                {51, SidFromName("R")},
                {52, SidFromName("S")},
                {53, SidFromName("T")},
                {54, SidFromName("U")},
                {55, SidFromName("V")},
                {56, SidFromName("W")},
                {57, SidFromName("X")},
                {58, SidFromName("Y")},
                {59, SidFromName("Z")},
                {60, SidFromName("bracketleft")},
                {61, SidFromName("backslash")},
                {62, SidFromName("bracketright")},
                {63, SidFromName("asciicircum")},
                {64, SidFromName("underscore")},
                {65, SidFromName("quoteleft")},
                {66, SidFromName("a")},
                {67, SidFromName("b")},
                {68, SidFromName("c")},
                {69, SidFromName("d")},
                {70, SidFromName("e")},
                {71, SidFromName("f")},
                {72, SidFromName("g")},
                {73, SidFromName("h")},
                {74, SidFromName("i")},
                {75, SidFromName("j")},
                {76, SidFromName("k")},
                {77, SidFromName("l")},
                {78, SidFromName("m")},
                {79, SidFromName("n")},
                {80, SidFromName("o")},
                {81, SidFromName("p")},
                {82, SidFromName("q")},
                {83, SidFromName("r")},
                {84, SidFromName("s")},
                {85, SidFromName("t")},
                {86, SidFromName("u")},
                {87, SidFromName("v")},
                {88, SidFromName("w")},
                {89, SidFromName("x")},
                {90, SidFromName("y")},
                {91, SidFromName("z")},
                {92, SidFromName("braceleft")},
                {93, SidFromName("bar")},
                {94, SidFromName("braceright")},
                {95, SidFromName("asciitilde")},
                {96, SidFromName("exclamdown")},
                {97, SidFromName("cent")},
                {98, SidFromName("sterling")},
                {99, SidFromName("fraction")},
                {100, SidFromName("yen")},
                {101, SidFromName("florin")},
                {102, SidFromName("section")},
                {103, SidFromName("currency")},
                {104, SidFromName("quotesingle")},
                {105, SidFromName("quotedblleft")},
                {106, SidFromName("guillemotleft")},
                {107, SidFromName("guilsinglleft")},
                {108, SidFromName("guilsinglright")},
                {109, SidFromName("fi")},
                {110, SidFromName("fl")},
                {111, SidFromName("endash")},
                {112, SidFromName("dagger")},
                {113, SidFromName("daggerdbl")},
                {114, SidFromName("periodcentered")},
                {115, SidFromName("paragraph")},
                {116, SidFromName("bullet")},
                {117, SidFromName("quotesinglbase")},
                {118, SidFromName("quotedblbase")},
                {119, SidFromName("quotedblright")},
                {120, SidFromName("guillemotright")},
                {121, SidFromName("ellipsis")},
                {122, SidFromName("perthousand")},
                {123, SidFromName("questiondown")},
                {124, SidFromName("grave")},
                {125, SidFromName("acute")},
                {126, SidFromName("circumflex")},
                {127, SidFromName("tilde")},
                {128, SidFromName("macron")},
                {129, SidFromName("breve")},
                {130, SidFromName("dotaccent")},
                {131, SidFromName("dieresis")},
                {132, SidFromName("ring")},
                {133, SidFromName("cedilla")},
                {134, SidFromName("hungarumlaut")},
                {135, SidFromName("ogonek")},
                {136, SidFromName("caron")},
                {137, SidFromName("emdash")},
                {138, SidFromName("AE")},
                {139, SidFromName("ordfeminine")},
                {140, SidFromName("Lslash")},
                {141, SidFromName("Oslash")},
                {142, SidFromName("OE")},
                {143, SidFromName("ordmasculine")},
                {144, SidFromName("ae")},
                {145, SidFromName("dotlessi")},
                {146, SidFromName("lslash")},
                {147, SidFromName("oslash")},
                {148, SidFromName("oe")},
                {149, SidFromName("germandbls")},
                {150, SidFromName("onesuperior")},
                {151, SidFromName("logicalnot")},
                {152, SidFromName("mu")},
                {153, SidFromName("trademark")},
                {154, SidFromName("Eth")},
                {155, SidFromName("onehalf")},
                {156, SidFromName("plusminus")},
                {157, SidFromName("Thorn")},
                {158, SidFromName("onequarter")},
                {159, SidFromName("divide")},
                {160, SidFromName("brokenbar")},
                {161, SidFromName("degree")},
                {162, SidFromName("thorn")},
                {163, SidFromName("threequarters")},
                {164, SidFromName("twosuperior")},
                {165, SidFromName("registered")},
                {166, SidFromName("minus")},
                {167, SidFromName("eth")},
                {168, SidFromName("multiply")},
                {169, SidFromName("threesuperior")},
                {170, SidFromName("copyright")},
                {171, SidFromName("Aacute")},
                {172, SidFromName("Acircumflex")},
                {173, SidFromName("Adieresis")},
                {174, SidFromName("Agrave")},
                {175, SidFromName("Aring")},
                {176, SidFromName("Atilde")},
                {177, SidFromName("Ccedilla")},
                {178, SidFromName("Eacute")},
                {179, SidFromName("Ecircumflex")},
                {180, SidFromName("Edieresis")},
                {181, SidFromName("Egrave")},
                {182, SidFromName("Iacute")},
                {183, SidFromName("Icircumflex")},
                {184, SidFromName("Idieresis")},
                {185, SidFromName("Igrave")},
                {186, SidFromName("Ntilde")},
                {187, SidFromName("Oacute")},
                {188, SidFromName("Ocircumflex")},
                {189, SidFromName("Odieresis")},
                {190, SidFromName("Ograve")},
                {191, SidFromName("Otilde")},
                {192, SidFromName("Scaron")},
                {193, SidFromName("Uacute")},
                {194, SidFromName("Ucircumflex")},
                {195, SidFromName("Udieresis")},
                {196, SidFromName("Ugrave")},
                {197, SidFromName("Yacute")},
                {198, SidFromName("Ydieresis")},
                {199, SidFromName("Zcaron")},
                {200, SidFromName("aacute")},
                {201, SidFromName("acircumflex")},
                {202, SidFromName("adieresis")},
                {203, SidFromName("agrave")},
                {204, SidFromName("aring")},
                {205, SidFromName("atilde")},
                {206, SidFromName("ccedilla")},
                {207, SidFromName("eacute")},
                {208, SidFromName("ecircumflex")},
                {209, SidFromName("edieresis")},
                {210, SidFromName("egrave")},
                {211, SidFromName("iacute")},
                {212, SidFromName("icircumflex")},
                {213, SidFromName("idieresis")},
                {214, SidFromName("igrave")},
                {215, SidFromName("ntilde")},
                {216, SidFromName("oacute")},
                {217, SidFromName("ocircumflex")},
                {218, SidFromName("odieresis")},
                {219, SidFromName("ograve")},
                {220, SidFromName("otilde")},
                {221, SidFromName("scaron")},
                {222, SidFromName("uacute")},
                {223, SidFromName("ucircumflex")},
                {224, SidFromName("udieresis")},
                {225, SidFromName("ugrave")},
                {226, SidFromName("yacute")},
                {227, SidFromName("ydieresis")},
                {228, SidFromName("zcaron")}
            };

            return map;
        }

        static uint16_t SidFromName(const std::string& name)
        {
            const auto& standardStrings = CffStandardStrings::Get();

            for (size_t i = 0; i < standardStrings.size(); i++)
            {
                if (standardStrings[i] == name)
                {
                    return static_cast<uint16_t>(i);
                }
            }

            return 0;
        }

    };
} } }
