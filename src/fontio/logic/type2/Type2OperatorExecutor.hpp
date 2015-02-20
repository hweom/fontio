#pragma once

#include <deque>
#include <vector>
#include <unordered_set>

#include <fontio/logic/type2/IType2Context.hpp>
#include <fontio/logic/type2/Type2SubroutineAccessor.hpp>
#include <fontio/model/GlyphMetrics.hpp>
#include <fontio/model/type2/Type2Charstring.hpp>

namespace fontio { namespace logic { namespace type2
{
    using namespace fontio::model;
    using namespace fontio::model::type2;

    class Type2OperatorExecutor
    {
    private:

        std::deque<Type2Object> stack;

        bool widthParsed = false;

        int nominalWidth;

        int defaultWidth;

        Point2I currentPoint = Point2I(0, 0);

    public:

        Type2OperatorExecutor()
        {
        }

    public:

        void Execute(
            IType2Context& context,
            const Type2Charstring& charstring,
            const Type2SubroutineAccessor& localSubroutines,
            const Type2SubroutineAccessor& globalSubroutines,
            int nominalWidth,
            int defaultWidth)
        {
            this->Reset(nominalWidth, defaultWidth);

            for (const auto& object : charstring.GetObjects())
            {
                if (!this->ExecuteObject(context, object))
                {
                    return;
                }
            }
        }

    private:

        void Reset(int nominalWidth, int defaultWidth)
        {
            this->nominalWidth = nominalWidth;
            this->defaultWidth = defaultWidth;

            this->stack.clear();
            this->widthParsed = false;
            this->currentPoint = Point2I(0, 0);
        }

        bool ExecuteObject(IType2Context& context, const Type2Object& object)
        {
            if (object.IsOperand())
            {
                this->stack.push_front(object);
                return true;
            }
            else
            {
                return this->ExecuteOperator(context, object.GetOperator(), object.GetArgCount(), object.IsStackClearingOperator());
            }
        }

        bool ExecuteOperator(IType2Context& context, Type2OperatorType op, uint16_t argCount, bool stackClearing)
        {
            int hintPos = 0;

            if (!this->widthParsed && stackClearing)
            {
                if (!this->stack.empty())
                {
                    context.SetWidth(this->nominalWidth + this->GetFromBottom(1)[0]);
                }
                else
                {
                    context.SetWidth(this->defaultWidth);
                }

                this->widthParsed = true;
            }

            switch (op)
            {
            case Type2OperatorType::HStem:
            case Type2OperatorType::HStemHM:
                for (const auto& pair : this->ToTuples<2>(this->GetPacksFromBottom(2)))
                {
                    hintPos += pair[0];
                    context.AddHorizontalHint(hintPos, hintPos + pair[1]);
                    hintPos += pair[1];
                }

                break;

            case Type2OperatorType::VStem:
            case Type2OperatorType::VStemHM:
                for (const auto& pair : this->ToTuples<2>(this->GetPacksFromBottom(2)))
                {
                    hintPos += pair[0];
                    context.AddVerticalHint(hintPos, hintPos + pair[1]);
                    hintPos += pair[1];
                }

                break;

            case Type2OperatorType::VMoveTo:
                this->currentPoint += Point2I(0, this->GetFromBottom(1)[0]);
                context.MoveTo(this->currentPoint);

            case Type2OperatorType::RLineTo:
                this->currentPoint += this->ToPoint(this->GetFromBottom(2));
                context.LineTo(this->currentPoint);
                break;

            case Type2OperatorType::HLineTo:
                this->LineLadder(context, true);
                break;

            case Type2OperatorType::VLineTo:
                this->LineLadder(context, false);
                break;

            case Type2OperatorType::RRCurveTo:
                for (const auto& triple : this->ToPointTuples<3>(this->GetPacksFromBottom(6)))
                {
                    auto t1 = this->currentPoint + triple[0];
                    auto t2 = t1 + triple[1];
                    this->currentPoint = t2 + triple[2];

                    context.BezierTo(t1, t2, this->currentPoint);
                }

                break;

            case Type2OperatorType::CallSubr:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Return:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::EndChar:
                return false;

            case Type2OperatorType::HintMask:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::CntrMask:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::RMoveTo:
                this->currentPoint += this->ToPoint(this->GetFromBottom(2));
                context.MoveTo(this->currentPoint);
                break;

            case Type2OperatorType::HMoveTo:
                this->currentPoint += Point2I(this->GetFromBottom(1)[0], 0);
                context.MoveTo(this->currentPoint);
                break;

            case Type2OperatorType::RCurveLine:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::RLineCurve:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::VVCurveTo:
                this->CurveSequence(context, false);
                break;

            case Type2OperatorType::HHCurveTo:
                this->CurveSequence(context, true);
                break;

            case Type2OperatorType::CallGSubr:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::VHCurveTo:
                this->CurveLadder(context, false);
                break;

            case Type2OperatorType::HVCurveTo:
                this->CurveLadder(context, true);
                break;

            case Type2OperatorType::And:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Or:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Not:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Abs:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Add:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Sub:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Div:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Neg:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Eq:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Drop:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Put:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Get:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::IfElse:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Random:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Mul:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Sqrt:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Dup:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Exch:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Index:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Roll:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::HFlex:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Flex:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::HFlex1:
                throw std::logic_error("Not implemented");
                break;

            case Type2OperatorType::Flex1:
                break;

            default:
                throw std::runtime_error("Unknown operator");
            };

            if (stackClearing)
            {
                this->stack.clear();
            }

            return true;
        }

