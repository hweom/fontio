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

#include <fontio/model/cff/CffOperatorType.hpp>

namespace fontio { namespace model { namespace cff
{
    class CffObject
    {
    public:

        enum Type
        {
            Operator = 0,

            Integer = 1,

            Real = 2
        };

    private:

        Type type;

        union
        {
            CffOperatorType operatorType;

            int64_t integerValue;

            double realValue;
        };

    public:

        CffObject(CffOperatorType operatorType)
            : type(Operator)
            , operatorType(operatorType)
        {
        }

        CffObject(int32_t integerValue)
            : type(Integer)
            , integerValue(integerValue)
        {
        }

        CffObject(uint32_t integerValue)
            : type(Integer)
            , integerValue(integerValue)
        {
        }

        CffObject(double realValue)
            : type(Real)
            , realValue(realValue)
        {
        }

    public:

        bool IsOperator() const
        {
            return this->type == Operator;
        }

        bool IsOperand() const
        {
            return this->type != Operator;
        }

        CffOperatorType GetOperator() const
        {
            assert (this->type == Operator);

            return this->operatorType;
        }

        int64_t GetIntegerSafe() const
        {
            if (this->type == Integer)
            {
                return this->integerValue;
            }
            else
            {
                throw std::runtime_error("Not an integer");
            }
        }

        double GetRealSafe() const
        {
            if (this->type == Integer)
            {
                return (double) this->integerValue;
            }
            else if (this->type == Real)
            {
                return this->realValue;
            }
            else
            {
                throw std::runtime_error("Not a number");
            }
        }

        uint16_t GetSidSafe() const
        {
            if ((this->type == Integer) && (this->integerValue >= 0))
            {
                return (uint16_t)this->integerValue;
            }
            else
            {
                throw std::runtime_error("Not a SID");
            }
        }
    };
} } }
