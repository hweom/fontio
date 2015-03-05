#pragma once

#include <array>

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
        {
            this->a[0][0] = a00;
            this->a[0][1] = a01;
            this->a[1][0] = a10;
            this->a[1][1] = a11;
            this->a[2][0] = a20;
            this->a[2][1] = a21;
        }

        CffFontMatrix(const std::array<double, 6>& a)
        {
            this->a[0][0] = a[0];
            this->a[0][1] = a[1];
            this->a[1][0] = a[2];
            this->a[1][1] = a[3];
            this->a[2][0] = a[4];
            this->a[2][1] = a[5];
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
