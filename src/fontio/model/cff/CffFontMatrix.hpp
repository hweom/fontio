#pragma once

namespace fontio { namespace model { namespace cff
{
    class CffFontMatrix
    {
    private:

        double a[3][2];

    public:

        CffFontMatrix()
        {
        }

        CffFontMatrix(double a00, double a01, double a10, double a11, double a20, double a21)
            : a { { a00, a01 }, { a10, a11}, { a20, a21 } }
        {
        }

    public:

        double GetScale() const
        {
            return this->a[0][0];
        }

        const double (&GetData() const)[3][2]
        {
            return this->a;
        }
    };
} } }
