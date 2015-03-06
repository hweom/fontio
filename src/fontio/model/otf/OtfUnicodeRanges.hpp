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

#include <cinttypes>

#include <vector>

namespace fontio { namespace model { namespace otf
{
    class OtfUnicodeRanges
    {
    public:

        static const uint16_t UNKNOWN_RANGE = 0xFFFF;

    private:

        struct Range
        {
            uint16_t rangeId;

            uint16_t start;

            uint16_t end;
        };

    public:

        uint16_t GetRangeId(uint16_t code) const
        {
            const auto& ranges = GetRanges();

            for (const auto& range : ranges)
            {
                if ((range.start <= code) && (range.end >= code))
                {
                    return range.rangeId;
                }
            }

            return UNKNOWN_RANGE;
        }

    private:

        static const std::vector<Range>& GetRanges()
        {
            static std::vector<Range> ranges =
            {
                {0, 0x0000, 0x007F},
                {1, 0x0080, 0x00FF},
                {2, 0x0100, 0x017F},
                {3, 0x0180, 0x024F},
                {4, 0x0250, 0x02AF},
                {4, 0x1D00, 0x1D7F},
                {4, 0x1D80, 0x1DBF},
                {5, 0x02B0, 0x02FF},
                {5, 0xA700, 0xA71F},
                {6, 0x0300, 0x036F},
                {6, 0x1DC0, 0x1DFF},
                {7, 0x0370, 0x03FF},
                {8, 0x2C80, 0x2CFF},
                {9, 0x0400, 0x04FF},
                {9, 0x0500, 0x052F},
                {9, 0x2DE0, 0x2DFF},
                {9, 0xA640, 0xA69F},
                {10, 0x0530, 0x058F},
                {11, 0x0590, 0x05FF},
                {12, 0xA500, 0xA63F},
                {13, 0x0600, 0x06FF},
                {13, 0x0750, 0x077F},
                {14, 0x07C0, 0x07FF},
                {15, 0x0900, 0x097F},
                {16, 0x0980, 0x09FF},
                {17, 0x0A00, 0x0A7F},
                {18, 0x0A80, 0x0AFF},
                {19, 0x0B00, 0x0B7F},
                {20, 0x0B80, 0x0BFF},
                {21, 0x0C00, 0x0C7F},
                {22, 0x0C80, 0x0CFF},
                {23, 0x0D00, 0x0D7F},
                {24, 0x0E00, 0x0E7F},
                {25, 0x0E80, 0x0EFF},
                {26, 0x10A0, 0x10FF},
                {26, 0x2D00, 0x2D2F},
                {27, 0x1B00, 0x1B7F},
                {28, 0x1100, 0x11FF},
                {29, 0x1E00, 0x1EFF},
                {29, 0x2C60, 0x2C7F},
                {29, 0xA720, 0xA7FF},
                {30, 0x1F00, 0x1FFF},
                {31, 0x2000, 0x206F},
                {31, 0x2E00, 0x2E7F},
                {32, 0x2070, 0x209F},
                {33, 0x20A0, 0x20CF},
                {34, 0x20D0, 0x20FF},
                {35, 0x2100, 0x214F},
                {36, 0x2150, 0x218F},
                {37, 0x2190, 0x21FF},
                {37, 0x27F0, 0x27FF},
                {37, 0x2900, 0x297F},
                {37, 0x2B00, 0x2BFF},
                {38, 0x2200, 0x22FF},
                {38, 0x2A00, 0x2AFF},
                {38, 0x27C0, 0x27EF},
                {38, 0x2980, 0x29FF},
                {39, 0x2300, 0x23FF},
                {40, 0x2400, 0x243F},
                {41, 0x2440, 0x245F},
                {42, 0x2460, 0x24FF},
                {43, 0x2500, 0x257F},
                {44, 0x2580, 0x259F},
                {45, 0x25A0, 0x25FF},
                {46, 0x2600, 0x26FF},
                {47, 0x2700, 0x27BF},
                {48, 0x3000, 0x303F},
                {49, 0x3040, 0x309F},
                {50, 0x30A0, 0x30FF},
                {50, 0x31F0, 0x31FF},
                {51, 0x3100, 0x312F},
                {51, 0x31A0, 0x31BF},
                {52, 0x3130, 0x318F},
                {53, 0xA840, 0xA87F},
                {54, 0x3200, 0x32FF},
                {55, 0x3300, 0x33FF},
                {56, 0xAC00, 0xD7AF},
                {57, 0xD800, 0xDFFF},
                {58, 0x1090, 0x091F},
                {59, 0x4E00, 0x9FFF},
                {59, 0x2E80, 0x2EFF},
                {59, 0x2F00, 0x2FDF},
                {59, 0x2FF0, 0x2FFF},
                {59, 0x3400, 0x4DBF},
                {59, 0x2000, 0xA6DF},
                {59, 0x3190, 0x319F},
                {60, 0xE000, 0xF8FF},
                {61, 0x31C0, 0x31EF},
                {61, 0xF900, 0xFAFF},
                {61, 0x2F80, 0xFA1F},
                {62, 0xFB00, 0xFB4F},
                {63, 0xFB50, 0xFDFF},
                {64, 0xFE20, 0xFE2F},
                {65, 0xFE10, 0xFE1F},
                {65, 0xFE30, 0xFE4F},
                {66, 0xFE50, 0xFE6F},
                {67, 0xFE70, 0xFEFF},
                {68, 0xFF00, 0xFFEF},
                {69, 0xFFF0, 0xFFFF},
                {70, 0x0F00, 0x0FFF},
                {71, 0x0700, 0x074F},
                {72, 0x0780, 0x07BF},
                {73, 0x0D80, 0x0DFF},
                {74, 0x1000, 0x109F},
                {75, 0x1200, 0x137F},
                {75, 0x1380, 0x139F},
                {75, 0x2D80, 0x2DDF},
                {76, 0x13A0, 0x13FF},
                {77, 0x1400, 0x167F},
                {78, 0x1680, 0x169F},
                {79, 0x16A0, 0x16FF},
                {80, 0x1780, 0x17FF},
                {80, 0x19E0, 0x19FF},
                {81, 0x1800, 0x18AF},
                {82, 0x2800, 0x28FF},
                {83, 0xA000, 0xA48F},
                {83, 0xA490, 0xA4CF},
                {84, 0x1700, 0x171F},
                {84, 0x1720, 0x173F},
                {84, 0x1740, 0x175F},
                {84, 0x1760, 0x177F},
                {85, 0x1030, 0x032F},
                {86, 0x1033, 0x034F},
                {87, 0x1040, 0x044F},
                {88, 0x1D00, 0xD0FF},
                {88, 0x1D10, 0xD1FF},
                {88, 0x1D20, 0xD24F},
                {89, 0x1D40, 0xD7FF},
                {90, 0xFF00, 0xFFFD},
                {90, 0x1000, 0xFFFD},
                {91, 0xFE00, 0xFE0F},
                {91, 0xE010, 0x01EF},
                {92, 0xE000, 0x007F},
                {93, 0x1900, 0x194F},
                {94, 0x1950, 0x197F},
                {95, 0x1980, 0x19DF},
                {96, 0x1A00, 0x1A1F},
                {97, 0x2C00, 0x2C5F},
                {98, 0x2D30, 0x2D7F},
                {99, 0x4DC0, 0x4DFF},
                {100, 0xA800, 0xA82F},
                {101, 0x1000, 0x007F},
                {101, 0x1008, 0x00FF},
                {101, 0x1010, 0x013F},
                {102, 0x1014, 0x018F},
                {103, 0x1038, 0x039F},
                {104, 0x103A, 0x03DF},
                {105, 0x1045, 0x047F},
                {106, 0x1048, 0x04AF},
                {107, 0x1080, 0x083F},
                {108, 0x10A0, 0x0A5F},
                {109, 0x1D30, 0xD35F},
                {110, 0x1200, 0x23FF},
                {110, 0x1240, 0x247F},
                {111, 0x1D36, 0xD37F},
                {112, 0x1B80, 0x1BBF},
                {113, 0x1C00, 0x1C4F},
                {114, 0x1C50, 0x1C7F},
                {115, 0xA880, 0xA8DF},
                {116, 0xA900, 0xA92F},
                {117, 0xA930, 0xA95F},
                {118, 0xAA00, 0xAA5F},
                {119, 0x1019, 0x01CF},
                {120, 0x101D, 0x01FF},
                {121, 0x102A, 0x02DF},
                {121, 0x1028, 0x029F},
                {121, 0x1092, 0x093F},
                {122, 0x1F03, 0xF09F},
                {122, 0x1F00, 0xF02F}
            };

            return ranges;
        }
    };
} } }
