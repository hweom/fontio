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

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

#include <fontio/logic/type2/IType2Context.hpp>
#include <fontio/model/BoundBox.hpp>
#include <fontio/model/GlyphMetrics.hpp>

namespace fontio { namespace logic { namespace type2
{
    class Type2GlyphMetricsContext : public IType2Context
    {
    private:

        int width = 0;

        int x0 = std::numeric_limits<int>::max();

        int y0 = std::numeric_limits<int>::max();

        int x1 = std::numeric_limits<int>::min();

        int y1 = std::numeric_limits<int>::min();

        Point2I currentPoint;

    public:

        BoundBox GetBoundBox() const
        {
            return BoundBox(this->x0, this->y0, this->x1, this->y1);
        }

        GlyphMetrics GetMetrics() const
        {
            return GlyphMetrics(this->GetBoundBox(), this->width, this->x0);
        }

        virtual void SetWidth(int width) override
        {
            this->width = width;
        }

        virtual void MoveTo(const Point2I& p) override
        {
            this->currentPoint = p;
        }

        virtual void LineTo(const Point2I& p) override
        {
            this->UpdateBoundBox(this->currentPoint);
            this->UpdateBoundBox(p);

            this->currentPoint = p;
        }

        virtual void BezierTo(const Point2I& t1, const Point2I& t2, const Point2I& p) override
        {
            this->UpdateBoundBox(this->currentPoint);
            this->UpdateBoundBox(p);

            this->UpdateBoundBoxByBezierValue<0>(this->currentPoint, t1, t2, p);
            this->UpdateBoundBoxByBezierValue<1>(this->currentPoint, t1, t2, p);

            this->currentPoint = p;
        }

    private:

        void UpdateBoundBox(const Point2I& p)
        {
            this->x0 = std::min(this->x0, p.GetX());
            this->y0 = std::min(this->y0, p.GetY());
            this->x1 = std::max(this->x1, p.GetX());
            this->y1 = std::max(this->y1, p.GetY());
        }

        template<size_t idx>
        void UpdateBoundBoxByBezierValue(const Point2I& p0, const Point2I& p1, const Point2I& p2, const Point2I& p3)
        {
            auto roots = this->GetRootsOfSquareEquation(
                static_cast<float>(-this->At<idx>(p0) + 3 * this->At<idx>(p1) - 3 * this->At<idx>(p2) + this->At<idx>(p3)),
                static_cast<float>(2 * (this->At<idx>(p0) -2 * this->At<idx>(p1) +this->At<idx>(p2))),
                static_cast<float>(this->At<idx>(p1) -this->At<idx>(p0)));

            if ((roots.first == roots.first) && (roots.first >= 0.0f) && (roots.first <= 1.0f))
            {
                auto x = static_cast<int>(this->GetBezierValue<idx>(p0, p1, p2, p3, roots.first));

                this->UpdateBoundBoxByValue<idx>(x);
            }

            if ((roots.second == roots.second) && (roots.second >= 0.0f) && (roots.second <= 1.0f))
            {
                auto x = static_cast<int>(this->GetBezierValue<idx>(p0, p1, p2, p3, roots.second));

                this->UpdateBoundBoxByValue<idx>(x);
            }
        }

        template<size_t idx>
        float GetBezierValue(const Point2I& p0, const Point2I& p1, const Point2I& p2, const Point2I& p3, float t)
        {
            assert ((t >= 0.0f) && (t <= 1.0f));

            auto rt = 1.0f - t;

            return
                rt * rt * rt * this->At<idx>(p0) +
                3 * rt * rt * t * this->At<idx>(p1) +
                3 * rt * t * t * this->At<idx>(p2) +
                t * t * t * this->At<idx>(p3);
        }

        template<size_t idx>
        int At(const Point2I& p)
        {
            static_assert(idx != idx, "No such coordinate");
        }

        template<size_t idx>
        void UpdateBoundBoxByValue(int value)
        {
            static_assert(idx != idx, "No such coordinate");
        }

        std::pair<float, float> GetRootsOfSquareEquation(float a, float b, float c)
        {
            if (fabs(a) < 0.00001f)
            {
                if (fabs(b) < 0.00001f)
                {
                    return std::make_pair(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
                }

                return std::make_pair(-c / b, std::numeric_limits<float>::quiet_NaN());
            }

            auto d = b * b - 4 * a * c;

            if (d > 0.0f)
            {
                auto rootD = sqrt(d);

                return std::make_pair((-b + rootD) / (2 * a), (-b - rootD) / (2 * a));
            }
            else if (d < 0.0f)
            {
                return std::make_pair(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
            }
            else
            {
                return std::make_pair(-b / (2 * a), std::numeric_limits<float>::quiet_NaN());
            }
        }

        virtual void AddHorizontalHint(int y0, int y1) override
        {
        }

        virtual void AddVerticalHint(int x0, int x1) override
        {
        }

        virtual void EnableHints(uint64_t mask) override
        {
        }
    };

    template<>
    inline int Type2GlyphMetricsContext::At<0>(const Point2I& p)
    {
        return p.GetX();
    }

    template<>
    inline int Type2GlyphMetricsContext::At<1>(const Point2I& p)
    {
        return p.GetY();
    }

    template<>
    inline void Type2GlyphMetricsContext::UpdateBoundBoxByValue<0>(int value)
    {
        this->x0 = std::min(this->x0, value);
        this->x1 = std::max(this->x1, value);
    }

    template<>
    inline void Type2GlyphMetricsContext::UpdateBoundBoxByValue<1>(int value)
    {
        this->y0 = std::min(this->y0, value);
        this->y1 = std::max(this->y1, value);
    }
} } }
