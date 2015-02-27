#pragma once

namespace fontio { namespace model { namespace otf
{
    enum class OtfTableType
    {
        Invalid = 0,

        Cff,

        Cmap,

        Head,

        Hhea,

        Hmtx,

        Maxp,

        Name,

        Os2,

        Post
    };
} } }
