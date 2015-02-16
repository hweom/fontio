#pragma once

#include <cinttypes>

#include <fontio/model/type2/Type2OperatorType.hpp>

namespace fontio { namespace model { namespace type2
{
    class Type2Object
    {
    public:

        enum Type
        {
            Operator = 0,

            Integer = 1,
        };

    private:

        Type type;

        union
        {
            Type2OperatorType operatorType;

            int32_t integerValue;
        };

    public:

        Type2Object(Type2OperatorType operatorType)
            : type(Operator)
            , operatorType(operatorType)
        {
        }

        Type2Object(int32_t integerValue)
            : type(Integer)
            , integerValue(integerValue)
        {
        }

        Type2Object(uint32_t integerValue)
            : type(Integer)
            , integerValue(integerValue)
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

        Type2OperatorType GetOperator() const
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
    };
} } }
