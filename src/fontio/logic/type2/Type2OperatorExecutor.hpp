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

#include <deque>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

#include <fontio/logic/type2/IType2Context.hpp>
#include <fontio/logic/type2/Type2CharstringReader.hpp>
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

        Type2CharstringReaderState charstringState;

        Type2SubroutineAccessor localSubroutines;

        Type2SubroutineAccessor globalSubroutines;

        std::deque<int> stack;

        bool widthParsed = false;

        int nominalWidth;

        int defaultWidth;

        Point2I currentPoint = Point2I(0, 0);

#ifdef DEBUG
        std::ostringstream debugStream;
#endif

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
            this->Reset(localSubroutines, globalSubroutines, nominalWidth, defaultWidth);

#ifdef DEBUG
            try
            {
                this->ExecuteCharstring(context, charstring);

                std::cout << this->debugStream.str() << std::endl;
            }
            catch(std::runtime_error& ex)
            {
                throw std::runtime_error(std::string("Error: ") + ex.what() + "\n" + this->debugStream.str());
            }
#else
            this->ExecuteCharstring(context, charstring);
#endif
        }

    private:

        void Reset(const Type2SubroutineAccessor& localSubroutines,
            const Type2SubroutineAccessor& globalSubroutines,
            int nominalWidth,
            int defaultWidth)
        {
            this->localSubroutines = localSubroutines;
            this->globalSubroutines = globalSubroutines;
            this->nominalWidth = nominalWidth;
            this->defaultWidth = defaultWidth;

            this->stack.clear();
            this->widthParsed = false;
            this->currentPoint = Point2I(0, 0);

            this->charstringState.Reset();

#ifdef DEBUG
            this->debugStream.clear();
#endif
        }

        void ExecuteCharstring(IType2Context& context, const Type2Charstring& charstring)
        {
            Type2CharstringReader reader(this->charstringState, charstring);
            Type2Object object;
            size_t idx= 0;

            while (reader.GetNextObject(object))
            {
                if (!this->ExecuteObject(context, object))
                {
                    return;
                }

                idx++;
            }
        }

        bool ExecuteObject(IType2Context& context, const Type2Object& object)
        {
            if (object.IsOperand())
            {
#ifdef DEBUG
                this->debugStream << object.GetIntegerSafe() << " ";
#endif

                this->stack.push_front(object.GetIntegerSafe());
                return true;
            }
            else
            {
#ifdef DEBUG
                this->debugStream << object << std::endl;
#endif

                return this->ExecuteOperator(context, object.GetType(), object.IsStackClearingOperator(), object.GetBitmask());
            }
        }

        void RLineTo(IType2Context& context)
        {
            while (this->stack.size() >= 2)
            {
                this->currentPoint += this->ToPoint(this->GetFromBottom(2));
                context.LineTo(this->currentPoint);
            }
        }

        void RrCurveTo(IType2Context& context)
        {
            for (const auto& triple : this->ToPointTuples<3>(this->GetPacksFromBottom(6)))
            {
                auto t1 = this->currentPoint + triple[0];
                auto t2 = t1 + triple[1];
                this->currentPoint = t2 + triple[2];

                context.BezierTo(t1, t2, this->currentPoint);
            }
        }

        bool ExecuteOperator(IType2Context& context, Type2ObjectType op, bool stackClearing, uint64_t mask)
        {
            int hintPos = 0;

            if (!this->widthParsed && stackClearing)
            {
                // This operators require 1 argument
                if ((op == Type2ObjectType::HMoveTo) ||
                    (op == Type2ObjectType::VMoveTo))
                {
                    if (this->stack.size() > 1)
                    {
                        context.SetWidth(this->nominalWidth + this->GetFromBottom(1)[0]);
                    }
                    else
                    {
                        context.SetWidth(this->defaultWidth);
                    }
                }
                // Other operators, allowed to be first, take even number of arguments.
                else if ((this->stack.size() & 0x1) == 1)
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
            case Type2ObjectType::HStem:
            case Type2ObjectType::HStemHM:
                for (const auto& pair : this->ToTuples<2>(this->GetPacksFromBottom(2)))
                {
                    hintPos += pair[0];
                    context.AddHorizontalHint(hintPos, hintPos + pair[1]);
                    hintPos += pair[1];
                }

                break;

            case Type2ObjectType::VStem:
            case Type2ObjectType::VStemHM:
                for (const auto& pair : this->ToTuples<2>(this->GetPacksFromBottom(2)))
                {
                    hintPos += pair[0];
                    context.AddVerticalHint(hintPos, hintPos + pair[1]);
                    hintPos += pair[1];
                }

                break;

            case Type2ObjectType::VMoveTo:
                this->currentPoint += Point2I(0, this->GetFromBottom(1)[0]);
                context.MoveTo(this->currentPoint);

            case Type2ObjectType::RLineTo:
                this->RLineTo(context);
                break;

            case Type2ObjectType::HLineTo:
                this->LineLadder(context, true);
                break;

            case Type2ObjectType::VLineTo:
                this->LineLadder(context, false);
                break;

            case Type2ObjectType::RRCurveTo:
                this->RrCurveTo(context);
                break;

            case Type2ObjectType::CallSubr:
                this->CallSubroutine(context, this->localSubroutines);
                break;

            case Type2ObjectType::Return:
            case Type2ObjectType::EndChar:
                return false;

            case Type2ObjectType::HintMask:
                context.EnableHints(mask);
                break;

            case Type2ObjectType::CntrMask:
                break;

            case Type2ObjectType::RMoveTo:
                this->currentPoint += this->ToPoint(this->GetFromBottom(2));
                context.MoveTo(this->currentPoint);
                break;

            case Type2ObjectType::HMoveTo:
                this->currentPoint += Point2I(this->GetFromBottom(1)[0], 0);
                context.MoveTo(this->currentPoint);
                break;

            case Type2ObjectType::RCurveLine:
                this->RrCurveTo(context);
                this->RLineTo(context);
                break;

            case Type2ObjectType::RLineCurve:
                while (this->stack.size() >= 8)
                {
                    this->RLineTo(context);
                }

                this->RrCurveTo(context);
                break;

            case Type2ObjectType::VVCurveTo:
                this->CurveSequence(context, false);
                break;

            case Type2ObjectType::HHCurveTo:
                this->CurveSequence(context, true);
                break;

            case Type2ObjectType::CallGSubr:
                this->CallSubroutine(context, this->globalSubroutines);
                break;

            case Type2ObjectType::VHCurveTo:
                this->CurveLadder(context, false);
                break;

            case Type2ObjectType::HVCurveTo:
                this->CurveLadder(context, true);
                break;

            case Type2ObjectType::And:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Or:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Not:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Abs:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Add:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Sub:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Div:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Neg:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Eq:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Drop:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Put:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Get:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::IfElse:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Random:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Mul:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Sqrt:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Dup:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Exch:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Index:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::Roll:
                throw std::logic_error("Not implemented");
                break;

            case Type2ObjectType::HFlex:
                this->HFlex(context);
                break;

            case Type2ObjectType::Flex:
                this->Flex(context);
                break;

            case Type2ObjectType::HFlex1:
                this->HFlex1(context);
                break;

            case Type2ObjectType::Flex1:
                this->Flex1(context);
                break;

            case Type2ObjectType::Blend:
            case Type2ObjectType::DotSection:
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

        void CallSubroutine(IType2Context& context, const Type2SubroutineAccessor& accessor)
        {
            if (this->stack.size() == 0)
            {
                throw std::runtime_error("Missing subroutine index");
            }

            auto index = this->stack.front();
            this->stack.pop_front();

            this->ExecuteCharstring(context, accessor[index]);
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

        void Flex(IType2Context& context)
        {
            while (this->stack.size() >= 13)
            {
                auto pos = this->stack.rbegin();

                auto dx1 = *pos++;
                auto dy1 = *pos++;
                auto dx2 = *pos++;
                auto dy2 = *pos++;
                auto dx3 = *pos++;
                auto dy3 = *pos++;
                auto dx4 = *pos++;
                auto dy4 = *pos++;
                auto dx5 = *pos++;
                auto dy5 = *pos++;
                auto dx6 = *pos++;
                auto dy6 = *pos++;
                auto fd = *pos++;

                this->stack.erase(pos.base(), this->stack.end());

                auto p0 = this->currentPoint += Point2I(dx1, dy1);
                auto p1 = this->currentPoint += Point2I(dx2, dy2);
                auto p2 = this->currentPoint += Point2I(dx3, dy3);
                auto p3 = this->currentPoint += Point2I(dx4, dy4);
                auto p4 = this->currentPoint += Point2I(dx5, dy5);
                auto p5 = this->currentPoint += Point2I(dx6, dy6);

                context.BezierTo(p0, p1, p2);
                context.BezierTo(p3, p4, p5);
            }
        }

        void HFlex(IType2Context& context)
        {
            while (this->stack.size() >= 7)
            {
                auto pos = this->stack.rbegin();

                auto dx1 = *pos++;
                auto dx2 = *pos++;
                auto dy2 = *pos++;
                auto dx3 = *pos++;
                auto dx4 = *pos++;
                auto dx5 = *pos++;
                auto dx6 = *pos++;

                this->stack.erase(pos.base(), this->stack.end());

                auto p0 = this->currentPoint += Point2I(dx1, 0);
                auto p1 = this->currentPoint += Point2I(dx2, dy2);
                auto p2 = this->currentPoint += Point2I(dx3, 0);
                auto p3 = this->currentPoint += Point2I(dx4, 0);
                auto p4 = this->currentPoint += Point2I(dx5, 0);
                auto p5 = this->currentPoint += Point2I(dx6, 0);

                context.BezierTo(p0, p1, p2);
                context.BezierTo(p3, p4, p5);
            }
        }

        void Flex1(IType2Context& context)
        {
            while (this->stack.size() >= 11)
            {
                auto pos = this->stack.rbegin();

                auto dx1 = *pos++;
                auto dy1 = *pos++;
                auto dx2 = *pos++;
                auto dy2 = *pos++;
                auto dx3 = *pos++;
                auto dy3 = *pos++;
                auto dx4 = *pos++;
                auto dy4 = *pos++;
                auto dx5 = *pos++;
                auto dy5 = *pos++;
                auto d6 = *pos++;

                this->stack.erase(pos.base(), this->stack.end());

                auto start = this->currentPoint;

                auto p0 = this->currentPoint += Point2I(dx1, dy1);
                auto p1 = this->currentPoint += Point2I(dx2, dy2);
                auto p2 = this->currentPoint += Point2I(dx3, dy3);
                auto p3 = this->currentPoint += Point2I(dx4, dy4);
                auto p4 = this->currentPoint += Point2I(dx5, dy5);

                auto delta = this->currentPoint - start;

                auto dx6 = abs(delta.GetX()) > abs(delta.GetY()) ? d6 : 0;
                auto dy6 = abs(delta.GetX()) > abs(delta.GetY()) ? 0 : d6;

                auto p5 = this->currentPoint += Point2I(dx6, dy6);

                context.BezierTo(p0, p1, p2);
                context.BezierTo(p3, p4, p5);
            }
        }

        void HFlex1(IType2Context& context)
        {
            while (this->stack.size() >= 9)
            {
                auto pos = this->stack.rbegin();

                auto dx1 = *pos++;
                auto dy1 = *pos++;
                auto dx2 = *pos++;
                auto dy2 = *pos++;
                auto dx3 = *pos++;
                auto dx4 = *pos++;
                auto dx5 = *pos++;
                auto dy5 = *pos++;
                auto dx6 = *pos++;

                this->stack.erase(pos.base(), this->stack.end());

                auto p0 = this->currentPoint += Point2I(dx1, dy1);
                auto p1 = this->currentPoint += Point2I(dx2, dy2);
                auto p2 = this->currentPoint += Point2I(dx3, 0);
                auto p3 = this->currentPoint += Point2I(dx4, 0);
                auto p4 = this->currentPoint += Point2I(dx5, dy5);
                auto p5 = this->currentPoint += Point2I(dx6, 0);

                context.BezierTo(p0, p1, p2);
                context.BezierTo(p3, p4, p5);
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
