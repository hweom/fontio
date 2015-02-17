#pragma once

#include <cinttypes>

namespace fontio { namespace model
{
    class BoundBox
    {
    private:

        int32_t x0, y0, x1, y1;

    public:

        BoundBox()
        {
        }

        BoundBox(int32_t x0, int32_t y0, int32_t x1, int32_t y1)
            : x0(x0)
            , y0(y0)
            , x1(x1)
            , y1(y1)
        {
        }

    public:

        int32_t GetWidth() const
        {
            return this->x1 - this->x0;
        }

        int32_t GetX0() const
        {
            return this->x0;
        }

        int32_t GetY0() const
        {
            return this->y0;
        }

        int32_t GetX1() const
        {
            return this->x1;
        }

        int32_t GetY1() const
        {
            return this->y1;
        }
    };
} }
