#pragma once

namespace fontio { namespace model
{
    template<typename T>
    class Point2
    {
    private:

        T x = 0, y = 0;

    public:

        Point2()
        {
        }

        Point2(T x, T y)
            : x(x)
            , y(y)
        {
        }

    public:

        T GetX() const
        {
            return this->x;
        }

        T GetY() const
        {
            return this->y;
        }

    };

    using Point2I = Point2<int>;

    using Point2F = Point2<float>;
} }