        void LineLadder(IType2Context& context, bool dir)
        {
            for (auto d : this->GetAllFromBottom())
            {
                if (dir)
                {
                    this->currentPoint += Point2I(d, 0);
                }
                else
                {
                    this->currentPoint += Point2I(0, d);
                }

                context.LineTo(this->currentPoint);

                dir = !dir;
            }
        }

        void CurveLadder(IType2Context& context, bool dir)
        {
            auto values = this->GetPacksFromBottom(4);

            auto addition = this->stack.empty() ? 0 : this->GetFromBottom(1)[0];

            for (size_t i = 0; i < values.size(); i += 4)
            {
                bool lastCycle = ((i + 4) >= values.size());
                auto lastAddition = lastCycle ? addition : 0;

                auto t1 = this->currentPoint + (dir ? Point2I(values[i], 0) : Point2I(0, values[i]));
                auto t2 = t1 + Point2I(values[i + 1], values[i + 2]);
                this->currentPoint = t2 + (dir ? Point2I(lastAddition, values[i + 3]) : Point2I(values[i + 3], lastAddition));

                context.BezierTo(t1, t2, this->currentPoint);

                dir = !dir;
            }
        }

        void CurveSequence(IType2Context& context, bool dir)
        {
            bool extraAgrument = (this->stack.size() % 4) != 0;
            auto addition = extraAgrument ? this->GetFromBottom(1)[0] : 0;

            auto values = this->GetPacksFromBottom(4);

            for (size_t i = 0; i < values.size(); i += 4)
            {
                bool firstCycle = i == 0;
                auto firstAddition = firstCycle ? addition : 0;

                auto t1 = this->currentPoint + (dir ? Point2I(values[i], firstAddition) : Point2I(firstAddition, values[i]));
                auto t2 = t1 + Point2I(values[i + 1], values[i + 2]);
                this->currentPoint = t2 + (dir ? Point2I(values[i + 3], 0) : Point2I(0, values[i + 3]));

                context.BezierTo(t1, t2, this->currentPoint);

                dir = !dir;
            }
        }

        std::vector<int> GetFromBottom(size_t n)
        {
            if (this->stack.size() < n)
            {
                throw std::runtime_error("Not enough arguments");
            }

            std::vector<int> result(n);
            for (size_t i = 0; i < n; i++)
            {
                result[i] = this->stack.back().GetIntegerSafe();
                this->stack.pop_back();
            }

            return result;
        }

        std::vector<int> GetAllFromBottom()
        {
            return this->GetFromBottom(this->stack.size());
        }

        std::vector<int> GetPacksFromBottom(size_t packSize)
        {
            return this->GetFromBottom((this->stack.size() / packSize) * packSize);
        }

        Point2I ToPoint(const std::vector<int>& values)
        {
            assert (values.size() == 2);

            return Point2I(values[0], values[1]);
        }

        template<size_t N>
        std::vector<std::array<int, N>> ToTuples(const std::vector<int>& values)
        {
            assert ((values.size() % (N)) == 0);

            std::vector<std::array<int, N>> result(values.size() / N);
            auto pos = result.begin();
            for (size_t i = 0; i < values.size(); i += N)
            {
                auto& array = *(pos++);

                for (size_t j = 0; j < N; j++)
                {
                    array[j] = values[i + j];
                }
            }

            return result;
        }

        template<size_t N>
        std::vector<std::array<Point2I, N>> ToPointTuples(const std::vector<int>& values)
        {
            assert ((values.size() % (N * 2)) == 0);

            std::vector<std::array<Point2I, N>> result(values.size() / (N * 2));
            auto pos = result.begin();
            for (size_t i = 0; i < values.size(); i += N * 2)
            {
                auto& array = *(pos++);

                for (size_t j = 0; j < N; j++)
                {
                    array[j] = Point2I(values[i + j * 2], values[i + j * 2 + 1]);
                }
            }

            return result;
        }

        std::vector<Point2I> ToPointArray(const std::vector<int>& values)
        {
            assert ((values.size() & 0x1) == 0);

            std::vector<Point2I> result(values.size() / 2, Point2I());
            auto pos = result.begin();
            for (size_t i = 0; i < values.size(); i += 2)
            {
                *(pos++) = Point2I(values[i], values[i + 1]);
            }

            return result;
        }

        std::vector<Point2I> ToPointArraySwapped(const std::vector<int>& values)
        {
            assert ((values.size() & 0x1) == 0);

            std::vector<Point2I> result(values.size() / 2, Point2I());
            auto pos = result.begin();
            for (size_t i = 0; i < values.size(); i += 2)
            {
                *(pos++) = Point2I(values[i + 1], values[i]);
            }

            return result;
        }
    };
} } }
