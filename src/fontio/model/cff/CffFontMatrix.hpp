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
