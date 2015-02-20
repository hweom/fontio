#include <gtest/gtest.h>

#include <fontio/logic/type2/Type2GlyphMetricsContext.hpp>

namespace fontio { namespace logic { namespace type2
{
    class Type2GlyphMestricsContextTests : public testing::Test
    {
    protected:

        Type2GlyphMetricsContext context;
    };

    TEST_F(Type2GlyphMestricsContextTests, CanCalculateBezierBoundBox)
    {
        this->context.MoveTo(Point2I(0,0));

        this->context.BezierTo(Point2I(0, 10), Point2I(10, 10), Point2I(10, 0));

        auto box = this->context.GetBoundBox();

        ASSERT_EQ(0, box.GetX0());
        ASSERT_EQ(0, box.GetY0());
        ASSERT_EQ(10, box.GetX1());
        ASSERT_EQ(7, box.GetY1());
    }
} } }
