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

#include <fontio/model/PdfDocEncoding.hpp>

namespace fontio { namespace model
{
    std::unordered_map<std::string, uint16_t> PdfDocEncoding::glyphs =
    {
        { "A", 0101 },
        { "AE", 0306 },
        { "Aacute", 0301 },
        { "Acircumflex", 0302 },
        { "Adieresis", 0304 },
        { "Agrave", 0300 },
        { "Aring", 0305 },
        { "Atilde", 0303 },
        { "B", 0102 },
        { "C", 0103 },
        { "Ccedilla", 0307 },
        { "D", 0104 },
        { "E", 0105 },
        { "Eacute", 0311 },
        { "Ecircumflex", 0312 },
        { "Edieresis", 0313 },
        { "Egrave", 0310 },
        { "Eth", 0320 },
        { "Euro", 0240 },
        { "F", 0106 },
        { "G", 0107 },
        { "H", 0110 },
        { "I", 0111 },
        { "Iacute", 0315 },
        { "Icircumflex", 0316 },
        { "Idieresis", 0317 },
        { "Igrave", 0314 },
        { "J", 0112 },
        { "K", 0113 },
        { "L", 0114 },
        { "Lslash", 0225 },
        { "M", 0115 },
        { "N", 0116 },
        { "Ntilde", 0321 },
        { "O", 0117 },
        { "OE", 0226 },
        { "Oacute", 0323 },
        { "Ocircumflex", 0324 },
        { "Odieresis", 0326 },
        { "Ograve", 0322 },
        { "Oslash", 0330 },
        { "Otilde", 0325 },
        { "P", 0120 },
        { "Q", 0121 },
        { "R", 0122 },
        { "S", 0123 },
        { "Scaron", 0227 },
        { "T", 0124 },
        { "Thorn", 0336 },
        { "U", 0125 },
        { "Uacute", 0332 },
        { "Ucircumflex", 0333 },
        { "Udieresis", 0334 },
        { "Ugrave", 0331 },
        { "V", 0126 },
        { "W", 0127 },
        { "X", 0130 },
        { "Y", 0131 },
        { "Yacute", 0335 },
        { "Ydieresis", 0230 },
        { "Z", 0132 },
        { "Zcaron", 0231 },
        { "a", 0141 },
        { "aacute", 0341 },
        { "acircumflex", 0342 },
        { "acute", 0264 },
        { "adieresis", 0344 },
        { "ae", 0346 },
        { "agrave", 0340 },
        { "ampersand", 046 },
        { "aring", 0345 },
        { "asciicircum", 0136 },
        { "asciitilde", 0176 },
        { "asterisk", 052 },
        { "at", 0100 },
        { "atilde", 0343 },
        { "b", 0142 },
        { "backslash", 0134 },
        { "bar", 0174 },
        { "braceleft", 0173 },
        { "braceright", 0175 },
        { "bracketleft", 0133 },
        { "bracketright", 0135 },
        { "breve", 030 },
        { "brokenbar", 0246 },
        { "bullet", 0200 },
        { "c", 0143 },
        { "caron", 031 },
        { "ccedilla", 0347 },
        { "cedilla", 0270 },
        { "cent", 0242 },
        { "circumflex", 032 },
        { "colon", 072 },
        { "comma", 054 },
        { "copyright", 0251 },
        { "currency", 0244 },
        { "d", 0144 },
        { "dagger", 0201 },
        { "daggerdbl", 0202 },
        { "degree", 0260 },
        { "dieresis", 0250 },
        { "divide", 0367 },
        { "dollar", 044 },
        { "dotaccent", 033 },
        { "dotlessi", 0232 },
        { "e", 0145 },
        { "eacute", 0351 },
        { "ecircumflex", 0352 },
        { "edieresis", 0353 },
        { "egrave", 0350 },
        { "eight", 070 },
        { "ellipsis", 0203 },
        { "emdash", 0204 },
        { "endash", 0205 },
        { "equal", 075 },
        { "eth", 0360 },
        { "exclam", 041 },
        { "exclamdown", 0241 },
        { "f", 0146 },
        { "fi", 0223 },
        { "five", 065 },
        { "fl", 0224 },
        { "florin", 0206 },
        { "four", 064 },
        { "fraction", 0207 },
        { "g", 0147 },
        { "germandbls", 0337 },
        { "grave", 0140 },
        { "greater", 076 },
        { "guillemotleft", 0253 },
        { "guillemotright", 0273 },
        { "guilsinglleft", 0210 },
        { "guilsinglright", 0211 },
        { "h", 0150 },
        { "hungarumlaut", 034 },
        { "hyphen", 055 },
        { "i", 0151 },
        { "iacute", 0355 },
        { "icircumflex", 0356 },
        { "idieresis", 0357 },
        { "igrave", 0354 },
        { "j", 0152 },
        { "k", 0153 },
        { "l", 0154 },
        { "less", 074 },
        { "logicalnot", 0254 },
        { "lslash", 0233 },
        { "m", 0155 },
        { "macron", 0257 },
        { "minus", 0212 },
        { "mu", 0265 },
        { "multiply", 0327 },
        { "n", 0156 },
        { "nine", 071 },
        { "ntilde", 0361 },
        { "numbersign", 043 },
        { "o", 0157 },
        { "oacute", 0363 },
        { "ocircumflex", 0364 },
        { "odieresis", 0366 },
        { "oe", 0234 },
        { "ogonek", 035 },
        { "ograve", 0362 },
        { "one", 061 },
        { "onehalf", 0275 },
        { "onequarter", 0274 },
        { "onesuperior", 0271 },
        { "ordfeminine", 0252 },
        { "ordmasculine", 0272 },
        { "oslash", 0370 },
        { "otilde", 0365 },
        { "p", 0160 },
        { "paragraph", 0266 },
        { "parenleft", 050 },
        { "parenright", 051 },
        { "percent", 045 },
        { "period", 056 },
        { "periodcentered", 0267 },
        { "perthousand", 0213 },
        { "plus", 053 },
        { "plusminus", 0261 },
        { "q", 0161 },
        { "question", 077 },
        { "questiondown", 0277 },
        { "quotedbl", 042 },
        { "quotedblbase", 0214 },
        { "quotedblleft", 0215 },
        { "quotedblright", 0216 },
        { "quoteleft", 0217 },
        { "quoteright", 0220 },
        { "quotesinglbase", 0221 },
        { "quotesingle", 047 },
        { "r", 0162 },
        { "registered", 0256 },
        { "ring", 036 },
        { "s", 0163 },
        { "scaron", 0235 },
        { "section", 0247 },
        { "semicolon", 073 },
        { "seven", 067 },
        { "six", 066 },
        { "slash", 057 },
        { "space", 040 },
        { "sterling", 0243 },
        { "t", 0164 },
        { "thorn", 0376 },
        { "three", 063 },
        { "threequarters", 0276 },
        { "threesuperior", 0263 },
        { "tilde", 037 },
        { "trademark", 0222 },
        { "two", 062 },
        { "twosuperior", 0262 },
        { "u", 0165 },
        { "uacute", 0372 },
        { "ucircumflex", 0373 },
        { "udieresis", 0374 },
        { "ugrave", 0371 },
        { "underscore", 0137 },
        { "v", 0166 },
        { "w", 0167 },
        { "x", 0170 },
        { "y", 0171 },
        { "yacute", 0375 },
        { "ydieresis", 0377 },
        { "yen", 0245 },
        { "z", 0172 },
        { "zcaron", 0236 },
        { "zero", 060 }
    };
} }
