#pragma once

#include <fontio/model/Point2.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model;

    class IType2Context
    {
    public:

        virtual void SetWidth(int width) = 0;

        virtual void MoveTo(const Point2I& p) = 0;

        virtual void LineTo(const Point2I& p) = 0;

        virtual void BezierTo(const Point2I& t1, const Point2I& t2, const Point2I& p) = 0;
    };
} } }
