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
