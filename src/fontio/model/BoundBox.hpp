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

        template<typename T>
        BoundBox(const std::array<T, 4>& a, typename std::enable_if<std::is_arithmetic<T>::value>::type* dummy = nullptr)
            : x0(static_cast<int32_t>(a[0]))
            , y0(static_cast<int32_t>(a[1]))
            , x1(static_cast<int32_t>(a[2]))
            , y1(static_cast<int32_t>(a[3]))
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
