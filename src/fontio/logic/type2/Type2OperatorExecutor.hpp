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

        std::unordered_set<Type2OperatorType> stackClearingOperators;

        std::deque<Type2Object> stack;

        bool widthParsed = false;

        Point2I currentPoint = Point2I(0, 0);

    public:

        Type2OperatorExecutor()
        {
            InitStackClearingOperators();
        }

    public:

        void Execute(
            IType2Context& context,
            const Type2Charstring& charstring,
            const Type2SubroutineAccessor& localSubroutines,
            const Type2SubroutineAccessor& globalSubroutines)
        {
            for (const auto& object : charstring.GetObjects())
            {
            }
        }

    private:

        void ExecuteObject(IType2Context& context, const Type2Object& object)
        {
            if (object.IsOperand())
            {
                this->stack.push_front(object);
            }
            else
            {
                this->ExecuteOperator(context, object.GetOperator(), object.GetArgCount());
            }
        }

        void ExecuteOperator(IType2Context& context, Type2OperatorType op, uint16_t argCount)
        {
            if (!this->widthParsed && this->IsStackClearingOperator(op))
            {
                if (!this->stack.empty())
                {
                    context.SetWidth(this->stack.back().GetIntegerSafe());
                }

                this->widthParsed = true;
            }

            switch (op)
            {
            case Type2OperatorType::HStem:
                break;
            case Type2OperatorType::VStem:
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
                break;
            case Type2OperatorType::Return:
                break;
            case Type2OperatorType::EndChar:
                break;
            case Type2OperatorType::HStemHM:
                break;
            case Type2OperatorType::HintMask:
                break;
            case Type2OperatorType::CntrMask:
                break;
            case Type2OperatorType::RMoveTo:
                this->currentPoint += this->ToPoint(this->GetFromBottom(2));
                context.MoveTo(this->currentPoint);
                break;

            case Type2OperatorType::HMoveTo:
                this->currentPoint += Point2I(this->GetFromBottom(1)[0], 0);
                context.MoveTo(this->currentPoint);
                break;

            case Type2OperatorType::VStemHM:
                break;
            case Type2OperatorType::RCurveLine:
                break;
            case Type2OperatorType::RLineCurve:
                break;
            case Type2OperatorType::VVCurveTo:
                this->CurveSequence(context, false);
                break;

            case Type2OperatorType::HHCurveTo:
                this->CurveSequence(context, true);
                break;

            case Type2OperatorType::CallGSubr:
                break;
            case Type2OperatorType::VHCurveTo:
                this->CurveLadder(context, false);
                break;

            case Type2OperatorType::HVCurveTo:
                this->CurveLadder(context, true);
                break;

            case Type2OperatorType::And:
                break;
            case Type2OperatorType::Or:
                break;
            case Type2OperatorType::Not:
                break;
            case Type2OperatorType::Abs:
                break;
            case Type2OperatorType::Add:
                break;
            case Type2OperatorType::Sub:
                break;
            case Type2OperatorType::Div:
                break;
            case Type2OperatorType::Neg:
                break;
            case Type2OperatorType::Eq:
                break;
            case Type2OperatorType::Drop:
                break;
            case Type2OperatorType::Put:
                break;
            case Type2OperatorType::Get:
                break;
            case Type2OperatorType::IfElse:
                break;
            case Type2OperatorType::Random:
                break;
            case Type2OperatorType::Mul:
                break;
            case Type2OperatorType::Sqrt:
                break;
            case Type2OperatorType::Dup:
                break;
            case Type2OperatorType::Exch:
                break;
            case Type2OperatorType::Index:
                break;
            case Type2OperatorType::Roll:
                break;
            case Type2OperatorType::HFlex:
                break;
            case Type2OperatorType::Flex:
                break;
            case Type2OperatorType::HFlex1:
                break;
            case Type2OperatorType::Flex1:
                break;
            default:
                throw std::runtime_error("Unknown operator");
            };
        }

        void LineLadder(IType2Context& context, bool dir)
        {
            for (auto d : this->GetAllFromBottom()))
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

            auto addition = this->stack.empty() ? 0 : this->GetFromBottom(0)[0];

            for (size_t i = 0; i < values.size(); i += 4)
            {
                bool lastCycle = ((i + 4) >= values.size());
                auto lastAddition = lastCycle ? addition : 0;

                auto t1 = this->currentPoint + (dir ? Point2I(values[i], 0) : Point2I(0, values[i], 0));
                auto t2 = t1 + Point2I(values[i + 1], values[i + 2]);
                this->currentPoint = t2 + (dir ? Point2I(lastAddition, values[i + 3]) : Point2I(values[i + 3], lastAddition));

                context.BezierTo(t1, t2, this->currentPoint);

                dir = !dir;
            }
        }

        void CurveSequence(IType2Context& context, bool dir)
        {
            bool extraAgrument = (this->stack.size() % 4) != 0;
            auto addition = extraAgrument ? this->GetFromBottom(0)[0] : 0;

            for (size_t i = 0; i < values.size(); i += 4)
            {
                bool firstCycle = i == 0;
                auto firstAddition = firstCycle ? addition : 0;

                auto t1 = this->currentPoint + (dir ? Point2I(values[i], firstAddition) : Point2I(0, values[i], firstAddition));
                auto t2 = t1 + Point2I(values[i + 1], values[i + 2]);
                this->currentPoint = t2 + (dir ? Point2I(values[i + 3], 0) : Point2I(0, values[i + 3]));

                context.BezierTo(t1, t2, this->currentPoint);

                dir = !dir;
            }
        }

        bool IsStackClearingOperator(Type2OperatorType op) const
        {
            return this->stackClearingOperators.count(op) > 0;
        }

        std::vector<int> GetFromBottom(size_t n)
        {
            if (this->stack.size() < n)
            {
                throw std::runtime_error("Not enough arguments");
            }

            std::vector<int> result;
            for (size_t i = 0; i < n; i++)
            {
                result[i] = this->stack.back();
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
        std::vector<std::array<Point2I, 3>> ToPointTuples(const std::vector<int>& values)
        {
            assert ((values.size() % (N * 2)) == 0);

            std::vector<std::array<Point2I, N>> result(values.size() / (N * 2), Point2I());
            auto pos = result.begin();
            for (size_t i = 0; i < values.size(); i += 6)
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

        void InitStackClearingOperators()
        {
            this->stackClearingOperators.insert(Type2OperatorType::RMoveTo);
            this->stackClearingOperators.insert(Type2OperatorType::HMoveTo);
            this->stackClearingOperators.insert(Type2OperatorType::VMoveTo);
            this->stackClearingOperators.insert(Type2OperatorType::RLineTo);
            this->stackClearingOperators.insert(Type2OperatorType::HLineTo);
            this->stackClearingOperators.insert(Type2OperatorType::VLineTo);
            this->stackClearingOperators.insert(Type2OperatorType::RRCurveTo);
            this->stackClearingOperators.insert(Type2OperatorType::HHCurveTo);
            this->stackClearingOperators.insert(Type2OperatorType::HVCurveTo);
            this->stackClearingOperators.insert(Type2OperatorType::RCurveLine);
            this->stackClearingOperators.insert(Type2OperatorType::RLineCurve);
            this->stackClearingOperators.insert(Type2OperatorType::VHCurveTo);
            this->stackClearingOperators.insert(Type2OperatorType::VVCurveTo);
            this->stackClearingOperators.insert(Type2OperatorType::Flex);
            this->stackClearingOperators.insert(Type2OperatorType::HFlex);
            this->stackClearingOperators.insert(Type2OperatorType::HFlex1);
            this->stackClearingOperators.insert(Type2OperatorType::Flex1);
            this->stackClearingOperators.insert(Type2OperatorType::EndChar);
            this->stackClearingOperators.insert(Type2OperatorType::HStem);
            this->stackClearingOperators.insert(Type2OperatorType::VStem);
            this->stackClearingOperators.insert(Type2OperatorType::HStemHM);
            this->stackClearingOperators.insert(Type2OperatorType::VStemHM);
            this->stackClearingOperators.insert(Type2OperatorType::HintMask);
            this->stackClearingOperators.insert(Type2OperatorType::CntrMask);
        }
    };
} } }
