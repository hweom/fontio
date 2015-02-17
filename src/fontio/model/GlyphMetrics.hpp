#pragma once

#include <cinttypes>

#include <fontio/model/BoundBox.hpp>

namespace fontio { namespace model
{
    class GlyphMetrics
    {
    private:

        BoundBox boundBox;

        uint32_t advanceWidth;

        int32_t leftSideBearings;

    public:

        const BoundBox& GetBoundBox() const
        {
            return this->boundBox;
        }

        uint32_t GetAdvanceWidth() const
        {
            return this->advanceWidth;
        }

        int32_t GetLeftSideBearings() const
        {
            return this->leftSideBearings;
        }
    };
} }