#pragma once

namespace fontio { namespace model { namespace otf
{
    enum class OtfPostTableVersion : uint32_t
    {
        Version_1_0 = 0x00010000,

        Version_2_0 = 0x00020000,

        Version_2_5 = 0x00025000,

        Version_3_0 = 0x00030000
    };
} } }
