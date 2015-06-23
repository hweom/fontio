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

#include <fontio/model/AdobeStandardEncoding.hpp>

namespace fontio { namespace model
{
    std::unordered_map<std::string, uint16_t> AdobeStandardEncoding::glyphs =
    {
        { "A", 0101 },
        { "AE", 0341 },
        { "B", 0102 },
        { "C", 0103 },
        { "D", 0104 },
        { "E", 0105 },
        { "F", 0106 },
        { "G", 0107 },
        { "H", 0110 },
        { "I", 0111 },
        { "J", 0112 },
        { "K", 0113 },
        { "L", 0114 },
        { "Lslash", 0350 },
        { "M", 0115 },
        { "N", 0116 },
        { "O", 0117 },
        { "OE", 0352 },
        { "Oslash", 0351 },
        { "P", 0120 },
        { "Q", 0121 },
        { "R", 0122 },
        { "S", 0123 },
        { "T", 0124 },
        { "U", 0125 },
        { "V", 0126 },
        { "W", 0127 },
        { "X", 0130 },
        { "Y", 0131 },
        { "Z", 0132 },
        { "a", 0141 },
        { "acute", 0302 },
        { "ae", 0361 },
        { "ampersand", 046 },
        { "asciicircum", 0136 },
        { "asciitilde", 0176 },
        { "asterisk", 052 },
        { "at", 0100 },
        { "b", 0142 },
        { "backslash", 0134 },
        { "bar", 0174 },
        { "braceleft", 0173 },
        { "braceright", 0175 },
        { "bracketleft", 0133 },
        { "bracketright", 0135 },
        { "breve", 0306 },
        { "bullet", 0267 },
        { "c", 0143 },
        { "caron", 0317 },
        { "cedilla", 0313 },
        { "cent", 0242 },
        { "circumflex", 0303 },
        { "colon", 072 },
        { "comma", 054 },
        { "currency", 0250 },
        { "d", 0144 },
        { "dagger", 0262 },
        { "daggerdbl", 0263 },
        { "dieresis", 0310 },
        { "dollar", 044 },
        { "dotaccent", 0307 },
        { "dotlessi", 0365 },
        { "e", 0145 },
        { "eight", 070 },
        { "ellipsis", 0274 },
        { "emdash", 0320 },
        { "endash", 0261 },
        { "equal", 075 },
        { "exclam", 041 },
        { "exclamdown", 0241 },
        { "f", 0146 },
        { "fi", 0256 },
        { "five", 065 },
        { "fl", 0257 },
        { "florin", 0246 },
        { "four", 064 },
        { "fraction", 0244 },
        { "g", 0147 },
        { "germandbls", 0373 },
        { "grave", 0301 },
        { "greater", 076 },
        { "guillemotleft", 0253 },
        { "guillemotright", 0273 },
        { "guilsinglleft", 0254 },
        { "guilsinglright", 0255 },
        { "h", 0150 },
        { "hungarumlaut", 0315 },
        { "hyphen", 055 },
        { "i", 0151 },
        { "j", 0152 },
        { "k", 0153 },
        { "l", 0154 },
        { "less", 074 },
        { "lslash", 0370 },
        { "m", 0155 },
        { "macron", 0305 },
        { "n", 0156 },
        { "nine", 071 },
        { "numbersign", 043 },
        { "o", 0157 },
        { "oe", 0372 },
        { "ogonek", 0316 },
        { "one", 061 },
        { "ordfeminine", 0343 },
        { "ordmasculine", 0353 },
        { "oslash", 0371 },
        { "p", 0160 },
        { "paragraph", 0266 },
        { "parenleft", 050 },
        { "parenright", 051 },
        { "percent", 045 },
        { "period", 056 },
        { "periodcentered", 0264 },
        { "perthousand", 0275 },
        { "plus", 053 },
        { "q", 0161 },
        { "question", 077 },
        { "questiondown", 0277 },
        { "quotedbl", 042 },
        { "quotedblbase", 0271 },
        { "quotedblleft", 0252 },
        { "quotedblright", 0272 },
        { "quoteleft", 0140 },
        { "quoteright", 047 },
        { "quotesinglbase", 0270 },
        { "quotesingle", 0251 },
        { "r", 0162 },
        { "ring", 0312 },
        { "s", 0163 },
        { "section", 0247 },
        { "semicolon", 073 },
        { "seven", 067 },
        { "six", 066 },
        { "slash", 057 },
        { "space", 040 },
        { "sterling", 0243 },
        { "t", 0164 },
        { "three", 063 },
        { "tilde", 0304 },
        { "two", 062 },
        { "u", 0165 },
        { "underscore", 0137 },
        { "v", 0166 },
        { "w", 0167 },
        { "x", 0170 },
        { "y", 0171 },
        { "yen", 0245 },
        { "z", 0172 },
        { "zero", 060 }
    };
} }
