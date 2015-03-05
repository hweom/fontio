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

        Point2<T>& operator += (const Point2<T>& p)
        {
            this->x += p.x;
            this->y += p.y;

            return *this;
        }

        inline friend Point2<T> operator + (const Point2<T>& p1, const Point2<T>& p2)
        {
            return Point2<T>(p1.x + p2.x, p1.y + p2.y);
        }

        inline friend Point2<T> operator - (const Point2<T>& p1, const Point2<T>& p2)
        {
            return Point2<T>(p1.x - p2.x, p1.y - p2.y);
        }
    };

    using Point2I = Point2<int>;

    using Point2F = Point2<float>;
} }
