#pragma once

namespace fontio { namespace model { namespace cff
{
    class CffBoundBox
    {
    private:

        double x0, y0, x1, y1;

    public:

        CffBoundBox()
        {
        }

        CffBoundBox(double x0, double y0, double x1, double y1)
            : x0(x0)
            , y0(y0)
            , x1(x1)
            , y1(y1)
        {
        }

    public:

        double GetX0() const
        {
            return this->x0;
        }

        double GetY0() const
        {
            return this->y0;
        }

        double GetX1() const
        {
            return this->x1;
        }

        double GetY1() const
        {
            return this->y1;
        }
    };
} } }
